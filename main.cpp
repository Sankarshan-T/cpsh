#include <iostream>
#include <string>
#include <vector>
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

void printWorkingDirectory()
{
    char currentPath[MAX_PATH];

    if (GetCurrentDirectoryA(MAX_PATH, currentPath))
    {
        cout << "Current Directory: ";
        coloredMessage(Color::Green, currentPath);
    }
    else
    {
        coloredMessage(Color::Red, "Ooof! couldn't get current directory.");
    }
}

void changeDirectory(const string &path)
{
    if (SetCurrentDirectoryA(path.c_str()))
    {
        coloredMessage(Color::Green, "Changed directory!");
    }
    else
    {
        coloredMessage(Color::Red, "Directory not found.");
    }
}

void printHelp()
{
    coloredMessage(Color::Cyan, "CPSH commands:");
    cout << "   > help - to show this message\n";
    cout << "   > home - to open shell home\n";
    cout << "   > clear - to clear the terminal\n";
    cout << "   > echo - to print something in the terminal\n";
    cout << "   > history - to print previously used commands\n";
    cout << "   > pwd - to print the current working directory\n";
    cout << "   > cd - to change the working directory in the terminal\n";
    cout << "   > exit - to exit cpsh\n";
    cout << "\n";
}

void printBanner()
{
    system("cls");
    coloredMessage(Color::Cyan, R"(
            ╔█████ ╔██████ ╔█████ ╔██ ╔██
            ║██    ║██  ██ ║██    ║██ ║██
            ║██    ║██████ ║█████ ║██████
            ║██    ║██     ╚═══██ ║██═╗██
            ║█████ ║██     ╔█████ ║██ ║██
            ╚════╝ ╚═╝     ╚════╝ ╚═╝ ╚═╝
                  C++ Command Line
    )");
    printHelp();
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("cls");

    printBanner();

    string input;
    vector<string> commandHistory;

    while (true)
    {
        cout << "cpsh$ ";

        setColor(Color::Yellow);
        getline(cin, input);
        setColor(Color::White);

        if (!input.empty())
        {
            commandHistory.push_back(input);
        }

        ParsedCommand parsed = parseCommand(input);

        if (parsed.command == "exit")
        {
            coloredMessage(Color::Green, "Exiting cpsh...");
            break;
        }
        if (parsed.command == "home")
        {
            printBanner();
            continue;
        }

        if (parsed.command == "help")
        {
            printHelp();
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
            if (parsed.arguments.empty())
            {
                coloredMessage(Color::Yellow, "echo command cannot be empty!, echo <message>");
                continue;
            }
            coloredMessage(Color::Cyan, parsed.arguments);
            continue;
        }

        if (parsed.command == "pwd")
        {
            printWorkingDirectory();
            continue;
        }

        if (parsed.command == "cd")
        {
            if (parsed.arguments.empty())
            {
                coloredMessage(Color::Yellow, "cd command cannot be empty!, enter a directory path, cd <message>");
                continue;
            }
            changeDirectory(parsed.arguments);
            continue;
        }
        if (parsed.command == "history")
        {
            if (commandHistory.empty())
            {
                coloredMessage(Color::Yellow, "No commands in history!");
            }
            for (size_t i = 0; i < commandHistory.size(); i++)
            {
                cout << "  " << i + 1 << ".  " << commandHistory[i] << "\n";
            }
            continue;
        }

        coloredMessage(Color::Red, "Unknown command");
        setColor(Color::White);
    }

    return 0;
}