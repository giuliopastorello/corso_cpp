//Scrivi una funzione gcd che prende due int e calcola e ritorna il massimo comune divisore tra i due numeri usando l'algoritmo di Euclide
//Variante 2. Implementa la funzione in forma ricorsiva.
#include <iostream>

using namespace std;

int gcd (int a, int b)
{
    if (b == 0){
        return a;
    } else {
        return gcd (b, a % b);
    }
}
int main ()
{
    int num1, num2;

    cout << "primo numero (intero): ";
    cin >> num1;
    cout << "secondo umero (intero): ";
    cin >> num2;
    cout << "MCD fra " << num1 << " e " << num2 << " = " << gcd (num1, num2) << endl;
    return 0;
}