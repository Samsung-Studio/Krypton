/*----------------------------------------------------------------------*
 *                         VERSION CONTROL LOGIC                        *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages the version control system, including initialization,
    configuration, and core operations.

------------------------------------------------------------------------*/

#include <iostream>
#include <filesystem>

#include "../inc/utils/file.h"
#include "../inc/core/vcs.h"
#include "../inc/utils/logger.h"

using namespace std;
using namespace std::filesystem;

//  Function Definitions -->

void init_repo()
{
    if (filesystem::exists(".krypton"))
    {
        cout << "\nRepository Already Initialized !" << endl;
        return;
    }
    
    // Create .krypton Directory Structure

    create_dir(".krypton");
    create_dir(".krypton/objects");
    create_dir(".krypton/refs");

    // Create Metadata Files

    create_file(".krypton/HEAD", "ref: refs/heads/main\n");
    create_file(".krypton/index", "");

    log_info("Initialized Empty Krypton Repository !");
    cout << "\nInitialized Empty Repository !" << endl;
}