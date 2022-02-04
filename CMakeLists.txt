cmake_minimum_required(VERSION 3.8)

project(var_list_list
  DESCRIPTION "Simple showcase of a generic list of var_list"
  LANGUAGES CXX)

add_executable(var_list_list var_list_list_test.cpp)
target_compile_features(var_list_list PUBLIC cxx_std_17)
