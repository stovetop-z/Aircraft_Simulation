# Aircraft Project

This project appears to be a C++ application with Python scripting capabilities, structured as follows:

## Project Structure

- `CMakeLists.txt`: CMake build configuration file.
- `include/`: Directory for C++ header files.
- `lib/`: Directory for compiled libraries.
- `run.py`: Python script, likely used for running or orchestrating the application.
- `scripts/`: Directory for additional scripts (e.g., build scripts, utility scripts).
- `src/`: Directory for C++ source code files.
- `tests/`: Directory for project tests.

## Building the Project

This project uses CMake for its build system. To build the project, navigate to the root directory and execute the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Project

After building, you can likely run the main application or execute the `run.py` script. Further instructions would depend on the specific entry points defined within the C++ and Python code.

```bash
# Example for C++ executable (replace `your_executable` with the actual name)
./build/your_executable

# Example for Python script
python run.py
```

## Testing

Tests are located in the `tests/` directory. If using CTest with CMake, you can run tests from the build directory:

```bash
cd build
ctest
```