//
// Created by Volodymyr on 4/30/2023.
//

#include <string>
#include "ConsoleManager.h"
#include <fmt/core.h>
#include <vector>
#include <filesystem>
#include <iostream>

auto ConsoleManager::print(std::string const &input) -> void {
    auto formatted = fmt::format("{}", input);
    fmt::print("{}", formatted);
}

auto ConsoleManager::println(std::string const &input) -> void {
    print(input);
    fmt::print("\n");
}

auto ConsoleManager::println() -> void {
    println("");
}

auto ConsoleManager::displayFiles(const std::vector<std::filesystem::path> &files) -> void {
    auto counter = 1;
    for (auto &f: files) {
        print(f.string());
        print("  <--  ");
        print(std::to_string(counter++));
        println();
    }
}

auto ConsoleManager::readNum() -> int {
    auto num = int();
    std::cin >> num;
    return num;
}

auto ConsoleManager::readPath() -> std::filesystem::path{
    auto sPath = std::string();
    std::getline(std::cin, sPath);
    auto path = std::filesystem::path(sPath);
    return path;
}
