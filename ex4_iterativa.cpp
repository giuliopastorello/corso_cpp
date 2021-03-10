//Scrivi una funzione gcd che prende due int e calcola e ritorna il massimo comune divisore tra i due numeri usando l'algoritmo di Euclide
//Variante 1. Implementa la funzione in forma iterativa.

#include <iostream>

using namespace std;

int euclide (int a, int b) //baby algo di euclide 
{
    int r;
    while (b != 0) //da ripetere finché b non diventa 0 
    {
        r = a % b;//a mod b = resto della divisione
        a = b;
        b = r;//scambio di ruolo fra a e b
    }
    return a;//quando b = 0 => MCD = a
}

int main()
{
    int num1, num2;

    cout << "primo numero (intero): ";
    cin >> num1;
    cout << "secondo numero (intero): ";
    cin >> num2;
    cout << euclide (num1, num2);
    return 0;
}