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

auto CryptographyManager::getCryptoSequence(const std::string &encPsw) -> std::string {
    auto cryptoSeq = encPsw;
    for (auto &c : cryptoSeq) {
        auto c2 = PSW_ENC_VEC[c].at(0);
        auto newC = (int) (c + c2);
        while (newC > 100) newC -= 39;
        c = (char) newC;
    }
    return cryptoSeq;
}

auto CryptographyManager::addTime(std::string &contents) -> void {
    auto curTime = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(curTime);
    auto locTime = std::localtime(&time);

    auto hours = std::to_string(locTime->tm_hour);
    auto minutes = std::to_string(locTime->tm_min);
    auto seconds = std::to_string(locTime->tm_sec);

    if (hours.size() < 2) hours.insert(0, "0");
    if (minutes.size() < 2) minutes.insert(0, "0");
    if (seconds.size() < 2) seconds.insert(0, "0");

    if (contents.size() >= 33) {
        contents.insert(11, hours);
        contents.insert(22, minutes);
        contents.insert(33, seconds);
    }
}

auto CryptographyManager::getLastTimeModifiedMsg(std::string &contents) -> std::string {
    auto hours = contents.substr(11, 2);
    auto minutes = contents.substr(22, 2);
    auto seconds = contents.substr(33, 2);

    contents.erase(contents.begin() + 11, contents.begin() + 13);
    contents.erase(contents.begin() + 22 - 2, contents.begin() + 24 - 2);
    contents.erase(contents.begin() + 33 - 4, contents.begin() + 35 - 4);

    auto lastTimeModMsg = std::string("Last time modified: Hours(" + hours + "), ");
    lastTimeModMsg.append("Minutes(").append(minutes).append("), ");
    lastTimeModMsg.append("Seconds(").append(seconds).append(")");

    return lastTimeModMsg;
}

auto CryptographyManager::encrypt(const std::filesystem::path &path, const std::string &encPass) -> void {
    auto fileContents = fileManager.getFileContents(path);
    addTime(fileContents);
    auto pswEnlarged = getCryptoSequence(encPass);
    auto repeatIndex = 0;
    auto i = 0;
    for (auto &c : fileContents) {
        if (repeatIndex == pswEnlarged.size()) repeatIndex = 0;
        if (i != 11 && i != 12 && i != 22 && i != 23 && i != 33 && i != 34) {
            c = (char) (c + (pswEnlarged[repeatIndex]));
            repeatIndex++;
        }
        i++;
    }
    fileManager.setFileContents(fileContents, path);
}

auto CryptographyManager::decrypt(const std::filesystem::path &path, const std::string &decPass) -> std::string {
    auto fileContents = fileManager.getFileContents(path);
    auto lastTimeModMsg = getLastTimeModifiedMsg(fileContents);
    auto pswEnlarged = getCryptoSequence(decPass);
    auto repeatIndex = 0;
    for (auto &c : fileContents) {
        if (repeatIndex == pswEnlarged.size()) repeatIndex = 0;
        c = (char) (c - (pswEnlarged[repeatIndex]));
        repeatIndex++;
    }

    try {
        auto catVec = PasswordMapper::mapTextToCategoryVec(fileContents);
        auto formattedContents = PasswordMapper::mapCategoryVecToText(catVec);
        fileManager.setFileContents(formattedContents, path);
    } catch (const std::runtime_error &e) {
        fileManager.setFileContents(fileContents, path);
    }
    return lastTimeModMsg;
}
