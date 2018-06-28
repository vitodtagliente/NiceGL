#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "nicegl/nicegl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// include ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

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

	// stb_image settings
	stbi_set_flip_vertically_on_load(1);

	// -----------------------------------
	std::map<ShaderType, std::string> sources;
	ShaderReader::parse("shaders/texture.shader", sources);

	VertexShader vs(sources[ShaderType::VertexShader]);
	if (vs.getStatus() == ShaderStatus::Error) {
		cout << vs.getErrorMessage() << endl;
	}
	else
	{
		cout << "Vertex Shader" << endl << endl;
		cout << sources[ShaderType::VertexShader] << endl << endl;
	}

	FragmentShader fs(sources[ShaderType::FragmentShader]);
	if (fs.getStatus() == ShaderStatus::Error) {
		cout << fs.getErrorMessage() << endl;
	}
	else
	{
		cout << "Fragment Shader" << endl << endl;
		cout << sources[ShaderType::FragmentShader] << endl << endl;
	}

	Program program({ &vs, &fs });
	if (program.getStatus() == ShaderStatus::Error) {
		cout << program.getErrorMessage() << endl;
	}

	program.unbind();
	// ----------------------------------
	// position_x position_y uv_x uv_y
	float positions[] = { 
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
	 	 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
	};

	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	vb.bind();

	// Vertex Array
	VertexArray va;
	
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.addBuffer(vb, layout);

	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	IndexBuffer ib(indices, 6);
	ib.bind();

	va.unbind();
	vb.unbind();
	ib.unbind();

	// load texture
	unsigned char * image_data;
	int width, height, num_components;
	image_data = stbi_load("textures/batman_logo.png", &width, &height, &num_components, 4);
	Texture texture(image_data, width, height, num_components);
	stbi_image_free(image_data);

	Renderer renderer;
	Color background_color(0.2f, 0.25f, 0.3f, 1.0f);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ImGUI context
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear(background_color);

		// ImGui new frame
		ImGui_ImplGlfwGL3_NewFrame();

		glClear(GL_COLOR_BUFFER_BIT);

		program.bind();
		program.set("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

		texture.bind();
		program.set("u_Texture", 0);

		va.bind();
		ib.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		// render ImGui window
		ImGui::Text("Change background color:");
		ImGui::SliderFloat("r", &background_color.r, 0.0f, 1.0f);
		ImGui::SliderFloat("g", &background_color.g, 0.0f, 1.0f);
		ImGui::SliderFloat("b", &background_color.b, 0.0f, 1.0f);

		// Render ImGui
		ImGui::Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// terminate ImGui
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
	return 0;
}