cmake_minimum_required(VERSION 3.24.2)
project(PJC_PROJECT_PasswordManager)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
#        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

add_executable(PJC_PROJECT_PasswordManager main.cpp src/file/FileManager.cpp src/file/FileManager.h src/controller/ProgramController.cpp src/controller/ProgramController.h src/view/ConsoleView.cpp src/view/ConsoleView.h src/enc/CryptographyManager.cpp src/enc/CryptographyManager.h src/model/Password.cpp src/model/Password.h src/model/Category.cpp src/model/Category.h main.cpp main.cpp src/mapper/PasswordMapper.cpp src/mapper/PasswordMapper.h)
target_link_libraries(PJC_PROJECT_PasswordManager fmt)
