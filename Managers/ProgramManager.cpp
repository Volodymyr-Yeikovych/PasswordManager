//
// Created by Volodymyr on 4/30/2023.
//

#include "ProgramManager.h"

auto ProgramManager::operator=(const ProgramManager &other) -> ProgramManager {
    this->fileManager = other.fileManager;
    this->consoleManager = other.consoleManager;
    return *this;
}

ProgramManager::ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager) : fileManager(fileManager) {
    this->fileManager = fileManager;
    this->consoleManager = consoleManager;
}

auto ProgramManager::start() -> void {
    auto numOfKnownFiles = fileManager.countFilesInDefDir();
    auto pathVector = fileManager.getFilesVector();
    consoleManager.println(
            "Choose files from list to decrypt/encrypt.");
    consoleManager.println("Type from 1 to n where n is the number of a last file.");
    consoleManager.println("If number out of bounds is printed, absolute path should be provided.");
    consoleManager.displayFiles(pathVector);
    consoleManager.print("Enter here: ");
    auto input = consoleManager.readNum();
    auto customPath = std::filesystem::path();
    if (inputOutOfBounds(input, pathVector.size())) {
        consoleManager.print("Provide custom path: ");
        customPath = consoleManager.readPath();
    } else customPath = pathVector.at(input - 1);
    consoleManager.println(customPath.string());
    consoleManager.println(std::to_string(numOfKnownFiles));
}

auto ProgramManager::inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool {
    if (input <= 0 || input > poolSize) return true;
    return false;
}



