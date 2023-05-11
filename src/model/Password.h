//
// Created by Volodymyr on 5/2/2023.
//
#pragma once

#include <string>

#ifndef PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H
#define PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

class Password{
    std::string name;
    std::string passText;
    std::string website;
    std::string login;

public:
//    auto operator==(const Password &password) -> bool;
    bool operator==(const Password &password) const = default;
    bool operator<=>(const Password &password) const = default;
    Password(const std::string& name, const std::string& passText);
    Password() = default;
    auto setWebsite(const std::string& website) -> void;
    auto setLogin(const std::string& login) -> void;
};