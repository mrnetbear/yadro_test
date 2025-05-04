# 🖥️ Computer Club Management System

A C++ application that simulates and manages events in a computer club, tracking client activities, table occupancy, and calculating daily revenue.

## 📋 Table of Contents
- [Features](#-features)
- [Build Instructions](#-build-instructions)
- [Running Tests](#-running-tests)
- [Project Structure](#-project-structure)
- [License](#-license)

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
cd computer-club

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .