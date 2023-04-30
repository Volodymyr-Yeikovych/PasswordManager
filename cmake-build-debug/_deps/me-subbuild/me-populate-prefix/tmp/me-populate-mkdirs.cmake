# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-src"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-build"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/tmp"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/src/me-populate-stamp"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/src"
  "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/src/me-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/src/me-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Volodymyr/CLionProjects/PJC_PROJECT_PasswordManager/cmake-build-debug/_deps/me-subbuild/me-populate-prefix/src/me-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
