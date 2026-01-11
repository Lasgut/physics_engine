#!/bin/bash
set -e  # stop on first error

echo "Building..."
rm -rf build
mkdir build
cd build
cmake ../
cmake --build .
cd ..

echo "Build complete!"