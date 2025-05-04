# 🖥️ Computer Club Management System

A C++ application that simulates and manages events in a computer club, tracking client activities, table occupancy, and calculating daily revenue.

## 📋 Table of Contents
- [Features](#-features)
- [Build Instructions](#-build-instructions)
- [Running Tests](#-running-tests)
- [Project Structure](#-project-structure)

## ✨ Features
- Event processing (client arrival, seating, waiting, departure)
- Table occupancy tracking
- Revenue calculation
- Queue management
- Error handling
- Time management with 24-hour format

## 🛠 Build Instructions

### Prerequisites
- C++20 compatible compiler (g++ 10+ or clang 10+)
- CMake 3.10+
- Make or Ninja

### Build Steps
```bash
# Clone the repository
git clone https://github.com/mrnetbear/yadro_test
cd yadro_test

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .
```
## 🧪 Running tests

### Basic Usage
```bash
./computer_club <input_file.txt>
```

### Provided Test Cases
```bash
# Test 1: Simple scenario with one table
./computer_club ../test1.txt

# Test 2: Error handling demonstration
./computer_club ../test2.txt

# Test 3: Complex multi-table scenario
./computer_club ../test3.txt
```

## 📑 Test Cases Description

### test1.txt

- Scenario: Single client using one table
- Checks: Basic revenue calculation and time tracking
- Expected: Correct single-table statistics

### test2.txt

- Scenario: Multiple error cases
- Checks: "NotOpenYet", "ClientUnknown", "PlaceIsBusy" handlers
- Expected: Proper error messages for each case

### test3.txt

- Scenario: Multiple clients and tables
- Checks: Queue management and table switching
- Expected: Correct revenue distribution across tables

## 📂 Project Structure

```
yadro_test/
├── CMakeLists.txt       - CMake build configuration
├── src/                     - source code
    ├── computer_club.hpp    - Time and ComputerClub classes
    ├── computer_club.cpp    - Class implementations
    └── software.cpp         - Main application logic
├── test1.txt            - Basic functionality test
├── test2.txt            - Error handling test
└── test3.txt            - Advanced scenario test
```