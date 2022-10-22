#include <iostream>
#include <math.h>
#include "GSS.h"

using namespace std;
const double epsilon = 0.0001;   ///погршность
const double a = 1; ///начало интеравла для метода хорд
const double b = 2; ///конец интервала для метода хорд


///функция для метода хорд
double func(double x){
    return 1/tan(x) - x/4;
}

///метод для подсчета ответа методом хорд
double chord(double x){
    double pastX = 0;
    while (abs(func(x)) > epsilon || abs(x - pastX) > epsilon){
        pastX = x;
        x = pastX - func(pastX)* func(b - pastX)/(func(b) - func(pastX));
    }
    return x;
}

///далее идут все функции для метода комбинированных хорд

///просто фунцкция для метода комбинированных хорд
double x(double x){
    return x*x*x + 3*x*x - 3;
}

///функция для нахождения производной первого порядка 
double diff(double x){
    return 3*x*x + 6*x;
}


///функция для нахождения производной второго порядка
double sqrtDiff(double x){
    return 6*x + 6;
}

///подсчитаыем корни методом комбинированных хорд
double mixChord(double a, double b){
    double aver = (a + b)/2;
    if (diff(aver) * sqrtDiff(aver) < 0){   ///определяем приближение метода комбинированных хорд(с избытком или с недостатком)
        while (abs(b - a) > epsilon){
            b = a - (x(a)*(b - a))/(x(b) - x(a));
            a = a - x(a)/diff(a);
        }
    }   else {
        while (abs(b - a) > epsilon){
            a = a - (x(a)*(b - a))/(x(b) - x(a));
            b = b - x(b)/diff(b);
        }
    }
    return a;
}


double halfDivision(double a, double b){
    double c;
    while (abs(a - b) > epsilon ){
            c = (a + b)/2;
        if (x(a)*x(c) < 0)
            b = c;
        else a = c;
    }
    return a;
}

int main() {

    cout << "Chord method\n";
    cout << chord(a)<<endl;    /// рассматриваем промежуток от 1 до 2

    cout <<"\nCombinated chord method\n";
    cout << mixChord(-3, -2)<<endl;    ///рассматриваем интервалы [-3;-2], [-2;-1], [0;1]
    cout << mixChord(-2, -1)<<endl;
    cout << mixChord(0, 1) << endl;

    cout <<"\nHalf division method\n";
    cout << halfDivision(-3, -2) << endl; ///рассматриваем интервалы [-3;-2], [-2;-1], [0;1]
    cout << halfDivision(-2, -1) << endl;
    cout << halfDivision(0, 1) << endl;

    cout << "\nGolden section method\n";
    int iter = 0;
    cout << GSS(x, -3, -2, epsilon, iter)<<endl;
    cout << GSS(x, -2, -1, epsilon, iter)<<endl;
    cout << GSS(x, 0, 1, epsilon, iter)<<endl;
    return 0;
}
