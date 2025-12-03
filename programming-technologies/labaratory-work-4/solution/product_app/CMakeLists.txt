cmake_minimum_required(VERSION 3.16)
project(product_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(MSYS2_PREFIX "C:/msys64/ucrt64")

set(CMAKE_PREFIX_PATH "${MSYS2_PREFIX};${CMAKE_PREFIX_PATH}")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_executable(product_app src/main.cpp)

target_include_directories(product_app PRIVATE
    ${CMAKE_SOURCE_DIR}/../product_qt_lib/include
)

target_link_libraries(product_app PRIVATE
    Qt6::Core
    Qt6::Widgets
    ${CMAKE_SOURCE_DIR}/../product_qt_lib/build/lib/libproduct_qt_lib.dll.a
)

if(WIN32)
    add_custom_command(TARGET product_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/../product_qt_lib/build/bin/libproduct_qt_lib.dll"
            $<TARGET_FILE_DIR:product_app>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/../product_db_lib/build/bin/libproduct_db_lib.dll"
            $<TARGET_FILE_DIR:product_app>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpqxx.dll"
            $<TARGET_FILE_DIR:product_app>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpq.dll"
            $<TARGET_FILE_DIR:product_app>
    )
endif()
