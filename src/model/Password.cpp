//
// Created by Volodymyr on 5/2/2023.
//

#include <string>
#include "Category.h"
#include "Password.h"

Password::Password(const std::string &name, const std::string &passText,
                   const Category &category) : name(name), passText(passText), category(category) {
    this->name = name;
    this->passText = passText;
    this->category = category;
}

auto Password::setWebsite(const std::string &website) -> void {
    this->website = website;
}

auto Password::setLogin(const std::string &login) -> void {
    this->login = login;
}
