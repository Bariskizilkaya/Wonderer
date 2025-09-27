cmake_minimum_required(VERSION 3.10.0)
project(Wonderer LANGUAGES C CXX)

# Point to your DynamoRIO package
set(DynamoRIO_DIR
    /home/asd/Documents/fuzzing/Wonderer/libs/DynamoRIO-Linux-11.3.0/DynamoRIO-Linux-11.3.0-1/cmake
    )

find_package(DynamoRIO REQUIRED)

# Build as a shared library, not executable
add_library(Wonderer SHARED main.c)

# Configure it as a DynamoRIO client
configure_DynamoRIO_client(Wonderer)

# Optionally use extensions (drmgr is common)
use_DynamoRIO_extension(Wonderer drmgr)
