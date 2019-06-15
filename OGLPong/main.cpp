#include <glad/glad.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "IO.h"
#include "TextureManager.h"

int main() {
	TextureManager tManager;
	SEIO::Init();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // not yet, but later we will scale
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Pong", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Texture* ballTex = tManager.GetTexture("ball.png");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	return 0;
}