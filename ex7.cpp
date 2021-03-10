//Scrivi una funzione che calcola la soluzione di un'equazione di primo grado ax+b=0ax + b = 0ax+b=0, dati i due coefficienti.

#include <iostream>

using namespace std;

int main()
{
    double a, b;
    cout << "inserire il coefficiente di primo grado: ";
    cin >> a;
    cout << "Inserire il termine noto: ";
    cin >> b;
    cout << "x = " << -(b / a) << endl;
    return 0;
}

