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
#include <sstream>

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
        log_info("Repository Already Initialized !");
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

void add_file(const string& filepath)
{
    if (!exists(".krypton"))
    {
        log_error("Not A Krypton Repository (Or Any Parent Up To Mount Point /)");
        return;
    }

    if (!exists(filepath))
    {
        log_error("Pathspec '" + filepath + "' Did Not Match Any Files !");
        return;
    }

    // Get file hash
    string hash = sha1_hash(filepath);
    if (hash.empty())
    {
        return; // Error already logged by sha1_hash
    }

    // Create object directory structure (using first 2 chars as directory)
    string dir_path = ".krypton/objects/" + hash.substr(0, 2);
    string object_path = dir_path + "/" + hash.substr(2);
    
    // Check if blob already exists
    if (exists(object_path))
    {
        log_error("File '" + filepath + "' Is Already Stored In The Repository !");
        return;
    }

    // Create directory if it doesn't exist
    create_dir(dir_path);

    try
    {
        // Copy file to objects
        filesystem::copy_file(filepath, object_path, filesystem::copy_options::overwrite_existing);
        
        // Update the index
        updateIndex(filepath, hash);
        
        log_info("Added File --> " + filepath + " To Stage Area !");
    }
    catch (const filesystem::filesystem_error& e)
    {
        log_error("Failed To Stage File !");
        return;
    }
}