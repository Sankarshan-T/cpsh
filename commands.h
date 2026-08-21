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

void setColor(Color color);

void coloredMessage(Color color, const std::string &message);

void printWorkingDirectory();

void changeDirectory(const std::string &path);

void printHelp();

void printBanner();

void executeCommands(
    const string &command,
    const string &argumens,
    vector<string> &history);