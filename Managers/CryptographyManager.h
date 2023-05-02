//
// Created by Volodymyr on 5/1/2023.
//
#pragma once

#include <filesystem>
#include <vector>

#ifndef PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

#endif //PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

class CryptographyManager {

    public:
        auto encrypt(std::filesystem::path file, std::string encPass) -> void;
        auto decrypt(std::filesystem::path file, std::string decPass) -> void;
};