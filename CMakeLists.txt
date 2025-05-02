cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(Minesweeper_Backtracking)

include(FetchContent)

# ✅ Release 输出路径一致，方便 CI 构建
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# ✅ 明确关闭 Malena 的不必要模块，减少 CI 构建时间
set(MALENA_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(MALENA_BUILD_TESTS OFF CACHE INTERNAL "")
set(MALENA_BUILD_DOCS OFF CACHE INTERNAL "")

FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.4
)


FetchContent_GetProperties(malena)
if(NOT malena_POPULATED)
    FetchContent_Populate(malena)
    add_subdirectory(${malena_SOURCE_DIR} ${malena_BINARY_DIR})
endif()

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

# ✅ 链接 Malena 库
target_link_libraries(${PROJECT_NAME} PRIVATE Malena)


## Copy the image files to the build directory, so that we can use relative paths
file(COPY ${CMAKE_SOURCE_DIR}/Image DESTINATION ${CMAKE_BINARY_DIR})