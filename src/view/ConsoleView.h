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
 * A console io class which purpose is to display data
 * in visual representation or transform input from console into data.
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */
class ConsoleView {

public:
    /**
     * Prints string into console without new line.
     * @param input - string to print
     */
    auto print(std::string const &input) -> void;

    /**
     * Prints string into console with new line.
     * @param input - string to print
     */
    auto println(std::string const &input) -> void;

    /**
     * Prints new line into console
     */
    auto println() -> void;

    /**
     * Transforms given path vector into string representation and prints it to console.
     * @param files - given path vector
     */
    auto displayFiles(const std::vector<std::filesystem::path> &files) -> void;

    /**
     * Reads number from console
     * @return number that was read
     */
    auto readNum() -> int;

    /**
     * Reads string from console
     * @return string that was read
     */
    auto readString() -> std::string;

    /**
     * Transforms std::map of Category.cpp and std::vector of Password.cpp to string representation and prints it to console
     * @param toPrint - map to print
     */
    auto printCategoryMap(const std::map<Category, std::vector<Password>> &toPrint) -> void;

    /**
     * Transforms std::vector of Category.cpp to string and prints it to console
     * @param catVec - categories vector to print
     */
    auto displayCategoryVec(const std::vector<Category> &catVec) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CONSOLEVIEW_H
