#include <iostream>

using namespace std;

int main()
{
    int num1, num2, num3;
    cout << "Inserire il primo numero: ";
    cin >> num1;
    cout << "Inserire il secondo numero: ";
    cin >> num2;
    cout << "Inserire il terzo numero: ";
    cin >> num3;

    if (num1 >= num2 && num1 >= num3){
        cout << "il numero maggiore è: " << num1;
    } else if (num2 >= num1 && num2 >= num3){
        cout << "il numero maggiore è: " << num2;
    } else {
        cout << "il numero maggiore è: " << num3;
    }    

    return 0;
}