#pragma once

#include <string>
#include <vector>

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

// Sets the color to the colored message
void setColor(Color color);

// A simple helper i made to get texts in different colors using the above void.
void coloredMessage(Color color, const std::string &message);

// void for the pwd command
void printWorkingDirectory();

// void for the cd command (obv)
void changeDirectory(const std::string &path);

// void for the help command (made a separate command cuz i wanted to ruse ths in many places)
void printHelp();

// silly thing for the home screen like the cpsh logo i made using ascii art pff
void printBanner();

// void for the ls command thingi
void listDirectory();

// the goat to run all the above commands!!!!
void executeCommands(
    const string &command,
    const string &argumens,
    vector<string> &history);