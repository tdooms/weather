cmake_minimum_required(VERSION 3.14)
project(weather_test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HDRS ${weather_test_SOURCE_DIR}/src/*.h  )
file(GLOB_RECURSE SRCS ${weather_test_SOURCE_DIR}/src/*.cpp)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_package(Qt5Charts  REQUIRED)


add_executable(weather_test ${HDRS} ${SRCS})

target_link_libraries(weather_test "-lcurl")

qt5_use_modules(weather_test Core Widgets Gui Charts)