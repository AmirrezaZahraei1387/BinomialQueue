cmake_minimum_required(VERSION 3.23)
project(BioQu)

set(CMAKE_CXX_STANDARD 17)

add_executable(BioQu main.cpp bioQ/BioQ.hpp bioQ/BioQ.inl)
