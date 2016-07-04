### lib/CMakeLists.txt ###
#
#

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake")


## imgui:
execute_process(
	COMMAND git submodule update --init imgui
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Imgui doesnt have a CMakeLists file (yet...)
add_library(imgui imgui/imgui.cpp imgui/imgui_draw.cpp)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
target_link_libraries(imgui ${PLATFORM_LIBS})
set(LIBS ${LIBS} imgui)


## glfw ##

# Try to find system lib
option(USE_SYSTEM_GLFW
	"Try to build using the system installed GLFW. Will fallback to included version if GLFW can't be found."
ON)
if(USE_SYSTEM_GLFW)
	find_package(GLFW3)
endif()

# Fallback to included one
if((NOT USE_SYSTEM_GLFW) OR (NOT GLFW3_FOUND))
	message("\n  Using included GLFW submodule\n")

	execute_process(
		COMMAND git submodule update --init glfw
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	
	# Set sane defaults
	set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	# Hide GLFW 'spam' from CMake GUI
	mark_as_advanced(FORCE LIB_SUFFIX GLFW_DOCUMENT_INTERNALS GLFW_BUILD_DOCS GLFW_BUILD_TESTS GLFW_BUILD_EXAMPLES)
	
	# Actually add glfw to build
	add_subdirectory(glfw)

	# GLFW needs a special flag for shared lib linking
	if(BUILD_SHARED_LIBS)
	target_compile_definitions(glfw INTERFACE -DGLFW_DLL)
	endif()

	set(LIBS ${LIBS} glfw)
else()
	message("\n  Using system GLFW\n")

	set(PLATFORM_LIBS ${PLATFORM_LIBS} ${GLFW3_LIBRARY})
endif()

## OpenGL
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!") # TODO: instructions on how to fix using cmake-gui
endif()


## utf8: no need to ass_lib since it is only a header file
execute_process(
	COMMAND git submodule update --init utf8
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

## Make a nice list for target_link_libraries, etc
set(LIBS ${LIBS} PARENT_SCOPE)

set(PLATFORM_LIBS ${PLATFORM_LIBS}
	${OPENGL_LIBRARIES}
PARENT_SCOPE)
