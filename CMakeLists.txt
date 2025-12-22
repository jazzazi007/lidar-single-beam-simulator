cmake_minimum_required(VERSION 3.10)
project(LidarSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)


add_executable(lidar_sim src/lidar_single_beam.cpp
                       src/main.cpp)


target_include_directories(lidar_sim PRIVATE include)


target_link_libraries(lidar_sim PRIVATE SDL2::SDL2)

target_include_directories(lidar_sim PRIVATE ${SDL2_INCLUDE_DIRS})