cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++0x")

project(sample)
find_package(OpenCV REQUIRED)

add_executable(
    sample
    main.cpp
    ./modules/Obj_ctrl.cpp
    ./modules/Obj_img.cpp
    ./modules/vector_2Dmaster.cpp
    ./modules/point_2Dmaster.cpp
    ./modules/windownView.cpp
)

target_link_libraries(sample ${OpenCV_LIBS})

