cmake_minimum_required(VERSION 3.0.0)
project(conways-game-of-life VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(conways-game-of-life ./src/main.cpp)
target_link_libraries(conways-game-of-life sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
