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
#include "../inc/core/add.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        krypton_ui();
        return 0;
    }

    string command = argv[1];
    string parsed_command = parse(command);

    // Using Enum for Command Types

    enum CommandType
    {
        CMD_INIT,
        CMD_HASH,
        CMD_ADD,
        CMD_UNKNOWN
    };

    // Convert string command to enum

    CommandType cmd;
    if (parsed_command == "init") cmd = CMD_INIT;
    else if (parsed_command == "hash") cmd = CMD_HASH;
    else if (parsed_command == "add") cmd = CMD_ADD;
    else cmd = CMD_UNKNOWN;

    // Switch on command type

    switch (cmd)
    {
        case CMD_INIT:
            init_repo();
            break;

        case CMD_HASH:
            if (argc < 3)
            {
                log_error("Usage --> krypton hash <file>");
                return 1;
            }
            {
                string hash = sha1_hash(argv[2]);
                log_info("Hash --> " + hash);
            }
            break;

        case CMD_ADD:
            if (argc < 3)
            {
                log_error("Usage --> krypton add <file>");
                return 1;
            }
            add_file(argv[2]);
            break;

        default:
            log_error("Unknown Command --> " + parsed_command);
            return 1;
    }

    return 0;
}