#include <iostream>
#include <string>
#include <windows.h>

#include "parser.h"

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
    string input;

    while (true)
    {
        cout << "cpsh$ ";

        setColor(Color::Yellow);
        getline(cin, input);
        setColor(Color::White);

        ParsedCommand parsed = parseCommand(input);

        if (parsed.command == "exit")
        {
            coloredMessage(Color::Green, "Exiting cpsh...");
            break;
        }

        if (parsed.command == "help")
        {
            coloredMessage(Color::Cyan, "All available commands:");
            cout << "   > help - to show this message\n";
            cout << "   > clear - to clear the terminal\n";
            cout << "   > exit - to exit cpsh\n";
            continue;
        }

        if (parsed.command == "clear")
        {
            coloredMessage(Color::Green, "Clearing...");
            system("cls");
            continue;
        }

        if (parsed.command == "echo")
        {
            coloredMessage(Color::Cyan, parsed.arguments);
            continue;
        }

        coloredMessage(Color::Red, "Unknown command");
        setColor(Color::White);
    }

    return 0;
}