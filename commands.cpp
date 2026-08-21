#include <iostream>
#include <filesystem>
#include <windows.h>

#include "commands.h"

using namespace std;

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
        cout << "Current Directory";
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

void listDirectory()
{
    namespace fs = filesystem;

    try
    {
        for (const auto &entry : fs::directory_iterator(fs::current_path()))
        {
            if (entry.is_directory())
            {
                setColor(Color::Cyan);
                cout << "DIR>  " << entry.path().filename().string() << "\n";
            }
            else
            {
                setColor(Color::White);
                cout << "FILE> " << entry.path().filename().string() << "\n";
            }
        }
    }
    catch (const fs::filesystem_error &error)
    {
        coloredMessage(Color::Red, "Error: Could not list directory.");
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
    cout << "   > ls - to list directories and files under the current dir\n";
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