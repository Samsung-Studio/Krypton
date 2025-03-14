/*----------------------------------------------------------------------*
 *                               FILE                                   *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages file operations, including reading, writing, and managing
    file paths.

------------------------------------------------------------------------*/

#include <fstream>
#include <filesystem>
#include <string>

#include "../inc/utils/file.h"

using namespace std;
using namespace std::filesystem;

void create_file(const string& path, const string& content)
{
    ofstream file(path);
    file << content;
    file.close();
}

void create_dir(const string& path)
{
    if (!exists(path))
    {
        filesystem::create_directory(path);
    }
}