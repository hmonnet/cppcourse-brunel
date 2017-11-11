cmake_minimum_required (VERSION 2.6)
project(Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")


enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
	../src/neuron.cpp
        ../src/network.cpp
	../src/main.cpp
     	)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(neuron ${SOURCE_FILES})
add_executable(unittest ../src/neuron.cpp ../src/test.cpp)

target_link_libraries(unittest gtest gtest_main)
add_test(unittest unittest)
