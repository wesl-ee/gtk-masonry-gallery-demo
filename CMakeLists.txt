project(gtk-mason-gallery-demo)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic -Wstrict-aliasing -Werror)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig)
find_package(Threads)
pkg_check_modules(GTKMM gtkmm-3.0)

# Demo program
add_executable(gtk-mason-gallery-demo)
target_include_directories(gtk-mason-gallery-demo PUBLIC include)
target_include_directories(gtk-mason-gallery-demo PRIVATE src)
target_sources(gtk-mason-gallery-demo PRIVATE
	src/main.cc
	src/MainWindow.cc
	src/ImageBrick.cc
	src/ImageBrickData.cc
	src/MasonRow.cc
	src/MasonLayout.cc
)

target_link_libraries(gtk-mason-gallery-demo PRIVATE ${GTKMM_LIBRARIES})
target_link_libraries(gtk-mason-gallery-demo PRIVATE Threads::Threads)
target_link_directories(gtk-mason-gallery-demo PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(gtk-mason-gallery-demo PRIVATE ${GTKMM_INCLUDE_DIRS})
