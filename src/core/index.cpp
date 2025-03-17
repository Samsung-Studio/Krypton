/*----------------------------------------------------------------------*
 *                               INDEX                                  *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages the staging area, tracks changes before committing.

------------------------------------------------------------------------*/

#include "../inc/core/index.h"

#include <fstream>
using namespace std;

void updateIndex(const string& filename, const string& hash)
{
    ofstream indexFile(".krypton/index", ios::app); // Append to Index file
    indexFile << filename << " " << hash << "\n";   // Write Filename and Hash To Index File
    indexFile.close();                              // Close Index File
}