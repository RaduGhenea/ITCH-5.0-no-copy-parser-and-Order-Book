cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Orderbook VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(core_lib src/Parser.cpp src/LimitOrderBook.cpp
src/MatchingEngine.cpp src/PriceTimeStrategy.cpp)
target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(orderbook src/main.cpp)

target_link_libraries(orderbook PRIVATE core_lib)


