#include <iostream>
#include <math.h>

using namespace std;
const double epsilon = 0.001;   ///погршность
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

///просто фунцкция для метода комбинированных хорд
double x(double x){
    return x*x*x + 3*x*x - 3;
}

///функция первой производной
double diff(double x){
    return 3*x*x + 6*x;
}


///функция второй производной
double sqrtDiff(double x){
    return 6*x + 6;
}

///подсчитаыем корни методом комбинированных хорд
double mixChord(double a, double b){
    double aver = (a + b)/2;
    if (diff(aver) * sqrtDiff(aver) < 0){   ///определяем приближение метода комбинированных хорд(с избытком или с недостатком)
        while (b - a > epsilon){
            b = a - (x(a)*(b - a))/(x(b) - x(a));
            a = a - x(a)/diff(a);
        }
    }   else {
        while (b - a > epsilon){
            a = a - (x(a)*(b - a))/(x(b) - x(a));
            b = b - x(b)/diff(b);
        }
    }
    return a;
}

int main() {

    cout << "Chord method\n";
    cout << chord(a)<<endl;    /// рассматриваем промежуток от 1 до 2
    cout <<"\nCombinated chord method\n";
    cout << mixChord(-3, -2)<<endl;    ///рассматриваем интервалы [-3;-2], [-2;-1], [0;1]
    cout << mixChord(-2, -1)<<endl;
    cout << mixChord(0, 1);
    return 0;
}
