//
// Created by Volodymyr on 5/2/2023.
//

#include <string>
#include "Category.h"
#include "Password.h"

//auto Password::operator==(const Password &other) -> bool {
//    if (&other == this) return true;
//    bool equalName = other.name == this->name;
//    bool equalPassword = other.passText == this->passText;
//    bool equalWebsite = other.website == this->website;
//    bool equalLogin = other.login == this->login;
//    return equalName && equalPassword && equalWebsite && equalLogin;
//}

Password::Password(const std::string &name, const std::string &passText) : name(name), passText(passText) {
    this->name = name;
    this->passText = passText;
}

auto Password::setWebsite(const std::string &website) -> void {
    this->website = website;
}

auto Password::setLogin(const std::string &login) -> void {
    this->login = login;
}

