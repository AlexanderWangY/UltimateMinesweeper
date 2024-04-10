cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper)

# Set the directory for SFML
set(SFML_DIR "/lib/cmake/SFML")

# Define the source and asset directories
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(ASSET_DIR "${CMAKE_SOURCE_DIR}/src/files")
set(BUILD_SHARED_LIBS OFF)

# Copy resource files to build directory
file(COPY ${ASSET_DIR} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML components
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# List your source files
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")

# Add the executable target
add_executable(minesweeper ${SOURCE_FILES} ${SOURCES})

# Link SFML libraries
target_link_libraries(minesweeper 
    sfml-system sfml-window sfml-graphics sfml-audio
    ${SFML_DEPENDENCIES}
    pthread sfml-network
)
