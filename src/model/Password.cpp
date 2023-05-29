//
// Created by Volodymyr on 5/2/2023.
//

#include <string>
#include "Password.h"

//auto Password::operator==(const Password &other) -> bool {
//    if (&other == this) return true;
//    bool equalName = other.name == this->name;
//    bool equalPassword = other.password == this->password;
//    bool equalWebsite = other.website == this->website;
//    bool equalLogin = other.login == this->login;
//    return equalName && equalPassword && equalWebsite && equalLogin;
//}

Password::Password(const std::string &name, const std::string &password) : name(name), password(password) {
    this->name = name;
    this->password = password;
}


auto Password::setWebsite(const std::string &website) -> void {
    this->website = website;
}

auto Password::setLogin(const std::string &login) -> void {
    this->login = login;
}

auto Password::setName(const std::string &name) -> void {
    this->name = name;
}

auto Password::setPassword(const std::string &password) -> void {
    this->password = password;
}

auto Password::getName() const -> std::string {
    return name;
}

auto Password::getPassword() const -> std::string {
    return password;
}

auto Password::getLogin() const -> std::string {
    return login;
}

auto Password::getWebsite() const -> std::string {
    return website;
}

auto Password::editMatching(const Password &password) -> void {
    auto nameMatches = !password.name.empty();
    auto passwordMatches = !password.password.empty();
    auto websiteMatches = !password.website.empty();
    auto loginMatches = !password.login.empty();

    if (nameMatches) this->name = password.name;
    if (passwordMatches) this->password = password.password;
    if (websiteMatches) this->website = password.website;
    if (loginMatches) this->login = password.login;
}

auto Password::toString() const -> std::string {
    return "Password{Name(" + name + "), Password(" + password + "), Website(" + website + "), Login(" + login + ")}";
}