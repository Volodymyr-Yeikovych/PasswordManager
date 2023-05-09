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
    const std::vector<std::string> SEARCH_EDIT_DELETE_PARAMS_TYPES = {"a", "n", "pw", "c", "w", "l"};
public:
    explicit ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager,
                            const CryptographyManager &cryptographyManager);

    auto start() -> void;

    auto operator=(ProgramManager const &programManager) -> ProgramManager;

    auto inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool;

    auto isValidStartMode(std::string basicString) -> bool;

    auto isEncryption(const std::string &basicString) -> bool;

    auto isDecryption(const std::string &basicString) -> bool;

    auto isExitCommand(const std::string &command) -> bool;

    auto isNotCommand(const std::string &command) -> bool;

    auto isSearchCommand(const std::string &command) -> bool;

    auto isSortCommand(const std::string &command) -> bool;

    auto isAddCommand(const std::string &command) -> bool;

    auto isEditPasswordCommand(const std::string &command) -> bool;

    auto isDeletePasswordCommand(const std::string &command) -> bool;

    auto isAddCategoryCommand(const std::string &command) -> bool;

    auto isDeleteCategoryCommand(const std::string &command) -> bool;

    auto isHelpCommand(const std::string &command) -> bool;

    auto executeCommand(const std::string &command) -> void;

    auto executeSearch(const std::string &command) -> void;

    auto listCommands() -> void;

    auto executeSort(const std::string &command) -> void;

    auto executeAdd(const std::string &command)  -> void;

    auto executeEditPassword(const std::string &command) -> void;

    auto executeDeletePassword(const std::string &command) -> void;

    auto executeAddCategory(const std::string &command) -> void;

    auto executeDeleteCategory(const std::string &command) -> void;

    auto getStringVecFromSADCommands(const std::string &command) -> std::vector<std::string>;

    auto strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string>;

    auto leftTrim(std::string &str) -> void;
    auto rightTrim(std::string &str) -> void;
    auto trim(std::string &str) -> void;

    static auto exit (int errCode) -> void;

    auto isEmptyCommand(const std::vector<std::string> &params) -> bool;
    auto isInvalidSADCommandSyntax(const std::vector<std::string> &params) -> bool;

    auto isInvalidCommandKeyword(const std::vector<std::string> &params, const std::string &commandKeyword) -> bool;
    auto isInvalidSEDCommandTypes(const std::vector<std::string> &params) -> bool;
    auto isInvalidAddCommandTypes(const std::vector<std::string> &params) -> bool;
    auto isInvalidAddCommandLength(const std::vector<std::string> &params) -> bool;
    auto strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string>;
    auto getStringVecFromAddDelCatCommands(const std::string &command) -> std::vector<std::string>;
    auto isInvalidAddDelCatCommandLength(const std::vector<std::string> &params) -> bool;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
