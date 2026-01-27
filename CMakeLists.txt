cmake_minimum_required(VERSION 3.16)

project(HandShake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt (Widgets module)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# List of source files
add_executable(HandShake
   src/App/main.cpp
)

# Include directories for headers
target_include_directories(HandShake PRIVATE
    src
)

# Link Qt libraries
target_link_libraries(HandShake
    Qt6::Widgets
)
