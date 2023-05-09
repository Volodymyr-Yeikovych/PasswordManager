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
        FileManager(const std::string& dir);
        FileManager();
        auto operator= (FileManager const& fileManager) -> FileManager;
        auto countFilesInDefDir() -> int;
        auto countFilesDir(const std::string &dir) -> int;
        auto getFilesVector() -> std::vector<std::filesystem::path>;
        auto getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path>;
        auto getFileContents(const std::filesystem::path &filePath) -> std::vector<std::string>;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H
