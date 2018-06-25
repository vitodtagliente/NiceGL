#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "nicegl/nicegl.h"

using namespace nicegl;
using namespace std;

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

	// Vertex array
	VertexArray va;

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
	 	 0.5f,  0.5f,
		-0.5f,  0.5f 
	};

	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	vb.bind();

	/*
	VertexBufferLayout layout;
	layout.push<float>(2);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	va.addBuffer(vb, layout);
	*/

	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	IndexBuffer ib(indices, 6);
	ib.bind();

	//va.unbind();
	vb.unbind();
	ib.unbind();

	Renderer renderer;
	Color color{ 0.2f,0.0f,0.3f,1.0f };

	std::string vs_source, fs_source;
	ShaderReader::load("shaders/test.vs", vs_source);
	ShaderReader::load("shaders/test.fs", fs_source);
	VertexShader vs(vs_source);
	if (vs.getStatus() == ShaderStatus::Error) {
		cout << vs.getErrorMessage() << endl;
	}
	FragmentShader fs(fs_source);
	if (fs.getStatus() == ShaderStatus::Error) {
		cout << fs.getErrorMessage() << endl;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear(color);

		//va.bind();
		//ib.bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}