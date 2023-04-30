cmake_minimum_required(VERSION 3.25)
project(PJC_PROJECT_PasswordManager)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

add_executable(PJC_PROJECT_PasswordManager main.cpp Managers/FileManager.cpp Managers/FileManager.h Managers/ProgramManager.cpp Managers/ProgramManager.h Managers/ConsoleManager.cpp Managers/ConsoleManager.h)
target_link_libraries(PJC_PROJECT_PasswordManager fmt)
