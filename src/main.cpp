#include <vector>
#include "../Managers/ProgramManager.h"

using std::vector;


auto main() -> int {
    ProgramManager manager = ProgramManager(FileManager(), ConsoleManager(), CryptographyManager());
    manager.start();
}
