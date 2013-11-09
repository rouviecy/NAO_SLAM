cmake_minimum_required(VERSION 2.8)
project(nao_visio)

find_package(qibuild)

qi_create_bin(nao_visio "main.cpp")

qi_use_lib(nao_visio ALCOMMON)

enable_testing()
qi_create_test(test_nao_visio "test.cpp")
