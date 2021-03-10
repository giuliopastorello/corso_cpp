//Scrivi una funzione is_prime che prende un int e indica se il numero è primo.

#include <iostream>

using namespace std;

int prime (int n) {
    for (int i = 2; i < n / 2; i++) {
        if (n % i == 0) {
            return 1;
        }
        return 0;
    }
}

int main()
{
    int num, flag = 0;
    cout << "Enter number to check wether it's a prime: ";
    cin >> num;

    flag = prime (num);

    if (flag == 0){
        cout << "The number is prime"; 
    } else {
        cout << "The number is not prime";
    }
    return 0;
}