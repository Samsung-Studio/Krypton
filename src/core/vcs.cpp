/*----------------------------------------------------------------------*
 *                         VERSION CONTROL LOGIC                        *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages the version control system, including initialization,
    configuration, and core operations.

------------------------------------------------------------------------*/

#include <iostream>
#include <filesystem>
#include <fstream>

#include "../inc/utils/file.h"
#include "../inc/core/vcs.h"
#include "../inc/utils/logger.h"
#include "../inc/core/hash.h"
#include "../inc/core/index.h"

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
}

void add_file(const string& path)
{
    if (!filesystem::exists(path))
    {
        log_error("File Does Not Exist !");
        return;
    }

    // Read File Content
    ifstream file(path);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    string hash = sha1_hash(content);   // Generate SHA1 Hash
    storeBlob(hash, content);           // Store Blob
    updateIndex(path, hash);            // Update Index

    log_info("File Added To Stage Area !");
}