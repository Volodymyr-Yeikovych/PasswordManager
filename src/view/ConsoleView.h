//
// Created by Volodymyr on 4/30/2023.
//

#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_CONSOLEVIEW_H
#define PJC_PROJECT_PASSWORDMANAGER_CONSOLEVIEW_H


#include <filesystem>
#include <vector>
#include <map>
#include "../model/Category.h"

/**
 *
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 * @since 1.0
 */

class ConsoleView {

public:
    auto print(std::string const &input) -> void;

    auto println(std::string const &input) -> void;

    auto println() -> void;

    auto displayFiles(const std::vector<std::filesystem::path> &files) -> void;

    auto readNum() -> int;

    auto readString() -> std::string;

    auto printCategoryMap(const std::map<Category, std::vector<Password>> &toPrint) -> void;

    auto displayCategoryVec(const std::vector<Category> &catVec) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CONSOLEVIEW_H
