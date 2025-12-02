cmake_minimum_required(VERSION 3.16)
project(productdb 
    VERSION 1.0.0 
    LANGUAGES CXX
    DESCRIPTION "Product Database C++/PostgreSQL library (explicit loading only)"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MSYS2_PREFIX "C:/msys64/ucrt64")
set(CMAKE_PREFIX_PATH "${MSYS2_PREFIX};${CMAKE_PREFIX_PATH}")

set(PQXX_INCLUDE_DIR "${MSYS2_PREFIX}/include")
set(PQXX_LIBRARY "${MSYS2_PREFIX}/lib/libpqxx.dll.a")
set(POSTGRESQL_INCLUDE_DIR "${MSYS2_PREFIX}/include")
set(POSTGRESQL_LIBRARY "${MSYS2_PREFIX}/lib/libpq.dll.a")

add_library(productdb SHARED
    src/appdb.cpp
)

target_include_directories(productdb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PQXX_INCLUDE_DIR}
    ${POSTGRESQL_INCLUDE_DIR}
)

target_link_libraries(productdb PRIVATE
    ${PQXX_LIBRARY}
    ${POSTGRESQL_LIBRARY}
    ws2_32
    secur32
)

set_target_properties(productdb PROPERTIES
    OUTPUT_NAME "productdb"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_command(TARGET productdb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MSYS2_PREFIX}/bin/libpqxx.dll"
        $<TARGET_FILE_DIR:productdb>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MSYS2_PREFIX}/bin/libpq.dll"
        $<TARGET_FILE_DIR:productdb>
    COMMENT "Copying PostgreSQL DLL dependencies"
)
