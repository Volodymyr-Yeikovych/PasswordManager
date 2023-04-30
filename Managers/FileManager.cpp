//
// Created by Volodymyr on 4/30/2023.
//

#include <filesystem>
#include "FileManager.h"

auto FileManager::countFilesInDefDir() -> int {
    return countFilesDir(DEFAULT_DIR);
}

auto FileManager::countFilesDir(std::string const& dir) -> int {
    auto dirIter = std::filesystem::directory_iterator(dir);
    auto fCount = 0;

    for (auto& f : dirIter) {
        if (f.is_regular_file()) fCount++;
    }
    return fCount;
}

auto FileManager::operator=(const FileManager &other) -> FileManager {
    return *this;
}

auto FileManager::getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path> {
    auto dirIter = std::filesystem::directory_iterator(dir);
    auto fileVec = std::vector<std::filesystem::path>();

    for (auto& f : dirIter) {
        if (f.is_regular_file()) fileVec.push_back(f.path());
    }
    return fileVec;
}

auto FileManager::getFilesVector() -> std::vector<std::filesystem::path> {
    return getFilesVector(DEFAULT_DIR);
}
