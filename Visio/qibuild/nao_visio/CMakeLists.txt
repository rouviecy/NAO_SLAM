cmake_minimum_required(VERSION 2.8)
project(nao_visio)

find_package(qibuild)

# Create a executable named nao_visio
# with the source file: main.cpp
qi_create_bin(nao_visio "main.cpp")

# Add a simple test:
enable_testing()
qi_create_test(test_nao_visio "test.cpp")
