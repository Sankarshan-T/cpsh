#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

enum class Color
{
    White = 7,
    Green = 10,
    Yellow = 14,
    Red = 12,
    Cyan = 11,
    Gray = 8
};

void setColor(Color color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        static_cast<int>(color));
}

int main()
{
    string command;

    while (true)
    {
        setColor(Color::White);
        cout << "cpsh$ ";
        setColor(Color::Yellow);
        getline(cin, command);
        setColor(Color::White);

        if (command == "exit")
        {
            setColor(Color::Green);
            cout << "Extiting....\n"
                 << "Exited!";

            setColor(Color::White);
            break;
        }

        if (command == "help")
        {
            setColor(Color::Cyan);
            cout << "All available commands:\n";
            setColor(Color::White);
            cout << "   > help - to show this message\n";
            cout << "   > clear - to clear the teminal\n";
            cout << "   > exit - to exit cpsh\n";
            continue;
        }

        if (command == "clear")
        {
            setColor(Color::Green);
            cout << "Extiting....";
            setColor(Color::White);
            system("cls");
            continue;
        }

        setColor(Color::Red);
        cout << "Unknown Command: " << command << '\n';
        setColor(Color::White);
    }

    return 0;
}