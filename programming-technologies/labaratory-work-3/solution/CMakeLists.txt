# Minimum CMake version and project description
cmake_minimum_required(VERSION 3.16)
project(main_qt_app 
    VERSION 1.0.0 
    LANGUAGES CXX
    DESCRIPTION "C++/Qt application with PostgreSQL"
)

# C++ standard configuration (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Automatic MOC file generation for Qt

# MSYS2 UCRT64 prefix configuration (Windows only)
if(WIN32)
    set(MSYS2_PREFIX "C:/msys64/ucrt64")

    # Add MSYS2 Qt paths to CMAKE_PREFIX_PATH
    # This allows find_package to locate Qt6 in non-standard locations
    set(CMAKE_PREFIX_PATH "${MSYS2_PREFIX};${CMAKE_PREFIX_PATH}")

    # Manual configuration for libpqxx (PostgreSQL C++ library)
    set(PQXX_INCLUDE_DIR "${MSYS2_PREFIX}/include")
    set(PQXX_LIBRARY "${MSYS2_PREFIX}/lib/libpqxx.dll.a")
endif()

# Find and include required Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()  # Standard Qt project setup

# Source files and headers lists
# Headers are automatically processed via CMAKE_AUTOMOC
set(SOURCES
    src/main.cpp
    src/database/database.cpp
    src/services/product_service.cpp
    src/windows/main_window.cpp
    src/modals/create_product_modal.cpp
    src/modals/update_product_modal.cpp
)

set(HEADERS
    src/database/database.h
    src/services/product_service.h
    src/windows/main_window.h
    src/modals/create_product_modal.h
    src/modals/update_product_modal.h
)

# Create executable
qt_add_executable(main_qt_app ${SOURCES} ${HEADERS})

# Configure include directories for compiler
target_include_directories(main_qt_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
    ${CMAKE_CURRENT_SOURCE_DIR}/src/services
    ${CMAKE_CURRENT_SOURCE_DIR}/src/windows
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modals
    ${PQXX_INCLUDE_DIR}  # For libpqxx headers
)

# Link libraries
target_link_libraries(main_qt_app PRIVATE
    Qt6::Core      # Qt core classes
    Qt6::Widgets   # GUI widgets
    ${PQXX_LIBRARY} # PostgreSQL C++ library

    # Windows system libraries (required for network operations)
    $<$<PLATFORM_ID:Windows>:ws2_32>      # Windows Sockets
    $<$<PLATFORM_ID:Windows>:secur32>     # Security API
)

# Windows-specific settings (deployment and DLL copying)
if(WIN32)
    # Automatic Qt library deployment using windeployqt
    # windeployqt automatically detects and copies all required Qt DLLs
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt6
        PATHS "${MSYS2_PREFIX}/bin"
        NO_DEFAULT_PATH
    )

    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET main_qt_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env 
                PATH="${MSYS2_PREFIX}/bin;$ENV{PATH}"
                ${WINDEPLOYQT_EXECUTABLE}
                --verbose 1
                --no-compiler-runtime    # Don't copy compiler redistributables
                --no-system-d3d-compiler # Don't copy system D3D compiler
                --no-angle               # Don't copy ANGLE libraries
                --no-opengl-sw           # Don't copy software OpenGL implementation
                $<TARGET_FILE:main_qt_app>     # Path to compiled executable
            COMMENT "Automatic Qt library deployment using windeployqt"
        )
    else()
        message(WARNING "windeployqt not found, manual Qt library deployment required")
    endif()

    # Manual copying of required DLLs not handled by windeployqt
    # libpqxx and libpq - PostgreSQL dependencies
    add_custom_command(TARGET main_qt_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpqxx.dll"
            $<TARGET_FILE_DIR:main_qt_app>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_PREFIX}/bin/libpq.dll"
            $<TARGET_FILE_DIR:main_qt_app>
        COMMENT "Copying PostgreSQL DLL libraries (libpqxx, libpq)"
    )
endif()
