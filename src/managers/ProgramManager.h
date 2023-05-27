//
// Created by Volodymyr on 4/30/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H

#include "FileManager.h"
#include "ConsoleManager.h"
#include "CryptographyManager.h"
#include "PasswordMapper.h"

class ProgramManager {
    FileManager fileManager;
    ConsoleManager consoleManager;
    CryptographyManager cryptographyManager;
    PasswordMapper passwordMapper;
    std::filesystem::path filePath = std::filesystem::path();
    const std::vector<std::string> SEARCH_EDIT_DELETE_PARAMS_TYPES = {"a", "n", "pw", "c", "w", "l"};
    const std::vector<std::string> SORT_PARAMS_TYPES = {"n", "pw", "c", "w", "l"};
    const std::vector<std::string> SORT_PARAMS_ORDER_TYPES = {"len", "abc", "desc", "asc"};
    const std::string DEFAULT_SORT_ORDER_FIRST_PARAM = "len";
    const std::string DEFAULT_SORT_ORDER_SECOND_PARAM = "asc";
public:
    explicit ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager,
                            const CryptographyManager &cryptographyManager, const PasswordMapper &mapper);

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

    auto executeAdd(const std::string &command) -> void;

    auto executeEditPassword(const std::string &command) -> void;

    auto executeDeletePassword(const std::string &command) -> void;

    auto executeAddCategory(const std::string &command) -> void;

    auto executeDeleteCategory(const std::string &command) -> void;

    auto getStringVecFromSearchDeleteCommands(const std::string &command) -> std::vector<std::string>;

    static auto exit(int errCode) -> void;

    auto isEmptyCommand(const std::vector<std::string> &params) -> bool;

    auto isInvalidSADCommandSyntax(const std::vector<std::string> &params) -> bool;

    auto isInvalidCommandKeyword(const std::vector<std::string> &params, const std::string &commandKeyword) -> bool;

    auto isInvalidSEDCommandTypes(const std::vector<std::string> &params) -> bool;

    auto isInvalidAddCommandTypes(const std::vector<std::string> &params) -> bool;

    auto isInvalidAddCommandLength(const std::vector<std::string> &params) -> bool;

    auto getStringVecFromAddDelCatCommands(const std::string &command) -> std::vector<std::string>;

    auto getStringVecFromAddCommands(const std::string &command) -> std::vector<std::string>;

    auto isInvalidAddDelCatCommandLength(const std::vector<std::string> &params) -> bool;

    auto getStringVecFromSortCommand(const std::string &command) -> std::vector<std::string>;

    auto isInvalidSortCommandTypes(const std::vector<std::string> &params) -> bool;

    auto isInvalidSortParam(const std::string &param) -> bool;

    auto isInvalidSortOrder(const std::string &param) -> bool;

    auto getStringVecFromEditCommand(const std::string &command) -> std::vector<std::string>;

    auto isInvalidEditCommandTypes(const std::vector<std::string> &params) -> bool;

    auto isInvalidSEDParamType(const std::string &paramType) -> bool;

    auto eraseNotMatching(const Category &searchCat, std::map<Category, std::vector<Password>> &matchingPsw) -> void;

    auto editData(const Category &catToMatch, const Category &catToEdit, const Password &pswToMatch,
                  const Password &pswToEdit, std::vector<Category> &saveData) -> void;

    auto catExists(const Category &catToAdd, const std::vector<Category> &fileData) -> bool;

    auto getNameMatchingCatIterator(const Category &catToAdd,
                                    const std::vector<Category> &fileData) -> std::vector<Category>::const_iterator;
    auto deleteMatching(const Password &pswToMatch, const Category &catToMatch, std::vector<Category> &fileData) -> void;
    auto sortData(const std::vector<std::string> &sortVec, std::vector<Category> &fileData) -> void;
    auto getSortVecFromSortCommand(const std::vector<std::string> &commandParams) -> std::vector<std::string>;
    auto isSortParam(const std::string &param) -> bool;
    auto isSortSubParam(const std::string &subParam) -> bool;
    auto isValidSortVec(const std::vector<std::string> &sortVec) -> bool;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
