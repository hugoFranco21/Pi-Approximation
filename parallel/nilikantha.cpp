/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje C++. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está paralelizado, utilizando la tecnología de Intel Thread Building Blocks.
    Hago uso del archivo utils.h generado por el Prof. Pedro Pérez
* Comando para compilar en Linux: g++ nilikantha.cpp -ltbb
* Comando para correr en Linux: ./a.out
* NOTA: De especificar otro nombre del ejecutable al compilar utilizar ./nombreDelEjecutable.out
*--------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include "utils.h"

const int SIZE = 1000000000; //1e9

using namespace std;
using namespace tbb;

class Nilikantha {
private:
	double result;

public:
	/**
	 * @brief Construct a new Nilikantha object. Result is initialized with 3.0 because this is 
	 * the first Nilikantha object, which corresponds to the first term of the 
	 * Nilikantha series.
	 * 
	 */
	Nilikantha() : result(3.0) {}

	/**
	 * @brief Construct a new Nilikantha object. Result is initialized with 0.0 because every
	 * subsequent Nilikantha objects do not need to know about the beginning of the series.
	 * The range for the calculation of Pi begins at the term 1, not 0.
	 * 
	 * @param x 
	 */
	Nilikantha(Nilikantha &x, split): result(0.0) {}

	/**
	 * @brief Getter for the result member variable
	 * 
	 * @return double 
	 */
	double getResult() const {
		return result;
	}

	/**
	 * @brief Operation definition to be performed on every element
	 * within the range defined by . In this case, it is obtaining the nth
	 * element of the Nilikantha series from r.begin to r.end, and adding it
	 * to the class variable result
	 * 
	 * @param r blocked_range<int>
	 */
	void operator() (const blocked_range<int> &r) {
        double sign, di, denominator, term;
		for (int i = r.begin(); i != r.end(); i++) {
			sign = i % 2 == 0 ? -1.0 : 1.0;
            di = i * 2.0;
            denominator = (di * (di + 1) * (di + 2));
            term = (4.0 * sign) / denominator;
            result += term;
		}
	}

	/**
	 * @brief Reduce operation to be performed
	 * 
	 * @param x Nilikantha
	 */
	void join(const Nilikantha &x) {
		result += x.result;
	}
};

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        cout << "Error: No arguments are allowed" << endl;
        return -1;
    }
	double result = 0.0;
	double ms;

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 1; i <= N; i++) {
		start_timer();
		/**
		 * @brief Creation of the first object
		 * 
		 */
		Nilikantha obj;
		/**
		 * @brief Using Intel's tbb, parallel reduction is performed from
		 * 1 to SIZE for the object defined previously, this executes
		 * operator() and calls the join function defined in the class.
		 * 
		 */
		parallel_reduce(blocked_range<int>(1, SIZE), obj);
		result = obj.getResult();

		ms += stop_timer();
	}
	cout << "Pi is approx: " << setprecision(15) << (double)(result) << endl;
    cout << "Average time elapsed: " << setprecision(15) << (ms / N) << " ms" << endl;

	return 0;
}
