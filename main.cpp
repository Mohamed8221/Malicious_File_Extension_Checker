#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <algorithm>

// Function to extract the file extension
std::string getFileExtension(const std::string& filename) {
    size_t dotPos = filename.find_last_of(".");
    if (dotPos == std::string::npos) {
        // No extension found
        return "";
    }
    return filename.substr(dotPos + 1);
}

// Function to check if the file has a malicious extension
bool isMaliciousExtension(const std::string& filename, const std::unordered_set<std::string>& maliciousExtensions) {
    std::string extension = getFileExtension(filename);
    // Convert the extension to lowercase for case-insensitive comparison
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // Check if the extension is in the set of malicious extensions
    return maliciousExtensions.find(extension) != maliciousExtensions.end();
}

// Function to read malicious file extensions from a file
bool loadMaliciousExtensions(const std::string& filepath, std::unordered_set<std::string>& maliciousExtensions) {
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return false;
    }

    std::string extension;
    while (std::getline(infile, extension)) {
        // Remove any leading or trailing whitespace
        extension.erase(0, extension.find_first_not_of(" \t\n\r"));
        extension.erase(extension.find_last_not_of(" \t\n\r") + 1);

        // Convert to lowercase for consistency
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        // Add extension to the set
        if (!extension.empty()) {
            maliciousExtensions.insert(extension);
        }
    }

    infile.close();
    return true;
}

int main() {
    std::unordered_set<std::string> maliciousExtensions;

    // Load malicious extensions from a file
    std::string extensionsFile = "D:\\offcrest\\pr\\malicious_extensions.txt";
    if (!loadMaliciousExtensions(extensionsFile, maliciousExtensions)) {
        return 1; // Exit if the file could not be opened
    }

    // Example file names to check
    std::string files[] = {"file1.exe", "document.txt", "script.js", "image.jpeg", "archive.rar", "virus.scr"};

    for (const auto& file : files) {
        if (isMaliciousExtension(file, maliciousExtensions)) {
            std::cout << file << " has a malicious file extension!" << std::endl;
        } else {
            std::cout << file << " is safe." << std::endl;
        }
    }

    return 0;
}
