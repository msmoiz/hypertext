cmake_minimum_required(VERSION 3.19)
project(hypertext)

add_library(hypertext
    "hypertext/hypertext.cpp" 
    "hypertext/methods.cpp")

target_include_directories(hypertext PRIVATE "hypertext")
