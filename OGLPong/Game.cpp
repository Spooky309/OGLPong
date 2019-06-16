#include "Game.h"
#include "IO.h"
#include "Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool Game::Init() {
	SEIO::Init();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // not yet, but later we will scale
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	window = glfwCreateWindow(1024, 768, "Pong", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	glfwSetKeyCallback(window, &Input::GLFWKeyCallback);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	spriteShader = shadMan.GetShaderProgram("sprite");
	spriteShader->Use();

	glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projMat = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.1f, 100.0f);
	glm::mat4 vpMat = projMat * viewMat;
	spriteShader->SetVPMat(glm::value_ptr(vpMat));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(GLfloat), planeVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glfwSwapInterval(1);

	player1 = new Paddle(false);
	player2 = new Paddle(true);


	dTime = 0.0f;
	return true;
}

bool Game::Update() {
	lastTime = glfwGetTime();
	glfwPollEvents();

	player1->Update(dTime);
	player2->Update(dTime);

	Render();
	dTime = glfwGetTime() - lastTime;
	Input::Update();

	if (Input::GetKeyDown(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	return !glfwWindowShouldClose(window);
}

void Game::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	spriteShader->SetMMat(glm::value_ptr(player1->GetSprite()->GetMMat()));
	glBindTexture(GL_TEXTURE_2D, player1->GetSprite()->GetTexture()->GetTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	spriteShader->SetMMat(glm::value_ptr(player2->GetSprite()->GetMMat()));
	glBindTexture(GL_TEXTURE_2D, player2->GetSprite()->GetTexture()->GetTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwSwapBuffers(window);
}

GLFWwindow* Game::GetWindow() const {
	return window;
}

ShaderManager& Game::GetShaderManager() {
	return shadMan;
}

TextureManager& Game::GetTextureManager() {
	return texMan;
}