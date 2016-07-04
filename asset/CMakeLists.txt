### asset/CMakeLists.txt ###
#
#

if (MSVC)
	# Needed for MSVS resource compiler
	set(ICON "${CMAKE_CURRENT_SOURCE_DIR}/OpenBoardView.rc" PARENT_SCOPE)
elseif(APPLE)
	# Used for app bundle
	set(ICON "${CMAKE_CURRENT_SOURCE_DIR}/brd.icns" PARENT_SCOPE)
	set_source_files_properties("brd.icns" PROPERTIES
		MAXOSX_PACKAGE_LOCATION "Resources")
endif()

# WiX Installer images
set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\brd.ico" PARENT_SCOPE) # icon for Add/Remove with WiX installer
set(CPACK_WIX_UI_BANNER "${CMAKE_CURRENT_SOURCE_DIR}\\\\wix_installer_banner.bmp" PARENT_SCOPE) # 493x58px bmp top banner for WiX installer
set(CPACK_WIX_UI_DIALOG "${CMAKE_CURRENT_SOURCE_DIR}\\\\wix_installer_bg.bmp" PARENT_SCOPE) # 493x312 bmp background image for WiX Welcome/Completion page

# Installer text resources
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt") # License
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/Installer_Welcome.txt") # Welcome text
