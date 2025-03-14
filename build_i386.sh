#!/bin/bash
BUILD_DIR="./build"
LINKER_FILES="kernel.bin boot.o kernel.o io/keyboard.o source.o"
LINKER_OPTS="--no-warn-rwx-segment"

if [[ "$1" == "--fullcln" ]]; then
    echo "Cleaning the build directory completely..."
    rm -rf $BUILD_DIR
    mkdir $BUILD_DIR
fi

if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Copy source files..."
cp -r ../src/* ./
# 32-bit GCC
echo "GCC compiling with Makefile..."
if [[ "$1" == "--fullcln" ]]; then
    make clean
fi
make

echo "Linking job..."
ld -m elf_i386 -T ../src/linker.ld -o $LINKER_FILES $LINKER_OPTS

# Control the output
if [ ! -f "kernel.bin" ]; then
    echo "ERR: kernel.bin couldn't created!"
    exit 1
fi

echo "SUCC: Compiling is done."

echo "Starting QEMU..."
qemu-system-i386 -kernel kernel.bin

echo "Cleaning obselote files..."
rm -f *.o kernel.bin
cd ..

if [[ "$1" == "--fullcln" ]]; then
    echo "Cleaning the build directory at exit..."
    rm -rf $BUILD_DIR
fi

echo "SUCC: All succeed."