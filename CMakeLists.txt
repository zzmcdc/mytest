cmake_minimum_required(VERSION 3.12)
project(circle)

set(CMAKE_CXX_STANDARD 11)
add_executable(circle main.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(circle ${OpenCV_LIBS})
