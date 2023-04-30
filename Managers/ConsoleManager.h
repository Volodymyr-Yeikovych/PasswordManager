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
    template<typename T>
    auto print(T const &input) -> void;
    template<typename T>
    auto println(T const &input) -> void;
    auto println() -> void;
    auto displayFiles(const std::vector<std::filesystem::path> &files) -> void;
    auto readNum() -> int;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CONSOLEMANAGER_H
