//
// Created by Volodymyr on 5/2/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
#define PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H

#include <string>
#include <vector>
#include "Password.h"

/**
 * @brief This class represents single entity of password category.
 *
 * @long Password category contains of n-number of Password.cpp entities.
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class Category {
    /**
     * Category name
     */
    std::string name;
    /**
     * Passwords that belong to this category
     */
    std::vector<Password> categoryPasswords;

public:
    /**
     * Constructs category entity with specified name
     * @param name - category name
     */
    explicit Category(const std::string &name);

    /**
     * Constructs category entity with specified name and password vector
     * @param name - category name
     * @param passVec - password vector
     */
    explicit Category(const std::string &name, const std::vector<Password> &passVec);

    /**
     * Constructs empty category with no name
     */
    Category() = default;

    auto operator==(const Category &other) const -> bool;

    auto operator<(const Category &other) const -> bool;

    /**
     * Adds password to this category password vector
     * @param password - password to add
     * @returns true - if password was added to vector
     * @returns false - otherwise
     */
    auto addPassword(const Password &password) -> bool;

    /**
     * Removes password from this category password vector
     * @param password - password to remove
     * @returns true - if password was found and removed
     * @returns false - otherwise
     */
    auto removePassword(const Password &password) -> bool;

    /**
     * Returns whether given password is present in this category password vector
     * @param password - given password
     * @returns true - if password is present
     * @returns false - otherwise
     */
    auto isPresent(const Password &password) -> bool;

    /**
     * Returns iterator to the given password of this category password vector.
     * @param password - given password to which we need iterator
     * @returns iterator - to the given password if such exists
     * @returns categoryPasswords.end() - if no iterator was found
     */
    auto getIterator(const Password &password) -> std::vector<Password>::iterator;

    /**
     * @brief Returns sub-vector of this category passwords vector,
     * consisting of passwords that match to the given password.
     *
     * @long Password is considered to be a match if all the fields
     * of the given password either matches the password or are empty.
     *
     * @param password - given password
     * @return sub-vector of this category passwords vector,
     * consisting of elements that match to the given password.
     */
    auto getMatchingVec(const Password &password) -> std::vector<Password>;

    /**
     * Returns the name of this category
     * @return the name of this category
     */
    auto getName() const -> std::string;

    /**
     * Returns copy of this category password vector
     * @return copy of this category password vector
     */
    auto getPasswordVec() const -> std::vector<Password>;

    /**
     * Sorts this category password vector by length according to the given parameters.
     *
     * @param field - field of Password.cpp to sort, by (name/password/website/login)
     * @param order - sorting order (ascending/descending)
     */
    auto sortByLength(const std::string &field, const std::string &order) -> void;

    /**
     * Sorts this category password vector alphabetically according to the given parameters.
     *
     * @param field - field of Password.cpp to sort, by (name/password/website/login)
     * @param order - sorting order (ascending/descending)
     */
    auto sortAlphabetically(const std::string &field, const std::string &order) -> void;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_CATEGORY_H
