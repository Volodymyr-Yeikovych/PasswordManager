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

auto operator<(const Category &left, const Category &right) -> bool {
    return left.getName().size() < right.getName().size();
}

auto operator<=>(const Category &left, const Category &right) -> bool {
    auto ls = left.getName().size();
    auto rs = right.getName().size();
    if (ls == rs) return ls == rs;
    if (ls < rs) return ls < rs;
    return ls > rs;
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



