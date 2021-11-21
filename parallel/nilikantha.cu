/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje CUDA C. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está paralelizado, utilizando la tecnología de CUDA de NVIDIA.
    Hago uso del archivo utils.h generado por el Prof. Pedro Pérez
* Comando para compilar en Linux: nvcc nilikantha.cu
* Comando para correr en Linux: ./a.out
* NOTA: De especificar otro nombre del ejecutable al compilar utilizar ./nombreDelEjecutable.out
*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "utils.h"

#define SIZE 1000000000 //1e9
#define THREADS	256
#define BLOCKS	MMIN(32, ((SIZE / THREADS) + 1))

/**
 * @brief This function will be run on the device (NVIDIA GPU), that is indicated by the
 * __global__ keyword. It will calculate the Nikilantha series for n terms, and save every 
 * partial sum for every block in the cache, which will be further reduced to be saved in 
 * the result array passed as parameter.
 * 
 * @param size int
 * @return double 
 */
__global__ void nilik(double *result) {
	/**
	 * The array declared below, will be shared across all blocks, and will
	 * save the partial sum of the Nilikantha terms calculated in the block
	 */
	__shared__ double cache[THREADS];

	/**
	 * The tid is a linealization of the memory in the GPU, and will be used
	 * for the calculation as the nth term
	 */
	int tid = threadIdx.x + (blockIdx.x * blockDim.x);
	int cacheIndex = threadIdx.x;

	double acum = 0.0, sign, di, denominator, term;
	/**
	 * Special case for the first element in the series
	 */
    if(tid == 0){
        acum += 3.0;
        tid += blockDim.x * gridDim.x;
    }

	/**
	 * The while loop below obtains every Nilikantha term for every threadId index in
	 * every block.
	 */
	while (tid < SIZE) {
		sign = tid % 2 == 0 ? -1.0 : 1.0;
        di = tid*2.0;
        denominator = (di*(di+1)*(di+2));
        term = (4.0*sign)/denominator;
        acum += term;
		tid += blockDim.x * gridDim.x;
	}

	/**
	 * Partial sum is saved in the cache
	 */
	cache[cacheIndex] = acum;

	/**
	 * The instruction below performs a block level syncronization barrier, this 
	 * means it will be called when every thread reaches this line in their execution pipeline
	 */
	__syncthreads();

	/**
	 * The code below, performs a reduction by adding the contents of the element in a power of 2
	 * distance to the element at the cacheIndex, which if recalled is the same as the threadId,
	 * it will stop after it reaches the original index. 
	 */
	int i = blockDim.x / 2;
	while (i > 0) {
		/**
		 * The if block belows prevents accidentaly accesing a non-valid index in the device.
		 */
		if (cacheIndex < i) {
			cache[cacheIndex] += cache[cacheIndex + i];
		}
		/**
		 * The line belows blocks all threads from advancing until they reach this line in their
		 * execution flow.
		 */
		__syncthreads();
		i /= 2;
	}

	/**
	 * After the contents in the block are summed up in each index of the cache, 
	 * it wil be added to the result array at the position indicated by its blockId
	 */
	if (cacheIndex == 0) {
		result[blockIdx.x] = cache[cacheIndex];
	}
}

int main(int argc, char* argv[]) {
    if(argc >= 2){
        printf("Error: No arguments are allowed\n");
        return -1;
    }
	int i;
	double *results, *d_r;
	double ms;

	/**
	 * Cache allocation in the host memory
	 */
	results = (double*) malloc( BLOCKS * sizeof(double) );

	/**
	 * Cache allocation in the device memory
	 */
	cudaMalloc( (void**) &d_r, BLOCKS * sizeof(double) );

	printf("Starting...\n");
	ms = 0;
	for (i = 1; i <= N; i++) {
		start_timer();
		/**
		 * This command calls the code defined in the function nilik and specifies the number of blocks
		 * and threads to be used for the calculation, the parameter is the cache array 
		 * allocated in the device.
		 */
		nilik<<<BLOCKS, THREADS>>> (d_r);

		ms += stop_timer();
	}

	/**
	 * Results from the device are copied onto the host 
	 */
	cudaMemcpy(results, d_r, BLOCKS * sizeof(double), cudaMemcpyDeviceToHost);

	/**
	 * The block below performs a reduction in the results array, getting the approximation of Pi.
	 * By using the parallel reduction earlier in the nilik function, it allowed us to only 
	 * need to perform n-block amount of operations to get the result, instead of adding the 
	 * result of every thread.
	 */
	double acum = 0;
	for (i = 0; i < BLOCKS; i++) {
		acum += results[i];
	}

	printf("Pi is approx: %.15lf \n", acum);
    printf("Average time elapsed: %.3lf ms\n", (ms / N));

	/**
	 * De-allocation of device memory
	 */
	cudaFree(d_r);

	/**
	 * De-allocation of host memory
	 */
	free(results);
	return 0;
}
