#include <iostream>
#include <iomanip>
#include "utils.h"

#define SIZE 1000000000

using namespace std;

class Nilikantha {
private:
    int size;

    double result;

public:
    Nilikantha(int s) : size(s) {}

    double getResult() {
        return this->result;
    }

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
    if (argc > 2) {
        cout << "No arguments are allowed" << endl;
        return -1;
    }
    Nilikantha nik(size);
    for (i = 0; i < N; i++) {
        start_timer();
        
        nik.calculate();

        time += stop_timer();
    }
    cout << "Pi is approx: " << setprecision(15) << nik.getResult() << endl;
    cout << "Time elapsed: " << setprecision(15) << (time / N) << " ms" << endl;
    return 0;
}