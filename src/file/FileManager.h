//
// Created by Volodymyr on 4/30/2023.
//
#include <string>
#include <vector>
#include <filesystem>

#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H


class FileManager {
    std::string defaultDir;

public:
    FileManager(const std::string &dir);

    FileManager();

    auto operator=(FileManager const &fileManager) -> FileManager &;

    auto getFilesVector() -> std::vector<std::filesystem::path>;

    auto getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path>;

    auto getFileLines(const std::filesystem::path &filePath) -> std::vector<std::string>;

    auto getFileContents(const std::filesystem::path &filePath) -> std::string;

    auto setFileContents(const std::string &fileContent, const std::filesystem::path &filePath) -> bool;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H