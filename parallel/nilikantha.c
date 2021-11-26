/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje C. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está paralelizado, utilizando la tecnología de OpenMP.
    Hago uso del archivo utils.h generado por el Prof. Pedro Pérez
* Comando para compilar en Linux: gcc nilikantha.c -fopenmp
* Comando para correr en Linux: ./a.out
* NOTA: De especificar otro nombre del ejecutable al compilar utilizar ./nombreDelEjecutable.out
*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "utils.h"

#define SIZE 1000000000 //1e9

/**
 * @brief The function belows receives a parameter size, which represents the nth term of the
 * Nilikantha series wanted for the approximation of Pi. The functions uses the OpenMP directive 
 * parallel for, which automatically divides a for statement to be processed by individual threads.
 * The directive declares the size variable to be shared across all threads, and an individual copy
 * of the variables: sign, di, denominator and term are created for each thread. Another declaration
 * added is the reduction keyword, which signals a reduction operation on the selected variable, 
 * and which operation; in this case it is a sum of every individual value of result.
 * 
 * @param size int
 * @return double 
 */
double nilik(int size) {
	double result = 3.0;
	int i;
	double sign, di, denominator, term;
	#pragma omp parallel for shared(size) private(sign, di, denominator, term) reduction(+:result)
	for(i = 1; i <= size; i++){
        sign = i % 2 == 0 ? -1.0 : 1.0;
        di = i*2.0;
        denominator = (di*(di+1)*(di+2));
        term = (4.0*sign)/denominator;
        result += term;
    }
	return result;
}

int main(int argc, char* argv[]) {
    if(argc >= 2){
        printf("Error: No arguments are allowed\n");
        return -1;
    }
	int i;
	double ms, result;

	printf("Starting...\n");
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();
		
		result = nilik(SIZE);
		
		ms += stop_timer();
	}
	printf("Pi is approx: %.15lf \n", result);
    printf("Average time elapsed: %.7lf ms\n", (ms / N));
	
	return 0;
}