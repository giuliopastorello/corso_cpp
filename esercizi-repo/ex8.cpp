#include <iostream>
#include <cmath>

using namespace std;

int Stri (int l1, int l2, int l3)
{
    double p = (l1 + l2 + l3) / 2; 
    double arg = p * (p - l1) * (p - l2) * (p - l3); 
    return sqrt (arg);
}

int Ptri (double l1, double l2, double l3)
{
    return l1 + l2 + l3;
}

int Ssq (double l)
{
    return l * l;
}

int Psq (double l)
{
    return 4 * l;
}

int Scu (double l)
{
    return 6 * l * l;
}

int Acu (double l)
{
    return l * l * l;
}

int main()
{
    int shape, request;
    int s1, s2, s3;
    double s;

    cout << "Choose between 1)Triangle, 2)Square or 3)Cube: ";
    cin >> shape;

    if (shape == 1) {
        cout << "Enter side 1: ";
        cin >> s1;
        cout << "Enter side 2: ";
        cin >> s1;
        cout << "Enter side 3: ";
        cin >> s3;
        cout << "Do you want to compute 1)Surface or 2)Perimeter: ";
        cin >> request;
            if (request == 1) {
                cout << "The surface of the triangle is: " << Stri (s1, s2, s3) << endl;
            } else if (request == 2) {
                cout << "The perimeter of the triangle is: " << Ptri (s1, s2, s3) << endl;
            } else {
                cout << "Invalid input: try again";
            }
    } else if (shape == 2 || shape == 3) {
        cout << "Enter side: ";
        cin >> s;
            if (shape == 2){
                cout << "Do you want to compute 1)Surface or 2)Perimeter: ";
                cin >> request;
                    if (request == 1) {
                        cout << "The surface of the square is: " << Ssq (s) << endl;
                    } else if (request == 2) {
                        cout << "The perimeter of the square is: " << Psq (s) << endl;
                    } else {
                        cout << "Invalid input: try again";
                    }
            } else if (shape == 3) {
                cout << "Do you want to compute 1)Surface or 2)Area: ";
                cin >> request;
                    if (request == 1) {
                        cout << "The surface of the cube is: " << Scu (s) << endl;
                    } else if (request == 2) {
                        cout << "The area of the cube is: " << Acu (s) << endl;
                    } else {
                        cout << "Invalid input: try again";
                    }
            } 
    } else {
        cout << "Invalid input: try again.";
        cin >> shape;
    }
    return 0;
}