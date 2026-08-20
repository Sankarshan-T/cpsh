#include <iostream>
#include <string>

using namespace std;

int main()
{
    string command;

    while (true)
    {
        cout << "cpsh> ";
        getline(cin, command);

        if (command == "exit")
        {
            cout << "Extiting....";
            break;
        }

        cout << "Command: " << command << '\n';
    }

    return 0;
}