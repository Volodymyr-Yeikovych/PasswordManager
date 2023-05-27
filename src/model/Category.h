//
// Created by Volodymyr on 5/2/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
#define PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H

#include <string>
#include <vector>
#include "Password.h"

class Category {
    std::string name;
    std::vector<Password> categoryPasswords;

    public:
        explicit Category(const std::string &name);
        explicit Category(const std::string &name, const std::vector<Password> &passVec);
        Category() = default;
        auto operator==(const Category &other) const -> bool;
//        auto operator<=>(const Category &other) const -> bool;
        auto operator<(const Category &other) const -> bool;
//        auto operator>(const Category &other) const -> bool;
        auto addPassword(const Password &password) -> bool;
        auto removePassword(const Password &password) -> bool;
        auto isPresent(const Password &password) -> bool;
        auto getIterator(const Password &password) -> std::vector<Password>::iterator;
        auto getMatchingVec(const Password &password) -> std::vector<Password>;
        auto getName() const -> std::string;
        auto getPasswordVec() const -> std::vector<Password>;
        auto sortByLength(const std::string &field, const std::string &order) -> void;
        auto sortAlphabetically(const std::string &field, const std::string &order) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
