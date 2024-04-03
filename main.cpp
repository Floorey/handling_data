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
                auto destFilePath = destDir + "/" + entry.path().filename().string();
                if (!fs::exists(destFilePath)) { // Check if the file doesn't exist in the destination directory
                    fs::copy(entry.path(), destFilePath);
                    std::cout << "Copied: " << entry.path() << std::endl;
                } else {
                    std::cout << "Skipped: " << entry.path() << " (already exists in the destination)" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Failed to copy: " << entry.path() << " Error: " << e.what() << std::endl;
            }
        }
    }
}

void updatePaths(std::vector<std::string>& sourceDirs, std::string& destDir) {
    sourceDirs = {"C:/Users/lukas/CLionProjects", "C:/Users/lukas/GolandProjects","C:/Users/lukas/OneDrive/Desktop/Bilder", "C:/Program Files/PostgreSQL"};
    destDir = {"D:/Backup"};
}

void searchFiles(const std::string& destDir, const std::vector<std::string>& fileTypes) {
    try {
        for (const auto& entry : fs::directory_iterator(destDir)) {
            if (entry.is_regular_file()) {
                for (const auto& fileType : fileTypes) {
                    if (entry.path().extension() == fileType) {
                        std::cout << "Found: " << entry.path() << std::endl;
                        break; // Weiter zum nächsten Eintrag, sobald eine passende Datei gefunden wurde
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to search files in destination directory. Error: " << e.what() << std::endl;
    }
}


int main() {
    std::vector<std::string> sourceDirs;
    std::string destDir;

    updatePaths(sourceDirs, destDir);

    // Liste der Dateitypen, nach denen gesucht werden soll
    std::vector<std::string> fileTypes = { ".txt", ".exe", ".png", "jpg", ".html"};

    while (true) {
        backupFiles(sourceDirs, destDir); // Dateien sichern
        searchFiles(destDir, fileTypes); // Suche nach den angegebenen Dateitypen im Zielverzeichnis
        std::this_thread::sleep_for(std::chrono::hours(24)); // Einmal pro Tag ausführen
    }

    return 0;
}
