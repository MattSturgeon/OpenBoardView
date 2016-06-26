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

	imgui_impl_dx9.cpp
	platform_win32.cpp)

## Add main target
add_executable(${PROJECT_NAME}
	WIN32
	${SOURCES}
	${ASSETS})

target_link_libraries(${PROJECT_NAME} PRIVATE
	imgui
	 ${PLATFORM_LIBS}
	)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/lib/utf8"
	# Other include directories should be handled by targets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD 11       # Use C++11
)

if (MSVC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		-D_CRT_SECURE_NO_WARNINGS
		-D_UNICODE -DUNICODE)
endif()

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR})
