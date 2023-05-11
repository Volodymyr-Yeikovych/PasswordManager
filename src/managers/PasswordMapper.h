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
    auto mapStringToPsw(const std::string &line) -> Password;

    auto mapPswToString(const Password &entry) -> std::string;

    auto static mapCategoryToString(const Category &category) -> std::string;

    auto static mapStringToCategory(const std::string &stack) -> Category;

    auto static mapTextToCategoryMap(const std::string &text) -> std::map<Category, std::vector<std::string>>;

    auto static mapCategoryMapToText(const std::map<Category, std::vector<std::string>> &categoryMap) -> std::string;

    auto strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string>;

    auto strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string>;

    auto leftTrim(std::string &str) -> void;

    auto rightTrim(std::string &str) -> void;

    auto trim(std::string &str) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORDMAPPER_H
