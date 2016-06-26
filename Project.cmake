### Project.cmake ###
#
# Project metadata and packaging information
#
# Run by CMakeLists.txt
#

project("OpenBoardView" CXX)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(PRETTY_NAME "Open Board View" CACHE STRING
    "Pretty name for the project.")
mark_as_advanced(FORCE PRETTY_NAME)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Software for viewing .brd files, intended as a drop-in replacement for the
\"Test_Link\" software.")

# Version
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# Owner
set(CPACK_PACKAGE_VENDOR "Chloridite")

# Name out install directory; goes under CMAKE_INSTALL_PREFIX
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME} - ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

# Used for Windows and OSX shortcuts; ${PROJECT_NAME} is a console command,
# "Open Board View" is the pretty text
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PRETTY_NAME})

if(WIN32)
	# WiX MD5 Hash, used for checking whether to upgrade an installed package,
	# or install a new one
	#		hash generated manually using `echo "openboardview" | md5sum` on unix
	set(CPACK_WIX_UPGRADE_GUID "e10554b8-a9ce-9f67-8a09-68fbc9474a7a"
			CACHE STRING "Dash separated MD5 hash, used by WiX to perform updates.")
	mark_as_advanced(FORCE CPACK_WIX_UPGRADE_GUID)
endif()

## Text files (like LICENCE.txt) are added from asset/CMakeLists.txt

# List of package generators to use
if (WIN32)
	set(CPACK_GENERATOR "WIX"
		CACHE STRING "CPack Generator to use to build installer"
	)
	mark_as_advanced(FORCE CPACK_GENERATOR)
endif()

