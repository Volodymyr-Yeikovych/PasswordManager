//
// Created by Volodymyr on 4/30/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H


#include "FileManager.h"
#include "ConsoleManager.h"
#include "CryptographyManager.h"

class ProgramManager {
    FileManager fileManager;
    ConsoleManager consoleManager;
    CryptographyManager cryptographyManager;
public:
    explicit ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager,
                            const CryptographyManager &cryptographyManager);

    auto start() -> void;

    auto operator=(ProgramManager const &programManager) -> ProgramManager;

    auto inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool;

    auto isValidStartMode(std::string basicString) -> bool;

    auto isEncryption(const std::string &basicString) -> bool;

    auto isDecryption(const std::string &basicString) -> bool;

    auto isCloseCommand(const std::string &basicString) -> bool;

    auto isNotCommand(const std::string &basicString) -> bool;

    auto isSearchCommand(const std::string &basicString) -> bool;

    auto isSortCommand(const std::string &basicString) -> bool;

    auto isAddCommand(const std::string &basicString) -> bool;

    auto isEditPasswordCommand(const std::string &basicString) -> bool;

    auto isDeletePasswordCommand(const std::string &basicString) -> bool;

    auto isAddCategoryCommand(const std::string &basicString) -> bool;

    auto isDeleteCategoryCommand(const std::string &basicString) -> bool;

    auto isHelpCommand(const std::string &basicString) -> bool;

    auto executeCommand(const std::string &basicString) -> void;

    auto executeSearch(const std::string &basicString) -> void;

    auto listCommands() -> void;

    auto executeSort(const std::string &basicString) -> void;

    auto executeAdd(const std::string &basicString)  -> void;

    auto executeEditPassword(const std::string &basicString) -> void;

    auto executeDeletePassword(const std::string &basicString) -> void;

    auto executeAddCategory(const std::string &basicString) -> void;

    auto executeDeleteCategory(const std::string &basicString) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
