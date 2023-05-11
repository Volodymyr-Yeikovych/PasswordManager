//
// Created by Volodymyr on 5/2/2023.
//

#include <algorithm>
#include "Category.h"

Category::Category(const std::string &name) {
    this->name = name;
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



