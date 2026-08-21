#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
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

void calculate(const string &expression)
{
    stringstream stream(expression);

    double firstNumber;
    double secondNumber;
    char operation;

    if (!(stream >> firstNumber >> operation >> secondNumber))
    {
        coloredMessage(
            Color::Yellow,
            "Wrong usage! Correct usage: calc <number> <operator> <number>");
        return;
    }

    double result;

    switch (operation)
    {
    case '+':
        result = firstNumber + secondNumber;
        break;

    case '-':
        result = firstNumber - secondNumber;
        break;

    case '*':
        result = firstNumber * secondNumber;
        break;

    case '/':
        if (secondNumber == 0)
        {
            coloredMessage(Color::Red, "Error: Cannot divide by zero.");
            return;
        }

        result = firstNumber / secondNumber;
        break;

    default:
        coloredMessage(Color::Yellow, "Unknown operator.");
        return;
    }

    cout << "= ";
    coloredMessage(Color::Green, to_string(result));
}

void createFile(const string &filename)
{
    namespace fs = filesystem;

    try
    {
        fs::path filepath = fs::current_path() / filename;

        if (fs::exists(filepath))
        {
            coloredMessage(Color::Yellow, "File already exists lol.");
            return;
        }

        ofstream file(filepath);

        if (file)
        {
            coloredMessage(Color::Green, "File created!");
        }
        else
        {
            coloredMessage(Color::Red, "Could not create file.");
        }
    }
    catch (const fs::filesystem_error &error)
    {
        coloredMessage(Color::Red, "Couldn't creating file.");
    }
}

void readFile(const std::string &filename)
{
    ifstream file(filename);

    if (!file)
    {
        coloredMessage(Color::Red, "Couldnt open file");
        return;
    }
    string line;

    while (getline(file, line))
    {
        cout << line << "\n";
    }
}

void removeFile(const std::string &filename)
{
    namespace fs = filesystem;

    try
    {
        fs::path filepath = fs::current_path() / filename;

        if (!fs::exists(filepath))
        {
            coloredMessage(Color::Red, "File not found.");
            return;
        }
        if (fs::is_directory(filepath))
        {
            coloredMessage(
                Color::Yellow,
                "That is a directory..... remove only deletes files.");
            return;
        }

        if (fs::remove(filepath))
        {
            coloredMessage(Color::Green, "File removed!");
        }
        else
        {
            coloredMessage(Color::Red, "Could not remove file.");
        }
    }
    catch (const fs::filesystem_error &error)
    {
        coloredMessage(Color::Red, "Error occured while removing the file....");
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
    cout << "   > touch - to create a file in the current directory\n";
    cout << "   > cat - to read the contents of a file\n";
    cout << "   > calc - to perform operations with numbers\n";
    cout << "   > rf - to remove a file from the working directory\n";
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