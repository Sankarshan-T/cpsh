#pragma once

#include <string>

using namespace std;

struct ParsedCommand
{
    string command;
    string arguments;
};

ParsedCommand parseCommand(const string &input);