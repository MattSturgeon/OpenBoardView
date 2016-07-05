### lib/CMakeLists.txt ###
#
#

## imgui:
execute_process(
	COMMAND git submodule update --init imgui
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(imgui imgui/imgui.cpp imgui/imgui_draw.cpp)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
target_link_libraries(imgui ${PLATFORM_LIBS})


## utf8: no need to ass_lib since it is only a header file
execute_process(
	COMMAND git submodule update --init utf8
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
