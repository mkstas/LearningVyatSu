cmake_minimum_required(VERSION 3.16)
project(prod VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(prodlib REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

qt_standard_project_setup()

qt_add_executable(prod
    src/main.cpp
    src/windows/main_window.cpp
    src/modals/create_product_modal.cpp
    src/modals/update_product_modal.cpp
)

target_link_libraries(prod 
  PRIVATE prodlib::prodlib
  PRIVATE Qt6::Core Qt6::Widgets
  PRIVATE ${PQXX_LIBRARIES}
)
