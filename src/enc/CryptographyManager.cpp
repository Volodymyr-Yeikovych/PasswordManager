//
// Created by Volodymyr on 5/1/2023.
//

#include "CryptographyManager.h"
#include "../mapper/PasswordMapper.h"

CryptographyManager::CryptographyManager(const FileManager &fileManager) {
    this->fileManager = fileManager;
}

auto CryptographyManager::operator=(const CryptographyManager &other) -> CryptographyManager & {
    this->fileManager = other.fileManager;
    return *this;
}

auto CryptographyManager::getEnlargedPsw(const std::string &encPsw) -> std::string {
    auto sliceFrom = encPsw.size();
    auto slice = encPsw;
    for (int i = sliceFrom; i < PSW_ENC_VEC.size(); i++) {
        slice.append(PSW_ENC_VEC[i]);
    }
    return slice;
}

auto CryptographyManager::encrypt(const std::filesystem::path &path, const std::string &encPass) -> void {
    auto fileContents = fileManager.getFileContents(path);
    auto pswEnlarged = getEnlargedPsw(encPass);
    auto repeatIndex = 0;
    for (auto &c : fileContents) {
        if (repeatIndex == pswEnlarged.size()) repeatIndex = 0;
        c = (char) (c + (pswEnlarged[repeatIndex]));
        repeatIndex++;
    }
    fileManager.setFileContents(fileContents, path);
}

auto CryptographyManager::decrypt(const std::filesystem::path &path, const std::string &decPass) -> void {
    auto fileContents = fileManager.getFileContents(path);
    auto pswEnlarged = getEnlargedPsw(decPass);
    auto repeatIndex = 0;
    for (auto &c : fileContents) {
        if (repeatIndex == pswEnlarged.size()) repeatIndex = 0;
        c = (char) (c - (pswEnlarged[repeatIndex]));
        repeatIndex++;
    }

    auto catVec = PasswordMapper::mapTextToCategoryVec(fileContents);
    auto formattedContents = PasswordMapper::mapCategoryVecToText(catVec);
    fileManager.setFileContents(formattedContents, path);
}
