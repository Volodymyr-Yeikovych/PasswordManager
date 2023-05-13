//
// Created by Volodymyr on 4/30/2023.
//

#include <string>
#include "ConsoleManager.h"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include "PasswordMapper.h"
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

auto ConsoleManager::readString() -> std::string {
    auto output = std::string();
    std::getline(std::cin >> std::ws, output);
    return output;
}

auto ConsoleManager::printMap(const std::map<Category, std::vector<Password>> &toPrint) -> void {
    for (const auto &entry : toPrint) {
        auto passVec = std::vector<std::string>();
        for (const auto &psw : entry.second)
            passVec.emplace_back(PasswordMapper::mapPasswordToString(psw));
        fmt::print("{}: {}\n", entry.first.getName(), passVec);
    }
}
