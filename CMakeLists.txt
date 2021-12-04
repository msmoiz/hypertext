cmake_minimum_required(VERSION 3.19)
project(hypertext)

add_library(hypertext
    "hypertext/hypertext.cpp" 
    "hypertext/method.cpp"
	"hypertext/version.cpp")

target_include_directories(hypertext PRIVATE "hypertext")

add_executable(tests
	"hypertext/main.test.cpp"
	"hypertext/method.test.cpp"
	"hypertext/version.test.cpp")
target_include_directories(tests PRIVATE "hypertext")
find_package(Catch2 REQUIRED)
target_link_libraries(tests hypertext Catch2::Catch2)
