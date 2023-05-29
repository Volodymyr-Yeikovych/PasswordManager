//
// Created by Volodymyr on 4/30/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PROGRAMCONTROLLER_H
#define PJC_PROJECT_PASSWORDMANAGER_PROGRAMCONTROLLER_H

#include "../file/FileManager.h"
#include "../view/ConsoleView.h"
#include "../enc/CryptographyManager.h"
#include "../mapper/PasswordMapper.h"

/**
 * Main logic class which is responsible for parsing and execution of commands received from user.
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class ProgramController {
    /**
     * Entity of file io
     */
    FileManager fileManager;
    /**
     * Entity of graphical io
     */
    ConsoleView consoleManager;
    /**
     * Entity that is responsible for encryption/decryption of data received from file io
     */
    CryptographyManager cryptographyManager;
    /**
     * Entity that is responsible for parsing console output into model classes
     */
    PasswordMapper passwordMapper;
    /**
     * Path to the file for file io
     */
    std::filesystem::path filePath = std::filesystem::path();
    /**
     * Parameter types for search/edit/delete commands
     */
    const std::vector<std::string> SEARCH_EDIT_DELETE_PARAMS_TYPES = {"a", "n", "pw", "c", "w", "l"};
    /**
     * Parameter types for sort command
     */
    const std::vector<std::string> SORT_PARAMS_TYPES = {"n", "pw", "c", "w", "l"};
    /**
     * Primary and Secondary sort order types for sort command
     */
    const std::vector<std::string> SORT_PARAMS_ORDER_TYPES = {"len", "abc", "desc", "asc"};
    /**
     * Default primary sort order parameter
     */
    const std::string DEFAULT_SORT_ORDER_FIRST_PARAM = "len";
    /**
     * Default secondary sort order parameter
     */
    const std::string DEFAULT_SORT_ORDER_SECOND_PARAM = "asc";
public:
    /**
     * Constructs entity of this class with specified file io, graphical io, cryptography and mapper instances
     *
     * @param fileManager - file io
     * @param consoleManager - graphical io
     * @param cryptographyManager  - cryptography class
     * @param mapper - mapper class
     */
    explicit ProgramController(const FileManager &fileManager, const ConsoleView &consoleManager,
                               const CryptographyManager &cryptographyManager, const PasswordMapper &mapper);
    /**
     * Starts execution of a program
     */
    auto start() -> void;

    auto operator=(ProgramController const &programManager) -> ProgramController &;

private:
    /**
     * Checks if input index of directory is out of bounds
     * @param input - index of directory
     * @param poolSize - size of directory pool
     * @returns true - if is valid index, and such directory index is present
     * @returns false - if index is out of bounds
     */
    auto inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool;

    /**
     * Checks if specified string is exit command
     * @param command - string to check
     * @returns true - specified string is exit command
     * @returns false - otherwise
     */
    auto isExitCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is not a command
     *
     * @param command - string to check
     * @returns true - if specified string is not a command
     * @returns false - otherwise
     */
    auto isNotCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a search command
     *
     * @param command - string to check
     * @returns true - if specified string is a search command
     * @returns false - otherwise
     */
    auto isSearchCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a sort command
     *
     * @param command - string to check
     * @returns true - if specified string is a sort command
     * @returns false - otherwise
     */
    auto isSortCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a add command
     *
     * @param command - string to check
     * @returns true - if specified string is a add command
     * @returns false - otherwise
     */
    auto isAddCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a edit password command
     *
     * @param command - string to check
     * @returns true - if specified string is a edit password command
     * @returns false - otherwise
     */
    auto isEditPasswordCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a delete password command
     *
     * @param command - string to check
     * @returns true - if specified string is a delete password command
     * @returns false - otherwise
     */
    auto isDeletePasswordCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a add category command
     *
     * @param command - string to check
     * @returns true - if specified string is a add category command
     * @returns false - otherwise
     */
    auto isAddCategoryCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a delete category command
     *
     * @param command - string to check
     * @returns true - if specified string is a delete category command
     * @returns false - otherwise
     */
    auto isDeleteCategoryCommand(const std::string &command) -> bool;

    /**
     * Checks if specified string is a help command
     *
     * @param command - string to check
     * @returns true - if specified string is a help command
     * @returns false - otherwise
     */
    auto isHelpCommand(const std::string &command) -> bool;

    /**
     * Executes specified command
     * @param command - command to execute
     */
    auto executeCommand(const std::string &command) -> void;

    /**
     * Executes search command
     * @param command - command to execute
     */
    auto executeSearch(const std::string &command) -> void;

    /**
     * Executes help command
     * @param command - command to execute
     */
    auto executeHelp() -> void;

    /**
     * Executes sort command
     * @param command - command to execute
     */
    auto executeSort(const std::string &command) -> void;

    /**
     * Executes add command
     * @param command - command to execute
     */
    auto executeAdd(const std::string &command) -> void;

    /**
     * Executes edit password command
     * @param command - command to execute
     */
    auto executeEditPassword(const std::string &command) -> void;

    /**
     * Executes delete password command
     * @param command - command to execute
     */
    auto executeDeletePassword(const std::string &command) -> void;

    /**
     * Executes add category command
     * @param command - command to execute
     */
    auto executeAddCategory(const std::string &command) -> void;

    /**
     * Executes delete category command
     * @param command - command to execute
     */
    auto executeDeleteCategory(const std::string &command) -> void;

    /**
     * Parses specified string to vector needed to execute search/delete commands.
     *
     * @param command - string to parse
     * @returns std::vector of std::string where each std::string is separate parameter of the given command
     * @returns empty std::vector if command has incorrect format
     */
    auto getStringVecFromSearchDeleteCommands(const std::string &command) -> std::vector<std::string>;

    /**
     * Checks if given vector of string is empty
     * @param params - vector of strings
     * @returns true - if vector is empty
     * @returns false - otherwise
     */
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

    auto editData(const Category &catToMatch, const Category &catToEdit, const Password &pswToMatch,
                  const Password &pswToEdit, std::vector<Category> &saveData) -> void;

    auto catExists(const Category &catToAdd, const std::vector<Category> &fileData) -> bool;

    auto getNameMatchingCatIterator(const Category &catToAdd,
                                    const std::vector<Category> &fileData) -> std::vector<Category>::const_iterator;

    auto
    deleteMatching(const Password &pswToMatch, const Category &catToMatch, std::vector<Category> &fileData) -> void;

    auto sortData(const std::vector<std::string> &sortVec, std::vector<Category> &fileData) -> void;

    auto getSortVecFromSortCommand(const std::vector<std::string> &commandParams) -> std::vector<std::string>;

    auto isSortParam(const std::string &param) -> bool;

    auto isSortSubParam(const std::string &subParam) -> bool;

    auto isValidSortVec(const std::vector<std::string> &sortVec) -> bool;

    auto passwordSafetyInform(const std::string &psw, const std::vector<Category> &fileData) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PROGRAMCONTROLLER_H
