//
// Created by Volodymyr on 5/2/2023.
//
#pragma once

#include <string>
#include "Category.h"

#ifndef PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H
#define PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

class Password{
    std::string name;
    std::string passText;
    Category category;
    std::string website;
    std::string login;

public:
    Password(const std::string& name, const std::string& passText, const Category& category);

    auto setWebsite(const std::string& website) -> void;
    auto setLogin(const std::string& login) -> void;
};