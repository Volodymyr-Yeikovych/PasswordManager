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
    std::string const DEFAULT_DIR = std::string(R"(C:\Users\Volodymyr\CLionProjects\PJC_PROJECT_PasswordManager\cmake-build-debug\EncFiles)");

    public:
        auto operator= (FileManager const& fileManager) -> FileManager;
        auto countFilesInDefDir() -> int;
        auto countFilesDir(const std::string &dir) -> int;
        auto getFilesVector() -> std::vector<std::filesystem::path>;
        auto getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path>;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H
