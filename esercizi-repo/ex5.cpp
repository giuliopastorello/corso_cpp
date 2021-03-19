//Scrivi una funzione lcm che prende due int e calcola e ritorna il minimo comune multiplo tra i due numeri.

#include <iostream>

using namespace std;

int lcm (int a, int b)
{
    for (int i = 1; i < b; i++) {
        if (((a * i) % b) == 0) {
            return a * i;
        }
    } return a * b;
}

int main()
{
    int num1, num2;
    
    cout << "primo numero (intero): ";
    cin >> num1;
    cout << "secondo numero (intero): ";
    cin >> num2;
    
    cout << "il mcm tra " << num1 << " e " << num2 << " = " << lcm (num1, num2) << endl;
    
    return 0;
}