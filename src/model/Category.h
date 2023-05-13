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
        auto operator==(const Category &other) const -> bool = default;
        auto operator<=>(const Category &other) const -> bool;
        auto operator<(const Category &other) const -> bool;
        auto addPassword(const Password &password) -> bool;
        auto removePassword(const Password &password) -> bool;
        auto isPresent(const Password &password) -> bool;
        auto getIterator(const Password &password) -> std::vector<Password>::iterator;
        auto getMatchingVec(const Password &password) -> std::vector<Password>;
        auto getName() const -> std::string;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
