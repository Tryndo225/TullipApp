cmake_minimum_required(VERSION 3.10)
project(TullipApp VERSION 1.0 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6 (version 6.9) components
find_package(Qt6 6.9 REQUIRED COMPONENTS Widgets Core Gui)

# Collect all source, header, and UI files
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

# Define the executable target
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include current source directory for headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against Qt6 libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
)

# (Optional) Installation settings
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
