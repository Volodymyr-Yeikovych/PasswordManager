//
// Created by Volodymyr on 4/30/2023.
//

#include <filesystem>
#include <fstream>
#include "FileManager.h"
#include <fmt/core.h>
#include <fmt/ranges.h>

FileManager::FileManager(const std::string &dir) {
    this->defaultDir = dir;
}

FileManager::FileManager() {
    this->defaultDir = R"(C:\Users\Volodymyr\CLionProjects\PJC_PROJECT_PasswordManager\resources\targetFiles)";
}

auto FileManager::operator=(const FileManager &other) -> FileManager & {
    return *this;
}

auto FileManager::getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path> {
    auto dirIter = std::filesystem::directory_iterator(dir);
    auto fileVec = std::vector<std::filesystem::path>();

    for (auto &f: dirIter) {
        if (f.is_regular_file()) fileVec.push_back(f.path());
    }
    return fileVec;
}

auto FileManager::getFilesVector() -> std::vector<std::filesystem::path> {
    return getFilesVector(defaultDir);
}

auto FileManager::getFileLines(const std::filesystem::path &filePath) -> std::vector<std::string> {
    auto in = std::fstream(filePath, std::fstream::in | std::fstream::app);
    auto line = std::string();
    auto lines = std::vector<std::string>();
    while (std::getline(in, line)) {
        if (!line.empty()) lines.emplace_back(line);
    }
    in.close();
    return lines;
}

auto FileManager::getFileContents(const std::filesystem::path &filePath) -> std::string {
    auto content = std::string();
    for (const auto &line: getFileLines(filePath)) {
        content.append(line);
    }
    return content;
}

auto FileManager::setFileContents(const std::string &fileContent, const std::filesystem::path &filePath) -> bool {
    auto out = std::ofstream(filePath);
    if (out) {
        out << fileContent;
    }
    out.close();
    return true;
}
