cmake_minimum_required(VERSION 2.8.11)

project(testproject)

INCLUDE(CPack)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)


# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 main.cpp mainwindow.cpp resources.qrc)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)

INSTALL(TARGETS helloworld
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		)
