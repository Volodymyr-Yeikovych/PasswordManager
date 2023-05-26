//
// Created by Volodymyr on 5/2/2023.
//

#include <algorithm>
#include "Category.h"

Category::Category(const std::string &name) {
    this->name = name;
    this->categoryPasswords = std::vector<Password>();
}

Category::Category(const std::string &name, const std::vector<Password> &passVec) {
    this->name = name;
    this->categoryPasswords = passVec;
}

auto Category::addPassword(const Password &password) -> bool {
    categoryPasswords.push_back(password);
    return true;
}

auto Category::isPresent(const Password &password) -> bool {
    return !(std::ranges::find(categoryPasswords, password) == categoryPasswords.end());
}

auto Category::getIterator(const Password &password) -> std::vector<Password>::iterator {
    return std::ranges::find(categoryPasswords, password);
}

auto Category::removePassword(const Password &password) -> bool {
    if (isPresent(password)) {
        categoryPasswords.erase(getIterator(password));
        return true;
    }
    return false;
}

auto Category::getName() const -> std::string {
    return this->name;
}

auto Category::getMatchingVec(const Password &password) -> std::vector<Password> {
    auto matchingVec = std::vector<Password>();
    for (auto const &entry : categoryPasswords) {
        auto matchingName = password.getName().empty() || password.getName() == entry.getName();
        auto matchingPassword = password.getPassword().empty() || password.getPassword() == entry.getPassword();
        auto matchingWebsite =  password.getWebsite().empty() || password.getWebsite() == entry.getWebsite();
        auto matchingLogin = password.getLogin().empty() || password.getLogin() == entry.getLogin();
        if (matchingName && matchingPassword && matchingWebsite && matchingLogin) matchingVec.emplace_back(entry);
    }
    return matchingVec;
}

auto Category::operator<(const Category &other) const -> bool {
    auto tNameLen = this->getName();
    auto oNameLen = other.getName();
    return tNameLen < oNameLen;
}

auto Category::operator==(const Category &other) const -> bool {
    return this->getName() == other.getName() && std::ranges::equal(this->getPasswordVec(), other.getPasswordVec());
}

auto Category::getPasswordVec() const -> std::vector<Password> {
    return categoryPasswords;
}



