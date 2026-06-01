cmake_minimum_required(VERSION 3.10)
project(AerospaceSim VERSION 1.0 LANGUAGES CXX)

# Require modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Strict adherence to the standard

# ---------------------------------------------------------
# 1. THE CORE PHYSICS LIBRARY
# ---------------------------------------------------------
# We compile the physics engine into a standalone library.
# This allows us to link it to the main flight loop AND the tests independently.
add_library(flight_core 
    src/physics/aerodynamics.cpp
    src/physics/state_vector.cpp
    src/math/quaternion.cpp
    src/math/tensor.cpp
    src/computation/mem.cpp
)

# Tell the core library where its public headers are
target_include_directories(flight_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---------------------------------------------------------
# 2. THE MAIN FLIGHT EXECUTIVE
# ---------------------------------------------------------
add_executable(flight_sim src/main.cpp)
target_link_libraries(flight_sim PRIVATE flight_core)

# ---------------------------------------------------------
# 3. VERIFICATION & TESTING
# ---------------------------------------------------------
enable_testing() # Turns on CMake's CTest harness

# Math Tests
add_executable(test_math tests/test_math.cpp)
target_link_libraries(test_math PRIVATE flight_core)
add_test(NAME MathVerification COMMAND test_math)

# Physics Tests
add_executable(test_physics tests/test_physics.cpp)
target_link_libraries(test_physics PRIVATE flight_core)
add_test(NAME PhysicsVerification COMMAND test_physics)