# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.25.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(me-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[C:/Program Files/Git/cmd/git.exe]==])
set(GIT_VERSION_STRING [==[2.39.1.windows.1]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[C:/Program Files/Git/cmd/git.exe;2.39.1.windows.1]==]
)


include(ExternalProject)
ExternalProject_Add(me-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/Volodymyr-Yeikovych/PswMngr" "GIT_TAG" "bfec5f8d9aef4d8eaa5d51642dd2adac0910f699"
                    SOURCE_DIR          "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-src"
                    BINARY_DIR          "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


