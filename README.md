# Advent of Code Challenge 🎄

This project contains my solutions for Advent of Code challenges in 2025. It includes a main program that handles file input and output, and a modular structure for implementing individual challenge solutions. The project is built with CMake and uses modern C++ features.

## 🛠️ Tech Stack

- **Language:** C++20
- **Build System:** CMake
- **Standard Library:** STL (Standard Template Library)
- **Main Program:** `main.cpp`, `main.h`

## 📦 Getting Started

### Prerequisites

- A C++20 compatible compiler (e.g., GCC, Clang)
- CMake (version 3.15 or higher)

### Installation

1.  **Clone the repository:**

    ```bash
    git clone <repository_url>
    cd <repository_directory>
    ```

2.  **Install VCPKG**

    - [VCPKG Install](https://github.com/microsoft/vcpkg)
    - Set Environment Variable `VCPKG_ROOT` to root of VCPKG install

3. **Configure the project with CMake:**

    Select preset:

    ```bash
    # For Windows
    cmake --preset x64-windows-debug
    # For Linux
    cmake --preset x64-linux-debug
    ```

    You need to specify the challenge to build using the `AOC_CHAL` option:

    ```bash
    cmake --preset <preset_name> -DAOC_CHAL=<challenge_name> ..
    ```

    For example, to build challenge 01:
    **Challenges are defined as their file names `chal01`, `chal02`, ... , `chal10`**

    ```bash
    cmake -DAOC_CHAL=chal01 ..
    ```

4.  **Build the project:**

    ```bash
    cmake --preset <preset_name> -DAOC_CHAL=<challenge_name>
    ```

### Running Locally

1.  **Navigate to the build directory:**

    ```bash
    cd out/build/<preset_name>/src
    ```

2.  **Run the executable:**

    ```bash
    # Windows
    ./main.exe
    # Linux
    ./main
    ```

    The program will read the input data from the file specified by `AOC_DATA_FILE` (defined in `src/CMakeLists.txt`) and print the results to the console.

## 📂 Project Structure

```
├── CMakeLists.txt
├── challenges
│   ├── chal10.cpp
│   ├── ...
│   ├── chal02.cpp
│   ├── chal01.cpp
│   ├── template.cpp
│   └── chal_data (all but template are untracked)
│       ├── chal10.txt
│       ├── ...
│       ├── chal02.txt
│       ├── chal01.txt
│       └── template.txt
├── include
│   ├── chal10.h
│   ├── ...
│   ├── chal02.h
│   ├── chal01.h
│   ├── main.h
│   └── template.h
└── src
    └── main.cpp
```

## 💖 Thanks

Thanks for checking out this Advent of Code project! I hope it helps you solve the challenges and learn more about C++.
