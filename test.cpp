#include <iostream>

using namespace std;

int main() {
    cout << "Enter temperature in Fahrenheit:  ";
    double temperature;
    cin >> temperature;
    cout << "Temperature in celcius: " << (temperature - 32) * 0.5555; 
    return 0;
}