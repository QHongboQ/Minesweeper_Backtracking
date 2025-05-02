cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(Minesweeper_Backtracking)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(FetchContent)

set(MALENA_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(MALENA_BUILD_TESTS OFF CACHE INTERNAL "")
set(MALENA_BUILD_DOCS OFF CACHE INTERNAL "")
set(MALENA_USE_SYSTEM_SFML OFF CACHE INTERNAL "")


FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.4
)
FetchContent_MakeAvailable(malena)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Board.h
        src/Board.cpp
        src/Node.h
        src/Node.cpp
        src/TileSprite.h
        src/TileSprite.cpp
        src/MinesweeperApp.h
        src/MinesweeperApp.cpp
        src/BackTracking.h
        src/BackTracking.cpp
        src/Highlighter.h
        src/Highlighter.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Malena::Malena)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Image $<TARGET_FILE_DIR:${PROJECT_NAME}>/Image
)
