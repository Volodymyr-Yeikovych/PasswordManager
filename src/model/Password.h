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
    std::string password;
    std::string website;
    std::string login;

public:
    bool operator==(const Password &password) const = default;
    bool operator<=>(const Password &password) const = default;
    Password(const std::string& name, const std::string& passText);
    Password() = default;
    auto setWebsite(const std::string &website) -> void;
    auto setLogin(const std::string &login) -> void;
    auto setName(const std::string &name) -> void;
    auto setPassword(const std::string &password) -> void;
    auto getWebsite() const -> std::string;
    auto getLogin() const -> std::string;
    auto getName() const -> std::string;
    auto getPassword() const -> std::string;
    auto editMatching(const Password &password) -> void;
};