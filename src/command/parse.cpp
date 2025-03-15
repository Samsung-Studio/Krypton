/*----------------------------------------------------------------------*
 *                             PARSE                                    *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Parses command-line arguments and configuration files.

------------------------------------------------------------------------*/

#include "../inc/command/parse.h"
#include <string>

using namespace std;

string parse(string command)
{
    for(char& c : command)
    {
        c = tolower(c);
    }
    return command;
}