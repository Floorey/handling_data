#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <vector>


namespace fs = std::filesystem;

void backupFiles(const std::vector<std::string>& sourceDirs, const std::string& destDir) {
    for (const auto& sourceDir : sourceDirs) {
        for (const auto& entry : fs::directory_iterator(sourceDir)) {
            try {
                fs::copy(entry.path(), destDir / entry.path().filename());
                std::cout << "Copied: " << entry.path() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Failed to copy: " << entry.path() << " Error: " << e.what() << std::endl;
            }
        }
    }
}

void updatePaths(std::vector<std::string>& sourceDirs, std::string& destDir) {
    sourceDirs = {"C:/Users/lukas/CLionProjects", "C:/Users/lukas/GolandProjects"};
    destDir = {"D:/Backup"};

}


int main() {
    std::vector<std::string > sourceDirs;
    std::string destDir;

    updatePaths(sourceDirs, destDir);

    while (true) {
        backupFiles(sourceDirs, destDir);
        std::this_thread::sleep_for(std::chrono::hours(24)); // Run once per day
    }
    return 0;
}