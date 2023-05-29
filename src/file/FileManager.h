//
// Created by Volodymyr on 4/30/2023.
//
#include <string>
#include <vector>
#include <filesystem>

#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H

/**
 * @brief File io class which purpose is to get data from files
 * and parse it to the data understandable by other logic layers
 *
 * @since 1.0
 * @author Volodymyr Yeikovych
 * @see <p><a href="https://github.com/Volodymyr-Yeikovych/PasswordManager">This project on my github</a></p>
 */

class FileManager {
    /**
     * Default data retrieving directory
     */
    std::string defaultDir = R"(C:\Users\Volodymyr\CLionProjects\PJC_PROJECT_PasswordManager\resources\targetFiles)";

public:
    /**
     * Constructs entity of this class with specified default directory
     * @param dir - default directory
     */
    explicit FileManager(const std::string &dir);

    /**
     * Constructs entity of this class with hardcoded default directory.
     */
    FileManager() = default;

    auto operator=(FileManager const &fileManager) -> FileManager & = default;

    /**
     * Returns std::vector consisting of std::filesystem::path elements from the default directory.
     *
     * @return std::vector consisting of std::filesystem::path elements from the default directory.
     */
    auto getFilesVector() -> std::vector<std::filesystem::path>;

    /**
     * Returns std::vector consisting of std::filesystem::path elements from the specified directory.
     *
     * @param dir - directory on the current machine to look for files
     * @return std::vector consisting of std::filesystem::path elements from the specified directory.
     */
    auto getFilesVector(const std::string &dir) -> std::vector<std::filesystem::path>;

    /**
     * Reads file from specified file path
     * and returns vector consisting of std::string elements
     * where each string is a line from the file.
     *
     * @param filePath - file to read
     * @return vector of strings where each string is a separate line of the file to read
     */
    auto getFileLines(const std::filesystem::path &filePath) -> std::vector<std::string>;

    /**
     * Reads file from from specified path and returns std::string consisting of specified file contents
     * @param filePath - file to read
     * @return all file contents in one string
     */
    auto getFileContents(const std::filesystem::path &filePath) -> std::string;

    /**
     * Overrides all data from specified file to the content of specified std::string
     * @param fileContent - file to override
     * @param filePath
     * @returns true - if file was overridden
     * @returns false - otherwise
     */
    auto setFileContents(const std::string &fileContent, const std::filesystem::path &filePath) -> bool;

    auto getU32FileContents(const std::filesystem::path &filePath) -> std::u32string;

    auto setU32FileContents(const std::u32string &fileContent, const std::filesystem::path &filePath) -> bool;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_FILEMANAGER_H
