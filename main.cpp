#include "src/managers/ProgramManager.h"

auto main() -> int {
    ProgramManager manager = ProgramManager(FileManager(), ConsoleManager(), CryptographyManager());
    manager.start();
}
