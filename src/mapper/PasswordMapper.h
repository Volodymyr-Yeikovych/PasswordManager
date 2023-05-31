//
// Created by Volodymyr on 5/11/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H
#define PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H


#include <map>
#include "../model/Password.h"
#include "../model/Category.h"

/**
 * Mapper class responsible for parsing data from one format to another
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class PasswordMapper {
    /**
     * String pool for creation of random password
     */
    inline static std::vector<std::string> charPool = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b",
                                                       "c", "d", "e",
                                                       "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q",
                                                       "r", "s", "t",
                                                       "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F",
                                                       "G", "H", "I",
                                                       "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
                                                       "V", "W", "X",
                                                       "Y", "Z", "+", "-", "&", "|", "!", "(", ")", "[", "]", "^",
                                                       "~",
                                                       "*", "?", "\"", "\\", "%", "@", "^", "$", ",", ".", "<", ">",
                                                       "#"};
public:
    /**
     * Parses search command into Password class
     * @param commandParams - command to parse
     * @returns parsed Password instance
     */
    auto static getPasswordFromSearchCommand(const std::vector<std::string> &commandParams) -> Password;

    /**
     * Parses add command into Password class
     * @param commandParams - command to parse
     *
     * @returns parsed Password instance
     */
    auto static getPasswordFromAddCommand(const std::vector<std::string> &commandParams) -> Password;

    /**
     * Parses edit command into Password class
     * @param commandParams - command to parse
     * @returns parsed Password instance
     * @throws throw std::runtime_error - if edit command has invalid syntax
     */
    auto static getSearchPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password;

    /**
     * Parses edit command into Password class
     * @param commandParams - command to parse
     * @returns parsed Password instance
     * @throws throw std::runtime_error - if edit command has invalid syntax
     */
    auto static getEditPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password;

    /**
     * Parses delete command into Password class
     * @param commandParams - command to parse
     * @returns parsed Password instance
     */
    auto static getPasswordFromDeleteCommand(const std::vector<std::string> &commandParams) -> Password;

    /**
     * Parses search command into Category class
     * @param commandParams - command to parse
     * @returns parsed Password instance
     */
    auto static getCategoryFromSearchCommand(const std::vector<std::string> &commandParams) -> Category;

    /**
     * Parses add command into Category class
     * @param commandParams - command to parse
     * @returns parsed Category instance
     * @returns empty category if command doesn't specify category
     */
    auto static getCategoryFromAddCommand(const std::vector<std::string> &commandParams) -> Category;

    /**
     * Parses edit command into Category class
     * @param commandParams - command to parse
     * @returns parsed Category instance
     * @throws throw std::runtime_error - if edit command has invalid syntax
     */
    auto static getSearchCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category;

    /**
     * Parses edit command into Category class
     * @param commandParams - command to parse
     * @returns parsed Category instance
     * @throws throw std::runtime_error - if edit command has invalid syntax
     */
    auto static getEditCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category;

    /**
     * Parses add/delete category commands into Category class
     * @param commandParams - command to parse
     * @returns parsed Category instance
     */
    auto static getCategoryFromAddDelCatCommand(const std::vector<std::string> &commandParam) -> Category;

    /**
     * Parses delete command into Category class
     * @param commandParams - command to parse
     * @returns parsed Category instance
     */
    auto static getCategoryFromDeleteCommand(const std::vector<std::string> &commandParam) -> Category;

    /**
     * Parses specified password to its string representation
     *
     * @param password - password to parse
     * @returns string representation of specified password
     */
    auto static mapPasswordToString(const Password &password) -> std::string;

    /**
     * Parses specified text into category vector
     *
     * @param text - text to parse
     *
     * @returns parsed category vector
     *
     * @throws throw std::runtime_error - if text has invalid format
     */
    auto static mapTextToCategoryVec(const std::string &text) -> std::vector<Category>;

    /**
     * Maps specified category vector into its text representation
     *
     * @param categoryVec - category vector to parse
     * @returns parsed text from category vector
     */
    auto static mapCategoryVecToText(const std::vector<Category> &categoryVec) -> std::string;

    /**
     * Splits specified string into vector of strings using specified delimiter
     *
     * @param string - string to split
     * @param delim - delimiter to use
     * @returns string vector from specified string
     */
    auto static strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string>;

    /**
     * Splits specified string into vector of strings using specified delimiter
     * and calls trim method on each vector element
     *
     * @param string - string to split
     * @param delim - delimiter to use
     * @returns string vector from specified string
     */
    auto static strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string>;

    /**
     * Trims all leading spaces from the left
     *
     * @param str - string to modify
     */
    auto static leftTrim(std::string &str) -> void;

    /**
     * Trims all leading spaces from the right
     *
     * @param str - string to modify
     */
    auto static rightTrim(std::string &str) -> void;

    /**
     * Trims all leading spaces from the left and right
     *
     * @param str - string to modify
     */
    auto static trim(std::string &str) -> void;

    /**
     * Checks if given string is number
     *
     * @param str - string to check
     * @returns true - if given string is a number
     * @returns false - otherwise
     */
    auto static isNumerical(const std::string &str) -> bool;
private:
    /**
     * Extracts generate password arguments from specified command and returns generated password
     *
     * @param params - command to extract from
     * @returns generated password
     */
    auto static parseCommandAndGeneratePassword(const std::string &params) -> std::string;
    /**
     * Generates random string from specified parameters using values from const vector 'charPool'
     * @param size - size of generated sequence
     * @param isUpper - generated sequence will have upper case letters or not
     * @param isSpecial - generated sequence will have special letters or not
     * @returns generated string
     */
    auto static createPassword(int size, bool isUpper, bool isSpecial) -> std::string;

    /**
     * Returns index of pipe ('|') symbol from edit command
     * @param commandParams - command to look for pipe
     * @returns index of pipe ('|') symbol
     * @returns -1 if pipe wasn't found
     */
    auto static getEditCommandPipeIndex(const std::vector<std::string> &commandParams) -> int;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H
