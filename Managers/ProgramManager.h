//
// Created by Volodymyr on 4/30/2023.
//
#pragma once
#ifndef PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
#define PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H


#include "FileManager.h"
#include "ConsoleManager.h"

class ProgramManager {
    FileManager fileManager;
    ConsoleManager consoleManager;
    public:
        explicit ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager);
        auto start() -> void;
        auto operator=(ProgramManager const &programManager) -> ProgramManager;
};


#endif //PJC_PROJECT_PASSWORDMANAGER_PROGRAMMANAGER_H
