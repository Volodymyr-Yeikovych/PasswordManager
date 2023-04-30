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

    consoleManager.println(
            "Choose files from list to decrypt/encrypt.");
    consoleManager.println("Type from 1 to n where n is the number of a last file.");
    consoleManager.println("If number out of bounds is printed, absolute path should be provided.");
    consoleManager.displayFiles(fileManager.getFilesVector());
    consoleManager.print("Enter here: ");
    auto input = consoleManager.readNum();
    consoleManager.println();
    consoleManager.println(input);
    consoleManager.println(std::to_string(numOfKnownFiles));
}



