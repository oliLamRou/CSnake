cmake_minimum_required(VERSION 3.31)

project(CSnake)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})