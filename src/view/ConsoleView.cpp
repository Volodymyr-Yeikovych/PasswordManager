//
// Created by Volodymyr on 4/30/2023.
//

#include <string>
#include "ConsoleView.h"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include "../mapper/PasswordMapper.h"
#include <vector>
#include <filesystem>
#include <iostream>

auto ConsoleView::print(std::string const &input) -> void {
    auto formatted = fmt::format("{}", input);
    fmt::print("{}", formatted);
}

auto ConsoleView::println(std::string const &input) -> void {
    print(input);
    fmt::print("\n");
}

auto ConsoleView::println() -> void {
    println("");
}

auto ConsoleView::displayFiles(const std::vector<std::filesystem::path> &files) -> void {
    auto counter = 1;
    for (auto &f: files) {
        print(f.string());
        print("  <--  ");
        print(std::to_string(counter++));
        println();
    }
}

auto ConsoleView::readNum() -> int {
    auto num = int();
    std::cin >> num;
    return num;
}

auto ConsoleView::readString() -> std::string {
    auto output = std::string();
    std::getline(std::cin >> std::ws, output);
    return output;
}

auto ConsoleView::printCategoryMap(const std::map<Category, std::vector<Password>> &toPrint) -> void {
    for (const auto &entry: toPrint) {
        auto passVec = std::vector<std::string>();
        for (const auto &psw: entry.second)
            passVec.emplace_back(psw.toString());
        fmt::print("Category({}): {}\n", entry.first.getName(), passVec);
    }
}

auto ConsoleView::displayCategoryVec(const std::vector<Category> &catVec) -> void {
    for (const auto &cat: catVec) {
        auto passVec = std::vector<std::string>();
        for (const auto &psw: cat.getPasswordVec())
            passVec.emplace_back(psw.toString());
        fmt::print("Category({}): {}\n", cat.getName(), passVec);
    }
}
