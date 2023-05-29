//
// Created by Volodymyr on 5/11/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H
#define PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H


#include <map>
#include "../model/Password.h"
#include "../model/Category.h"

class PasswordMapper {
    inline static std::vector<std::string> randomPool = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b",
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
    auto static getPasswordFromSearchCommand(const std::vector<std::string> &commandParams) -> Password;

    auto static getPasswordFromAddCommand(const std::vector<std::string> &commandParams) -> Password;

    auto static getSearchPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password;

    auto static getEditPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password;

    auto static getPasswordFromDeleteCommand(const std::vector<std::string> &commandParams) -> Password;

    auto static getCategoryFromSearchCommand(const std::vector<std::string> &commandParams) -> Category;

    auto static getCategoryFromAddCommand(const std::vector<std::string> &commandParams) -> Category;

    auto static getSearchCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category;

    auto static getEditCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category;

    auto static getCategoryFromAddDelCatCommand(const std::vector<std::string> &commandParam) -> Category;

    auto static getCategoryFromDeleteCommand(const std::vector<std::string> &commandParam) -> Category;

    auto static mapPasswordToString(const Password &password) -> std::string;

    auto static mapTextToCategoryVec(const std::string &text) -> std::vector<Category>;

    auto static mapCategoryVecToText(const std::vector<Category> &categoryVec) -> std::string;

    auto static strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string>;

    auto static strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string>;

    auto static leftTrim(std::string &str) -> void;

    auto static rightTrim(std::string &str) -> void;

    auto static trim(std::string &str) -> void;

private:
    auto static generatePassword(const std::string &params) -> std::string;

    auto static createPassword(int size, bool isUpper, bool isSpecial) -> std::string;

    auto static getEditCommandPipeIndex(const std::vector<std::string> &commandParams) -> int;

    auto static isNumerical(const std::string &str) -> bool;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H