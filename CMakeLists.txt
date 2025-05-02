cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(Minesweeper_Backtracking)

# ✅ 为 Visual Studio 多配置构建器指定 Release 模式
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

# ✅ Release 输出路径一致，方便 CI 构建
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(FetchContent)

# ✅ 明确关闭 Malena 的不必要模块，减少 CI 构建时间
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

# ✅ 正确链接命名空间目标
target_link_libraries(${PROJECT_NAME} PRIVATE Malena::Malena)

# ✅ 拷贝资源文件（Image 文件夹）
file(COPY ${CMAKE_SOURCE_DIR}/Image DESTINATION ${CMAKE_BINARY_DIR})