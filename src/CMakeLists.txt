### src/CMakeLists.txt ###
#
#

# SOURCES to be added to main target
set(SOURCES
	main.cpp

	BoardView.cpp
	BRDBoard.cpp
	BRDFile.cpp
	NetList.cpp
	PartList.cpp

	imgui_impl_glfw.cpp
)

# Add platform specific sources
if(WIN32)
	SET(SOURCES ${SOURCES}
		platform_win32.cpp
	)
elseif(APPLE)
	SET(SOURCES ${SOURCES}
		platform_osx.mm
	)
elseif(UNIX AND NOT APPLE)
	SET(SOURCES ${SOURCES}
		platform_unix.cpp
	)
endif()

## Add main target
add_executable(${PROJECT_NAME}
	WIN32 MACOSX_BUNDLE
	${SOURCES}
	${ICON})

target_link_libraries(${PROJECT_NAME} PRIVATE
	 ${LIBS}
	 ${PLATFORM_LIBS}
	)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${GTK3_INCLUDE_DIRS}
	"${PROJECT_SOURCE_DIR}/lib/utf8"
	# Other include directories should be handled by targets
	#${OPENGL_INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD 11       # Use C++11
)

if (MSVC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		-D_CRT_SECURE_NO_WARNINGS
		-D_UNICODE -DUNICODE)

	# Tell MSVC to use main instead of WinMain for Windows subsystem executables
	set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS "/subsystem:windows /ENTRY:mainCRTStartup")
elseif(APLE)
	# Help CPack build the bundle
	set_target_properties(${PROJECT_NAME} PROPERTIES
		RESOURCE glfw.icns
		MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
		MACOSX_BUNDLE_SHORT_VERSION_STRING "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}"
		MACOSX_BUNDLE_LONG_VERSION_STRING ${CPACK_PACKAGE_VERSION}
		MACOSX_BUNDLE_ICON_FILE "brd.icns"
		MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/MacOSXBundleInfo.plist.in")
endif()

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR})
