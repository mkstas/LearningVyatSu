cmake_minimum_required(VERSION 3.16)
project(prodlib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

add_library(prodlib SHARED src/prodlib.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

target_link_libraries(prodlib
    PRIVATE ${PQXX_LIBRARIES}
)

target_include_directories(prodlib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS prodlib
    EXPORT prodlib-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES include/prodlib.h DESTINATION include)

install(EXPORT prodlib-targets
    FILE prodlib-config.cmake
    NAMESPACE prodlib::
    DESTINATION lib/cmake/prodlib
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    prodlib-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/prodlib-config-version.cmake
    DESTINATION lib/cmake/prodlib
)
