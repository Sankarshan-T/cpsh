#include <iostream>

int main() {
    // silly thing i found on the internet
    int a = 1;
    int b = 2;
    int temp = a;
    
    a = b;
    b = temp;

    std::cout << a;

    return 0;
}