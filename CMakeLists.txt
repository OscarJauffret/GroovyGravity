cmake_minimum_required(VERSION 3.30)
project(GroovyGravity)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 1. On macOS, look in Homebrew's directory for libraries
if (APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif ()

# 2. Find the required graphics libraries
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
# GLM is header-only. Its bundled CMake config can be too old for modern CMake,
# so find it quietly and fall back to a plain interface target on system headers.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
find_package(glm QUIET)
if (NOT TARGET glm::glm)
    add_library(glm::glm INTERFACE IMPORTED)
endif ()

# 3. Define the executable (assumes main.cpp is in the same folder)
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/object.cpp
        src/spaceTime.cpp
        src/objectUtils.cpp
)

add_executable(test
    src/test.cpp
)

# 3.5 Get the graphics library
include(FetchContent)
FetchContent_Declare(
        graphics
        GIT_REPOSITORY https://github.com/OscarJauffret/graphics.git
        GIT_TAG        main          # better: pin a commit SHA, see below
)
FetchContent_MakeAvailable(graphics)

# 4. Link the libraries
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
        GLEW::GLEW
        glm::glm
        OpenGL::GL
        graphics::graphics
)

# On Mac, we also need the system's App frameworks
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
endif ()

# 5. Include directories (ensures headers are found)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external)
if (APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE "/opt/homebrew/include")
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE
        SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders")

set(COMPILER_FLAGS -O3)
target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)