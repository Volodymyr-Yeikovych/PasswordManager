#include "src/managers/ProgramManager.h"

auto main() -> int {
    FileManager fileManager = FileManager();
    ProgramManager manager = ProgramManager(fileManager, ConsoleManager(), CryptographyManager(fileManager), PasswordMapper());
    manager.start();
}
