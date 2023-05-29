//
// Created by Volodymyr on 5/1/2023.
//
#pragma once

#include <filesystem>
#include <vector>
#include "../file/FileManager.h"
#include "../view/ConsoleView.h"

#ifndef PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H

/**
 * Cryptography responsible class which enables encryption and decryption of data.
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class CryptographyManager {
    /**
     * Entity of file io class that helps to retrieve data to encrypt/decrypt
     */
    FileManager fileManager;
    /**
     * random sequence of 128 chars to make encryption of data harder to decipher
     */
    const std::vector<std::string> PSW_ENC_VEC = {"w", "-", "R", "3", "6", "W", "r", "+", "D", "#", "a", "M", "F", "-",
                                                  "m", "V", "7", "f", "!", "M", "=", "5", "!", "7", "a", "4", "r", "t",
                                                  "p", "F", "C", "V", "_", "u", "$", "O", "2", "J", "+", "=", "I", "7",
                                                  "X", "I", "c", "b", "J", "C", "e", "A", "R", "S", "n", "_", "X", "6",
                                                  "r", "o", "+", "@", "W", "S", "9", "z", "F", "R", "w", "3", "F", "%",
                                                  "K", "H", "g", "S", ")", "u", "C", "*", "c", "l", "J", "?", "G", "K",
                                                  "f", "?", "3", "X", "@", "L", "3", "S", "N", "$", "!", "S", "V", "6",
                                                  "E", "A", "3", "7", "1", "F", "x", "t", "j", "L", ">", "h", "=", "F",
                                                  "W", "6", "K", "b", "q", "X", "m", "3", "M", "D", "L", "p", "i", "b",
                                                  "q", "a"};
public:
    /**
     * Constructs entity this class with specified file io
     * @param fileManager - file io
     */
    CryptographyManager(const FileManager &fileManager);

    auto operator=(const CryptographyManager &other) -> CryptographyManager &;
    /**
     * Encrypts file from the specified path with specified password
     * @param path - file to encrypt
     * @param encPass - password to encrypt with
     */
    auto encrypt(const std::filesystem::path &path, const std::string &encPass) -> void;

    /**
     * Decrypts file from the specified pass using specified password.
     *
     * @param path - file to decrypt
     * @param decPass - password to decrypt with
     * @return last time when file was read message
     */
    auto decrypt(const std::filesystem::path &path, const std::string &decPass) -> std::string;

private:
    auto getCryptoSequence(const std::string &encPsw) -> std::string;
    auto appendTime(std::string &contents) -> void;
    auto getLastTimeModifiedMsg(std::string &contents) -> std::string;

};

#endif //PJC_PROJECT_PASSWORDMANAGER_CRYPTOGRAPHYMANAGER_H