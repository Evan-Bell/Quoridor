cmake_minimum_required(VERSION 3.16)
project(Quor LANGUAGES CXX)

# Set output directories and compiler flags
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_compile_options(-Wall)


set(IMGUI_SFML_INCLUDE ${IMGUI_DIR})


# Fetch ImGui
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

# add_executable(main console/main.cpp)
# target_link_libraries(main PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
# target_compile_features(main PRIVATE cxx_std_17)










# Define executable and sources
add_executable(z_output
    console/main.cpp
    console/game.cpp
    console/game_state.cpp
    console/render.cpp
    console/minimax.cpp
    console/randomBot.cpp
)

# Link SFML libraries
target_link_libraries(z_output PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Link ImGui-SFML
target_link_libraries(z_output PRIVATE
    ImGui-SFML::ImGui-SFML
)

# Include directories
target_include_directories(z_output PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/console
    ${IMGUI_SFML_INCLUDE}  # Add ImGui include directory
)

# Custom command to run the executable
add_custom_target(run
    COMMAND ./bin/z_output
    DEPENDS z_output
    COMMENT "Running executable..."
)

# Custom command to clean build artifacts
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/z_output
    COMMENT "Cleaning up..."
)
