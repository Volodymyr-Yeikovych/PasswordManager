//
// Created by Volodymyr on 5/1/2023.
//
#pragma once

#include <filesystem>
#include <vector>
#include "FileManager.h"

#ifndef PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

#endif //PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

class CryptographyManager {
    FileManager fileManager;

    public:
        CryptographyManager(const FileManager &fileManager);
        auto encrypt(std::filesystem::path path, std::string encPass) -> void;
        auto decrypt(std::filesystem::path path, std::string decPass) -> void;
        auto getPasswordSequence(const std::string &encPsw) -> int;
};