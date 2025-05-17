#!/bin/bash

set -e  # Exit on error

echo "Configuring project with CMake..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

echo "Building project..."
cmake --build build --config Release

echo "Build completed!"
