#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define SIZE 1000000000

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
    if(argc > 2){
        printf("No arguments are allowed\n");
        return -1;
    }
    for (i = 0; i < N; i++) {
		start_timer();

		result = nilik(size);

		time += stop_timer();
	}
    printf("Pi is approx: %.15lf \n", result);
    printf("Time elapsed: %.7lf ms\n", (time / N));
    return 0;
}