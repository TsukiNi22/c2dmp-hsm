cmake_minimum_required(VERSION 3.20)
set(TARGET c2dmp-hsm)
project(${TARGET} LANGUAGES CXX)

# =========================
# Compilateur & Standard
# =========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Moderne compilation -fPIE

# =========================
# Warnings
# =========================
add_compile_options(
    -W
    -Wall
    -Wextra
    -Wpedantic
    -Wunused-parameter
    -Wshadow
    -Wuninitialized
)

# =========================
# Sources
# =========================
set(SRC
    # Test execution
    main.cpp

    # Algorithm
    c2dmp-hsm/c2dmp-hsm_optimized.cpp
    c2dmp-hsm/c2dmp-hsm_simplified.cpp
)
add_executable(${TARGET} ${SRC})
#add_library(${TARGET} STATIC ${SRC})
#add_library(${TARGET} SHARED ${SRC})

# =========================
# Dependencies
# =========================
target_include_directories(${TARGET} PUBLIC include)

# =========================
# Modes
# =========================
target_compile_options(${TARGET} PRIVATE
    $<$<CONFIG:debug>:-g -ggdb3>
    $<$<CONFIG:optimized>:-O3 -ffast-math -flto -funroll-loops -fvectorize -fslp-vectorize -mtune=native -fno-plt -pipe -DNDEBUG>
)

# =========================
# Utils
# =========================
add_custom_target(get_unregistered_files
    COMMAND bash ${CMAKE_SOURCE_DIR}/cmake/script/check_files.sh unregistered ${SRC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
