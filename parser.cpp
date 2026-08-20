#include "parser.h"

using namespace std;

ParsedCommand parseCommand(const string &input)
{
    ParsedCommand result;

    size_t space = input.find(' ');

    if (space == string::npos)
    {
        result.command = input;
        result.arguments = "";
    }
    else
    {
        result.command = input.substr(0, space);
        result.arguments = input.substr(space + 1);
    }

    return result;
}