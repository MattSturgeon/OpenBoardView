#
# Try to find GLFW library and include path.
# Once done this will define
#
# GLFW3_FOUND
# GLFW3_INCLUDE_DIR
# GLFW3_LIBRARY
# 

if(WIN32)
		find_path( GLFW3_INCLUDE_DIR GLFW/glfw3.h
		$ENV{PROGRAMFILES}/GLFW/include
		${GLFW_ROOT_DIR}/include
		DOC "The directory where GLFW/glfw3.h resides")

	if(BUILD_SHARED_LIBS)
		set(LIB_NAMES glfw3dll.lib GLFWdll.lib glfw3dll.a GLFWdll.a)
	else()
		set(LIB_NAMES glfw3 GLFW)
	endif()

	find_library( GLFW3_LIBRARY
		NAMES ${LIB_NAMES}
		PATHS
		$ENV{PROGRAMFILES}/GLFW/lib
		${GLFW_ROOT_DIR}/lib
		DOC "The GLFW library")
else(WIN32)
	find_path( GLFW3_INCLUDE_DIR GLFW/glfw3.h
		/usr/include
		/usr/local/include
		/sw/include
				/opt/local/include
		${GLFW_ROOT_DIR}/include
		DOC "The directory where GLFW/glfw3.h resides")

	if(BUILD_SHARED_LIBS)
		set(LIB_NAMES libglfw.so libglfw.so.3 libglfw.so.3.0 libglfw.so.3.1 libglfw.so.3.2)
	else()
		set(LIB_NAMES libGLFW.a GLFW libGLFW3.a GLFW3)
	endif()

	find_library( GLFW3_LIBRARY
			NAMES ${LIB_NAMES}
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLFW_ROOT_DIR}/lib
		DOC "The GLFW library")
endif(WIN32)

set(GLFW3_FOUND "NO")
if(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
	set(GLFW_LIBRARIES ${GLFW3_LIBRARY})
	set(GLFW3_FOUND "YES")
		message(STATUS "Found GLFW")
endif(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
