#include "GSS.h"
#include <cmath>
#include <stdexcept>

double GSS(double (*func)(double x), double a, double b, const double ERROR, int& iterCounter) {
    if(func(a) * func(b) > 0) throw std::runtime_error("Invalid bounds");

    while(std::abs(b-a) > ERROR) {
        double c = a + 0.618*(b-a);
        if(func(a) * func(c) <= 0) b = c;
        else a = c;
        iterCounter++;
    }

    return a;
}
