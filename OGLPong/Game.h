#ifndef _H_GANE_
#define _H_GAME_
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include <GLFW/glfw3.h>

class Game {
public:
	static Game& Instance() {
		static Game _inst;
		return _inst;
	}
	bool Init();
	bool Update();
	void Render();
	GLFWwindow* GetWindow() const;
	ShaderManager& GetShaderManager();
	TextureManager& GetTextureManager();
private:
	ShaderManager shadMan;
	TextureManager texMan;
	Sprite* rendSprite;
	GLFWwindow* window;
	ShaderProgram* spriteShader;
	Game() = default;
	~Game() = default;
	Game(const Game&) = delete;
	GLuint vao;
	GLuint vbo;
	GLfloat planeVerts[30] {
		 1.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom right
		-1.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top left
		-1.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top left
		 1.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom right
		 1.0f,  1.0f,  0.0f, 1.0f, 1.0f  // top right
	};
};
#endif