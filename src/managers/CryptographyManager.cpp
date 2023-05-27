//
// Created by Volodymyr on 5/1/2023.
//

#include <iostream>
#include "CryptographyManager.h"
#include "PasswordMapper.h"

CryptographyManager::CryptographyManager(const FileManager &fileManager) {
    this->fileManager = fileManager;
}

auto CryptographyManager::getPasswordSequence(const std::string &encPsw) -> int {
    return 3;
}

auto CryptographyManager::encrypt(std::filesystem::path path, std::string encPass) -> void {
    auto fileContents = fileManager.getFileContents(path);
    auto passwordSequence = getPasswordSequence(encPass);
    for (auto &c : fileContents) {
        c = (char) (c + passwordSequence);
    }
    fileManager.setFileContents(fileContents, path);
}

auto CryptographyManager::decrypt(std::filesystem::path path, std::string decPass) -> void {
    auto fileContents = fileManager.getFileContents(path);
    auto passwordSequence = getPasswordSequence(decPass);
    for (auto &c : fileContents) {
        c = (char) (c - passwordSequence);
    }

    auto catVec = PasswordMapper::mapTextToCategoryVec(fileContents);
    auto formattedContents = PasswordMapper::mapCategoryVecToText(catVec);
    fileManager.setFileContents(formattedContents, path);
}
