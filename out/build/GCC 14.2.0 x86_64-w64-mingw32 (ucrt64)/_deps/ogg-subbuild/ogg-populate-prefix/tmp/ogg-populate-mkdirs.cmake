# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-src")
  file(MAKE_DIRECTORY "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-src")
endif()
file(MAKE_DIRECTORY
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-build"
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix"
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/tmp"
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/src"
  "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/out/build/GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
