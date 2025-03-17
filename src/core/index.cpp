/*----------------------------------------------------------------------*
 *                               INDEX                                  *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages the staging area, tracks changes before committing.

------------------------------------------------------------------------*/

#include "../inc/core/index.h"

#include <fstream>
#include <sstream>

using namespace std;

void updateIndex(const string& filepath, const string& hash)
{
    // Read existing index
    ifstream index_read(".krypton/index");
    stringstream index_content;
    string line;
    bool file_already_staged = false;

    // Check for existing entries
    while (getline(index_read, line))
    {
        size_t space_pos = line.find(' ');
        if (space_pos != string::npos)
        {
            string existing_path = line.substr(space_pos + 1);
            if (existing_path != filepath)
            {
                index_content << line << '\n';
            }
            else
            {
                index_content << hash << ' ' << filepath << '\n';
                file_already_staged = true;
            }
        }
    }
    index_read.close();

    // Add new entry if file wasn't already in index
    if (!file_already_staged)
    {
        index_content << hash << ' ' << filepath << '\n';
    }

    // Write back to index
    ofstream index_write(".krypton/index");
    index_write << index_content.str();
    index_write.close();
}