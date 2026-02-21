cmake_minimum_required(VERSION 3.15)
project(Feature Selection with Nearest Neighbor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. COVERAGE FLAGS (Wrapped for Safety) ---
#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0 -fprofile-arcs -ftest-coverage")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lgcov")
#endif()

# --- 2. OUTPUT DIRECTORY (From your guide) ---
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# --- 3. DEFINE SOURCES ---
# set(CORE_SOURCES ./lib/Puzzle.cpp ./lib/Solver.cpp)

# --- 4. EXECUTABLE: THE MAIN GAME ---
#add_executable(main ./lib/main.cpp ${CORE_SOURCES})
add_executable(SearchProgram ./lib/main.cpp)