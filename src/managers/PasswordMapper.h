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
public:
    auto mapFileEntryToPassword(const std::string &line) -> Password;
    auto static mapSearchCommandEntryToPassword(const std::string &command) -> Password;
    auto mapPasswordToFileEntry(const Password &entry) -> std::string;
    auto static getCategoryFromSearchCommand(const std::string &command) -> Category;
    auto static mapPasswordToString(const Password &password) -> std::string;
    auto static mapCategoryToString(const Category &category) -> std::string;

    auto static mapStringToCategory(const std::string &stack) -> Category;

    auto static mapTextToCategoryVec(const std::string &text) -> std::vector<Category>;

    auto static mapCategoryVecToText(const std::vector<Category> &categoryVec) -> std::string;

    auto static strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string>;

    auto static strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string>;

    auto static leftTrim(std::string &str) -> void;

    auto static rightTrim(std::string &str) -> void;

    auto static trim(std::string &str) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H
