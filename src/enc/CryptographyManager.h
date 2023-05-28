//
// Created by Volodymyr on 5/1/2023.
//
#pragma once

#include <filesystem>
#include <vector>
#include "../file/FileManager.h"

#ifndef PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

class CryptographyManager {
    FileManager fileManager;
    const std::vector<std::string> PSW_ENC_VEC = {"w", "-", "R", "3", "6", "W", "r", "+", "D", "#", "a", "M", "F", "-",
                                                  "m", "V", "7", "f", "!", "M", "=", "5", "!", "7", "a", "4", "r", "t",
                                                  "p", "F", "C", "V", "_", "u", "$", "O", "2", "J", "+", "=", "I", "7",
                                                  "X", "I", "c", "b", "J", "C", "e", "A", "R", "S", "n", "_", "X", "6",
                                                  "r", "o", "+", "@", "W", "S", "9", "z", "F", "R", "w", "3", "F", "%",
                                                  "K", "H", "g", "S", ")", "u", "C", "*", "c", "l", "J", "?", "G", "K",
                                                  "f", "?", "3", "X", "@", "L", "3", "S", "N", "$", "!", "S", "V", "6",
                                                  "E", "A", "3", "7", "1", "F", "x", "t", "j", "L", ">", "h", "=", "F",
                                                  "W", "6", "K", "b", "q", "X", "m", "3", "M", "D", "L", "p", "i", "b",
                                                  "q", "a"};
public:
    CryptographyManager(const FileManager &fileManager);

    auto operator=(const CryptographyManager &other) -> CryptographyManager &;

    auto encrypt(const std::filesystem::path &path, const std::string &encPass) -> void;

    auto decrypt(const std::filesystem::path &path, const std::string &decPass) -> void;

private:
    auto getEnlargedPsw(const std::string &encPsw) -> std::string;

};

#endif //PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H