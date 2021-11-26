/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje C. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está de forma secuencial.
    Hago uso del archivo utils.h generado por el Prof. Pedro Pérez
* Comando para compilar en Linux: gcc nilikantha.c
* Comando para correr en Linux: ./a.out
* NOTA: De especificar otro nombre del ejecutable al compilar utilizar ./nombreDelEjecutable.out
*--------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define SIZE 1000000000 // 1e9

/**
 * @brief This function implements the Nilikantha series up to a given n (size), this to 
 * give an approximation of Pi. With a larger n, the approximation is more precise.
 * 
 * @param size int
 * @return double 
 */
double nilik(int size){
    double result = 3.0;
    double sign, di, denominator, term;
    int i = 1;
    for(i; i <= size; i++){
        sign = i % 2 == 0 ? -1.0 : 1.0;
        di = i*2.0;
        denominator = (di*(di+1)*(di+2));
        term = (4.0*sign)/denominator;
        result += term;
    }
    return result;
}

int main(int argc, char * argv[]){
    int size = SIZE, i = 0;
    double result = 0.0, time = 0.0;
    if(argc >= 2){
        printf("Error: No arguments are allowed\n");
        return -1;
    }
    printf("Starting...\n");
    for (i = 0; i < N; i++) {
		start_timer();

		result = nilik(size);

		time += stop_timer();
	}
    printf("Pi is approx: %.15lf \n", result);
    printf("Average time elapsed: %.7lf ms\n", (time / N));
    return 0;
}