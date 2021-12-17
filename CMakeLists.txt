cmake_minimum_required(VERSION 3.10)

project(Handler)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(tmp)

target_include_directories(${PROJECT_NAME} PRIVATE tmp)
target_link_directories(${PROJECT_NAME} PUBLIC tmp)
target_link_libraries(${PROJECT_NAME} myHandler)
