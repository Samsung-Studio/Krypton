/*----------------------------------------------------------------------*
 *                              KRYPTON                                 *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Main Entry Point For The Krypton Version Control System.

------------------------------------------------------------------------*/

#include <iostream>
#include "../inc/command/ui.h"
#include "../inc/core/vcs.h"
#include "../inc/utils/logger.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        krypton_ui();
    }

    string command = argv[1];

    if (command == "init")
    {
        init_repo();
    }
}