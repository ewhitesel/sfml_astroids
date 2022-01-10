cmake_minimum_required(VERSION 3.10)

project(sfml_astroids)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(sfml_astroids main.cpp 
./Entities/Object.cpp
./Collision/Collider.cpp
./Entities/Bullet/Bullet.cpp
./Entities/Player/Player.cpp
./Entities/Astroid/Astroid.cpp)

target_link_libraries(sfml_astroids sfml-graphics sfml-audio)