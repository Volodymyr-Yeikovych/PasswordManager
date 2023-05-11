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
    std::vector<Password> categoryPasswords = std::vector<Password>();

    public:
        Category(const std::string &name);
        auto addPassword(const Password &password) -> bool;
        auto removePassword(const Password &password) -> bool;
        auto isPresent(const Password &password) -> bool;
        auto getIterator(const Password &password) -> std::vector<Password>::iterator;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
