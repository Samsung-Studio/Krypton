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
#include "../inc/command/parse.h"
#include "../inc/core/hash.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        krypton_ui();
    }

    string command = argv[1];

    string parsed_command = parse(command);

    if (parsed_command == "init")
    {
        init_repo();
    }
    else if (parsed_command == "hash")
    {
        // If no file is provided, print usage
        if (argc < 3)
        {
            log_error("Usage --> krypton hash <file>");
            return 1;
        }
        
        string hash = sha1_hash(argv[2]);
        log_info("Hash --> " + hash);
    }
}