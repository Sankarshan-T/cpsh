#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    long seconds = time(0);
    srand(seconds);
    int randomNo {rand() % 10};

    cout << randomNo;
    return 0;
}