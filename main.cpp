#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "commands.h"
#include "parser.h"

using namespace std;

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