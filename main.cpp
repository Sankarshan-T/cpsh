#include <iostream>
#include <string>

using namespace std;

int main()
{
    string command;

    while (true)
    {
        cout << "cpsh$ ";
        getline(cin, command);

        if (command == "exit")
        {
            cout << "Extiting....\n"
                 << "Exited!";
            break;
        }

        if (command == "help")
        {
            cout << "All available commands:\n";
            cout << "   > help - to show this message\n";
            cout << "   > clear - to clear the teminal\n";
            cout << "   > exit - to exit cpsh\n";
            continue;
        }

        if (command == "clear")
        {
            system("cls");
            continue;
        }

        cout << "Unknown Command: " << command << '\n';
    }

    return 0;
}