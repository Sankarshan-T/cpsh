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

void coloredMessage(Color color, const string &message)
{
    setColor(color);
    cout << message << "\n";
    setColor(Color::White);
}

int main()
{
    string command;

    while (true)
    {
        cout << "cpsh$ ";

        setColor(Color::Yellow);
        getline(cin, command);
        setColor(Color::White);

        if (command == "exit")
        {
            coloredMessage(Color::Green, "Exiting cpsh...");
            break;
        }

        if (command == "help")
        {
            coloredMessage(Color::Cyan, "All available commands:");
            cout << "   > help - to show this message\n";
            cout << "   > clear - to clear the terminal\n";
            cout << "   > exit - to exit cpsh\n";
            continue;
        }

        if (command == "clear")
        {
            coloredMessage(Color::Green, "Clearing...");
            system("cls");
            continue;
        }

        coloredMessage(Color::Red, "Unknown command");
        setColor(Color::White);
    }

    return 0;
}