cmake_minimum_required(VERSION 3.1.0)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "24")

project(PrestoPalette VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

enable_testing()

include(InstallRequiredSystemLibraries)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An artist's tool for creating harmonious color palettes")
SET(CPACK_PACKAGE_VENDOR "John Cbonis and Darryl T. Agostinelli")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/application.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/application.rc" @ONLY IMMEDIATE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Network REQUIRED)

IF(MINGW)
	add_executable(${CMAKE_PROJECT_NAME} WIN32 main.cpp mainwindow.cpp resources.qrc ${CMAKE_CURRENT_BINARY_DIR}/application.rc visualpalette.cpp circlepalette.cpp clickablelabel.cpp aboutdialog.cpp)
ELSEIF(APPLE)
		add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE "${CMAKE_SOURCE_DIR}/graphics/favicon.icns" main.cpp mainwindow.cpp resources.qrc ${CMAKE_CURRENT_BINARY_DIR}/application.rc visualpalette.cpp circlepalette.cpp clickablelabel.cpp aboutdialog.cpp)
ELSE()
		add_executable(${CMAKE_PROJECT_NAME} main.cpp mainwindow.cpp resources.qrc ${CMAKE_CURRENT_BINARY_DIR}/application.rc visualpalette.cpp circlepalette.cpp clickablelabel.cpp aboutdialog.cpp)
ENDIF()

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Gui)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Multimedia)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
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
	file(COPY ${CMAKE_FIND_ROOT_PATH}/lib/qt5/plugins/audio/ DESTINATION ${CMAKE_BINARY_DIR}/bin/audio/)

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
ENDIF()

# CPack Variable Cheetsheet
# https://github.com/mgalloy/cpack-cheatsheets/blob/master/cpack-variables.rst

# NSIS (Windows)
SET(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
SET(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/graphics/favicon.ico)
SET(CPACK_NSIS_MUI_UNIICON ${CMAKE_CURRENT_SOURCE_DIR}/graphics/favicon.ico)
SET(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_PROJECT_NAME}.exe)
SET(CPACK_NSIS_MENU_LINKS ${CMAKE_PROJECT_NAME}.exe;${CPACK_PACKAGE_NAME})
SET(CPACK_NSIS_DISPLAY_NAME "${CMAKE_PROJECT_NAME}")
SET(CPACK_NSIS_HELP_LINK "http://www.prestopalette.com")
SET(CPACK_NSIS_COMPONENT_INSTALL OFF)

# Bundle (OSX)
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.plist.in" "${CMAKE_CURRENT_BINARY_DIR}/Info.plist")
SET(CPACK_BUNDLE_NAME "${CMAKE_PROJECT_NAME}")
#SET(CPACK_BUNDLE_STARTUP_COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/Launcher")
SET(CPACK_BUNDLE_STARTUP_COMMAND ${CPACK_PACKAGE_NAME})
SET(CPACK_BUNDLE_PLIST "${CMAKE_BINARY_DIR}/Info.plist")
SET(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/graphics/favicon.icns")
SET(MACOSX_BUNDLE_ICON_FILE favicon.icns)

IF(APPLE)
	SET(PACKAGE_PLATFORM_TAG "-osx")
	SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/graphics/favicon.icns")
	set_source_files_properties("${CMAKE_SOURCE_DIR}/graphics/favicon.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
ENDIF()

# Debian related stuff
# SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libgcc1, libqt (>= 5.5.0)")
# SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}${PACKAGE_PLATFORM_TAG}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

INCLUDE(CPack)
