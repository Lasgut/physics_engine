#!/bin/bash
set -e  # stop on first error

# Default: do not remove existing build directory unless requested
CLEAN=0

# Simple argument parsing: -clean, --clean, -c enable cleaning
for arg in "$@"; do
	case "$arg" in
		-clean|--clean|-c)
			CLEAN=1
			shift
			;;
		-h|--help)
			echo "Usage: $0 [-clean|--clean|-c]"
			echo "  -clean    Remove existing build/ directory before building"
			exit 0
			;;
		*)
			;;
	esac
done

echo "Building..."
if [ "$CLEAN" -eq 1 ]; then
	echo "Cleaning build directory..."
	rm -rf build
fi
mkdir -p build
cd build
cmake ../
cmake --build .
cd ..

echo "Build complete!"