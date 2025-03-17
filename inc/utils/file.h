/*----------------------------------------------------------------------*
 *                            FILE HEADER                               *
 *----------------------------------------------------------------------*/

#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

void create_file(const string& path, const string& content);
void create_dir(const string& path);
void storeBlob(const string& hash, const string& content);

#endif