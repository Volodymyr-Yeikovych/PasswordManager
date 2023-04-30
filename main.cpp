#include <vector>
#include <filesystem>
#include "Managers/ProgramManager.h"

using std::vector;


auto main() -> int {
    ProgramManager manager = ProgramManager(FileManager(), ConsoleManager());
    manager.start();
}
