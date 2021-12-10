cmake_minimum_required(VERSION 3.19)
project(hypertext)

add_library(hypertext
    "hypertext/method.cpp"
	"hypertext/version.cpp"
	"hypertext/connection.cpp"
	"hypertext/client.cpp"
	"hypertext/serialization.cpp")

set_target_properties(hypertext PROPERTIES CXX_STANDARD 17)
target_include_directories(hypertext PRIVATE "hypertext")
target_link_libraries(hypertext wsock32 ws2_32)

add_executable(tests
	"hypertext/main.test.cpp"
	"hypertext/method.test.cpp"
	"hypertext/version.test.cpp"
	"hypertext/serialization.test.cpp")
target_include_directories(tests PRIVATE "hypertext")
find_package(Catch2 REQUIRED)
target_link_libraries(tests hypertext Catch2::Catch2)

add_executable(demo
	"demo/main.cpp")
target_include_directories(demo PRIVATE "hypertext")
target_link_libraries(demo hypertext)
