#include "src/controller/ProgramController.h"
auto main() -> int {
    FileManager fileManager = FileManager();
    ProgramController manager = ProgramController(fileManager, ConsoleView(), CryptographyManager(fileManager), PasswordMapper());
    manager.start();
}
