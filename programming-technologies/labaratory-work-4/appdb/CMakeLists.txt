cmake_minimum_required(VERSION 3.16)
project(productdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(-fvisibility=hidden)
add_link_options(-Wl,--no-undefined)

add_library(productdb SHARED
    src/product_repository.cpp
)

target_include_directories(productdb PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(pqxx REQUIRED)
target_link_libraries(productdb PRIVATE pqxx::pqxx)

set_target_properties(productdb PROPERTIES
    PREFIX ""
    OUTPUT_NAME "productdb"
)
