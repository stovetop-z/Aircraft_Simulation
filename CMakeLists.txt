cmake_minimum_required(3.0)

project(Aircraft VERSION 1.0)

add_executable(aircract main.cpp aircraft.cpp)
target_include_directories(YourProjectTarget PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include # Add this line
)