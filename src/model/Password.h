//
// Created by Volodymyr on 5/2/2023.
//
#pragma once

#include <string>

#ifndef PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H
#define PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

#endif //PJC_PROJECT_PASSWORDMANAGER_PASSWORD_H

/** <p>This class is a single entity of a password save file
 * and represents exactly one password with 4 parameters, 2 of which are optional.
 *
 * @optional If parameter is optional it may or may not be present in password.
 * If field is set to empty it means that this field is not present.
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class Password {
    /**
     * name of the password
     **/
    std::string name;
    /**
     * password itself
     **/
    std::string password;
    /**
     * website or service name, this param is optional.
     */
    std::string website;
    /**
     * login name, this param is optional.
     */
    std::string login;

public:
    bool operator==(const Password &password) const = default;

    bool operator<=>(const Password &password) const = default;

    /**
     * Constructs a password entity with specified name and password
     * @param name - name of the password
     * @param password - password
     */
    Password(const std::string &name, const std::string &password);

    /**
     * Constructs a password entity with all empty fields
     */
    Password() = default;

    /**
     * Sets field website value to the given argument value
     *
     * @param website - website or service name to set
     */
    auto setWebsite(const std::string &website) -> void;

    /**
     * Sets field login value to the given argument value
     *
     * @param login - login to set
     */
    auto setLogin(const std::string &login) -> void;

    /**
     * Sets field name value to the given argument value
     *
     * @param name - name to set
     */
    auto setName(const std::string &name) -> void;

    /**
     * Sets field password value to the given argument value
     *
     * @param password - password to set
     */
    auto setPassword(const std::string &password) -> void;

    /**
     * Returns the value of website field
     *
     * @return the value of website field
     */
    auto getWebsite() const -> std::string;

    /**
     * Returns the value of login field
     *
     * @return the value of login field
     */
    auto getLogin() const -> std::string;

    /**
     * Returns the value of name field
     *
     * @return the value of name field
     */
    auto getName() const -> std::string;

    /**
     * Returns the value of password field
     *
     * @return the value of password field
     */
    auto getPassword() const -> std::string;

    /**
     * Sets fields of this password to values of the given password
     * if given password fields are not empty.
     *
     * @param password - given password
     */
    auto editMatching(const Password &password) -> void;

    /**
     * @brief Returns string representation of this password entity.
     *
     * @long The string representation consists of all 4 fields of the class
     * enclosed in a curly braces and a class name ("Password{}").
     * Each field is preceded by the name of this exact field and
     * then enclosed in a parenthesis FieldName(value).
     *
     * @example Password{Name(someName), Password(somePassword), Website(someWebSite), Login(theLogin)}
     * @return string representation of this password entity
     */
    auto toString() const -> std::string;
};