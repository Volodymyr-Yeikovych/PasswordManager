//
// Created by Volodymyr on 4/30/2023.
//

#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H


#include <filesystem>
#include <vector>
#include <map>
#include "../model/Category.h"

class ConsoleManager {

public:
    auto print(std::string const &input) -> void;
    auto println(std::string const &input) -> void;
    auto println() -> void;
    auto displayFiles(const std::vector<std::filesystem::path> &files) -> void;
    auto readNum() -> int;
    auto readString() -> std::string;
    auto printMap(const std::map<Category, std::vector<Password>> &toPrint) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H
