cmake_minimum_required(VERSION 3.15)
project("Feature Selection with Nearest Neighbor")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. TREAT WARNINGS AS ERRORS ---
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

# --- 2. OUTPUT DIRECTORY (From your guide) ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# --- 3. DEFINE SOURCES ---
set(CORE_SOURCES ./lib/algorithms.cpp)

# --- 4. EXECUTABLE: THE MAIN GAME ---
#add_executable(main ./lib/main.cpp ${CORE_SOURCES})
add_executable(SearchProgram ./lib/main.cpp)