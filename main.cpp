#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "nicegl/nicegl.h"

// image loading library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// include ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// test applications
#include "tests/tests.h"

using namespace nicegl;
using namespace std;

tests::Application* create_test_application() {
	return new tests::SquareApplication();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "NiceGL test application", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLAD library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Cannot load GLAD" << std::endl;
		return 0;
	}

	// resize callback
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	// swap interval or vsync
	glfwSwapInterval(1);

	// stb_image settings
	stbi_set_flip_vertically_on_load(1);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ImGUI context
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	// test application
	tests::Application* app{ nullptr };

	// create test application
	app = create_test_application();

	// init application 
	if (app) app->init();

	float application_time{ 0.0f };

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// ImGui new frame
		ImGui_ImplGlfwGL3_NewFrame();	

		// update and render the application
		if (app)
		{
			app->update(glfwGetTime());
			app->render();
			app->gui();
		}

		// Render ImGui
		ImGui::Render();

		// update time
		application_time += glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// uninit app
	if (app) app->uninit();
	delete app;

	// terminate ImGui
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
	return 0;
}