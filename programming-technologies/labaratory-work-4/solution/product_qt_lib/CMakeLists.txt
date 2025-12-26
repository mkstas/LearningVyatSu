cmake_minimum_required(VERSION 3.16)
project(product_qt_lib 
    VERSION 1.0.0 
    LANGUAGES CXX
    DESCRIPTION "Qt Product Management Library"
)

enable_language(ASM_NASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

set(MSYS2_PREFIX "C:/msys64/ucrt64")
set(CMAKE_PREFIX_PATH "${MSYS2_PREFIX};${CMAKE_PREFIX_PATH}")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_definitions(-DPRODUCT_QT_LIB_EXPORTS)

set(VALIDATE_ASM_SRC src/asm/validate_int_input.asm)

file(WRITE ${CMAKE_BINARY_DIR}/validate_int_lib.def "EXPORTS\nvalidateIntInputAsm\n")

add_library(validate_int_lib SHARED ${VALIDATE_ASM_SRC} ${CMAKE_BINARY_DIR}/validate_int_lib.def)
set_source_files_properties(${VALIDATE_ASM_SRC} PROPERTIES LANGUAGE ASM_NASM)

set_target_properties(validate_int_lib PROPERTIES
    PREFIX ""
    OUTPUT_NAME "validate_int_lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(SOURCES
    src/main.cpp
    src/product_repository_wrapper.cpp
    src/windows/main_window.cpp
    src/modals/create_product_modal.cpp
    src/modals/update_product_modal.cpp
)

set(HEADERS
    include/product_qt_lib.h
    src/product_repository_wrapper.h
    src/windows/main_window.h
    src/modals/create_product_modal.h
    src/modals/update_product_modal.h
)

add_library(product_qt_lib SHARED ${SOURCES} ${HEADERS})

target_include_directories(product_qt_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/windows
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modals
)

target_link_libraries(product_qt_lib PRIVATE
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(product_qt_lib PROPERTIES
    OUTPUT_NAME "product_qt_lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(MINGW)
    set_target_properties(product_qt_lib PROPERTIES
        ENABLE_EXPORTS ON
        WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
endif()

if(WIN32)
    set_target_properties(product_qt_lib PROPERTIES
        DEFINE_SYMBOL "PRODUCT_QT_LIB_EXPORTS"
    )
endif()

if(WIN32)
    add_custom_command(TARGET product_qt_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpqxx.dll"
            $<TARGET_FILE_DIR:product_qt_lib>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpq.dll"
            $<TARGET_FILE_DIR:product_qt_lib>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/../product_db_lib/build/bin/libproduct_db_lib.dll"
            $<TARGET_FILE_DIR:product_qt_lib>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:validate_int_lib>"
            $<TARGET_FILE_DIR:product_qt_lib>
        COMMENT "Copying required DLLs including validate_int_lib.dll"
    )
endif()

install(TARGETS product_qt_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

install(FILES include/product_qt_lib.h
    DESTINATION include
)
