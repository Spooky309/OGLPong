#include <glad/glad.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "IO.h"
#include "TextureManager.h"
#include "Game.h"
int main() {
	Game::Instance().Init();
	while (Game::Instance().Update());
	return 0;
}