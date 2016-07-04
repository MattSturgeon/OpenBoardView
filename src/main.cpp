// ImGui - standalone example application for GLFW + OpenGL
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "BoardView.h"

#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <iostream>
#include <string>

/* Callback used for errors (by glfw) */
static void error_callback(int error, const char *description) {
	std::cerr << "Error " << error << ": " << description << std::endl;
}

/* Load the font to use for the UI */
static void load_font(ImGuiIO io) {
	// TODO: Option to use system fonts
}

/* Main */
int main(int argc, char **argv) {
	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Open Board View", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Setup ImGui binding
	ImGui_ImplGlfw_Init(window, true);

	// Setup ImguiIO options
	ImGuiIO &io = ImGui::GetIO();
	io.IniFilename = NULL; // Disable imgui.ini

	// Load Fonts
	load_font(io);

	ImVec4 clear_color = ImColor(20, 20, 30);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Begin imgui frame
		ImGui_ImplGlfw_NewFrame();

		app.Update();

		if (app.m_wantsQuit) {
			glfwTerminate();
			exit(0);
		}

		if (app.m_wantsTitleChange) {
			app.m_wantsTitleChange = false;

			std::string title = app.m_lastFileOpenName;
			title += " - Open Board View";

			glfwSetWindowTitle(window, title.c_str());
		}

		// Rendering - end of frame
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();

	return 0;
}
