/*----------------------------------------------------------------------*
 *                               HASH                                   *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages cryptographic hash functions, including SHA-1 and SHA-256.

------------------------------------------------------------------------*/

#include "../inc/core/hash.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

string sha1_hash(const string &file_path)
{
    // Open file in binary mode
    ifstream file(file_path, ios::binary);
    if (!file) {
        cerr << "Cannot open file: " << file_path << endl;
        return "";
    }

    // Read file content
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    file.close();

    // Create SHA1 hash
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(content.c_str()), content.length(), hash);

    // Convert hash to hex string
    stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}