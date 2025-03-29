/*----------------------------------------------------------------------*
 *                             COMMIT                                   *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages commit history, stores metadata, tracks snapshots.

------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include "../inc/core/commit.h"

namespace fs = std::filesystem;

// Function to get the current timestamp
std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// Function to create a commit
void createCommit(const std::string& message) {
    if (message.empty()) {
        std::cerr << "Error: Commit message cannot be empty." << std::endl;
        return;
    }

    // Generate commit metadata
    std::string timestamp = getCurrentTimestamp();
    std::string commitId = std::to_string(std::hash<std::string>{}(timestamp + message));

    // Create a commit directory if it doesn't exist
    fs::path commitDir = ".krypton/commits";
    if (!fs::exists(commitDir)) {
        fs::create_directories(commitDir);
    }

    // Write commit metadata to a file
    std::ofstream commitFile(commitDir / (commitId + ".txt"));
    if (commitFile.is_open()) {
        commitFile << "Commit ID: " << commitId << "\n";
        commitFile << "Timestamp: " << timestamp << "\n";
        commitFile << "Message: " << message << "\n";
        commitFile.close();
        std::cout << "Commit created successfully with ID: " << commitId << std::endl;
    } else {
        std::cerr << "Error: Unable to write commit file." << std::endl;
    }
}