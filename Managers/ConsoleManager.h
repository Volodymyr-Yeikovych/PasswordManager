//
// Created by Volodymyr on 4/30/2023.
//

#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H


#include <filesystem>
#include <vector>

class ConsoleManager {

public:
    auto print(std::string const &input) -> void;
    auto println(std::string const &input) -> void;
    auto println() -> void;
    auto displayFiles(const std::vector<std::filesystem::path> &files) -> void;
    auto readNum() -> int;
    auto readString() -> std::string ;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H
