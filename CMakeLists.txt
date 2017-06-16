cmake_minimum_required(VERSION 3.1.0)

project(prestopalette VERSION 1.0.0.1)

enable_testing()

include(InstallRequiredSystemLibraries)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(prestopalette WIN32 main.cpp mainwindow.cpp resources.qrc visualpalette.cpp circlepalette.cpp clickablelabel.cpp)

target_link_libraries(prestopalette Qt5::Widgets)
target_link_libraries(prestopalette Qt5::Core)
target_link_libraries(prestopalette Qt5::Gui)
target_link_libraries(prestopalette Qt5::Multimedia)

set_property(TARGET prestopalette PROPERTY CXX_STANDARD 11)
set_property(TARGET prestopalette PROPERTY CXX_STANDARD_REQUIRED ON)

INSTALL(TARGETS prestopalette
		BUNDLE DESTINATION .
		RUNTIME DESTINATION .
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		)

IF(MINGW)
	function(force_find_library file_name)
		SET(FOUND_LIB "FOUND_LIB-NOTFOUND")
		find_library(FOUND_LIB NAMES ${file_name} PATHS ${CMAKE_FIND_ROOT_PATH}/bin/ NO_DEFAULT_PATH)
		if(FOUND_LIB)
			file(COPY ${FOUND_LIB} DESTINATION ${CMAKE_BINARY_DIR}/bin/)
		else()
			message(FATAL_ERROR "${file_name} not found")
		endif()
	endfunction()
	
	force_find_library("libgcc_s_seh-1.dll")
	force_find_library("libstdc++-6.dll")
	force_find_library("libwinpthread-1.dll")
	force_find_library("libpcre16-0.dll")
	force_find_library("libpcre-1.dll")
	force_find_library("libGLESv2.dll")
	force_find_library("libharfbuzz-0.dll")
	force_find_library("libglib-2.0-0.dll")
	force_find_library("zlib1.dll")
	force_find_library("libintl-8.dll")
	force_find_library("iconv.dll")
	force_find_library("libpng16-16.dll")
	force_find_library("libEGL.dll")

	file(COPY ${CMAKE_FIND_ROOT_PATH}/lib/qt5/plugins/platforms/ DESTINATION ${CMAKE_BINARY_DIR}/bin/platforms/)

	install(DIRECTORY ${CMAKE_BINARY_DIR}/bin/ DESTINATION . FILES_MATCHING PATTERN "*.dll" )

	get_target_property(Qt5_Core_Location Qt5::Core LOCATION)
	get_target_property(Qt5_Gui_Location Qt5::Gui LOCATION)
	get_target_property(Qt5_Widgets_Location Qt5::Widgets LOCATION)
	get_target_property(Qt5_Multimedia_Location Qt5::Multimedia LOCATION)
	get_target_property(Qt5_Network_Location Qt5::Network LOCATION)

	INSTALL(FILES ${Qt5_Core_Location} DESTINATION . COMPONENT Libraries)
	INSTALL(FILES ${Qt5_Gui_Location} DESTINATION . COMPONENT Libraries)
	INSTALL(FILES ${Qt5_Widgets_Location} DESTINATION . COMPONENT Libraries)
	INSTALL(FILES ${Qt5_Multimedia_Location} DESTINATION . COMPONENT Libraries)
	INSTALL(FILES ${Qt5_Network_Location} DESTINATION . COMPONENT Libraries)
ENDIF(MINGW)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Presto Palette")
SET(CPACK_PACKAGE_VENDOR "John Cbonis and Darryl T. Agostinelli")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)
