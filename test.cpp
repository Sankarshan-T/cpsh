#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double input1, input2;
    cout << "Enter 2 numbers: ";
    cin >> input1 >> input2;
    double result = pow(input1, input2);
    cout << result;
    return 0;
}