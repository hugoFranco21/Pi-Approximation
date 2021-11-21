/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje C++. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está de forma secuencial.
    Hago uso del archivo utils.h generado por el Prof. Pedro Pérez
* Comando para compilar en Linux: g++ nilikantha.cpp
* Comando para correr en Linux: ./a.out
* NOTA: De especificar otro nombre del ejecutable al compilar utilizar ./nombreDelEjecutable.out
*--------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
#include "utils.h"

#define SIZE 1000000000 //1e9

using namespace std;

class Nilikantha {
private:
    int size;

    double result;

public:
    /**
     * @brief Construct a new Nilikantha object
     * 
     * @param s int
     */
    Nilikantha(int s) : size(s) {}

    /**
     * @brief Get the result value from the Nilikantha object
     * 
     * @return double 
     */
    double getResult() {
        return this->result;
    }

    /**
     * @brief This function does the calculation of the Nilikantha series up to the size defined
     * in the object constructor.
     * 
     */
    void calculate() {
        result = 3.0;
        double sign, di, denominator, term;
        int i = 1;
        for (i; i <= size; i++) {
            sign = i % 2 == 0 ? -1.0 : 1.0;
            di = i * 2.0;
            denominator = (di * (di + 1) * (di + 2));
            term = (4.0 * sign) / denominator;
            result += term;
        }
    }
};

int main(int argc, char *argv[]) {
    int size = SIZE, i = 0;
    double result = 0.0, time = 0.0;
    if (argc >= 2) {
        cout << "Error: No arguments are allowed" << endl;
        return -1;
    }
    cout << "Starting..." << endl;
    Nilikantha nik(size);
    for (i = 0; i < N; i++) {
        start_timer();
        
        nik.calculate();

        time += stop_timer();
    }
    cout << "Pi is approx: " << setprecision(15) << nik.getResult() << endl;
    cout << "Average time elapsed: " << setprecision(15) << (time / N) << " ms" << endl;
    return 0;
}