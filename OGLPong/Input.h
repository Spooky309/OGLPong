#ifndef _H_INPUT_
#define _H_INPUT_
#include <GLFW/glfw3.h>
class Input {
public:
	friend class Game;
	static bool GetKeyDown(const unsigned int& key);
	static bool GetKey(const unsigned int& key);
	static bool GetKeyUp(const unsigned int& key);
private:
	static void GLFWKeyCallback(GLFWwindow* wind, int key, int, int action, int);
	static void Update();
	static bool keys[512];
	static bool lKeys[512];
	static bool nkeys[512];
	Input() = delete;
	~Input() = delete;
	Input(const Input&) = delete;
};

#endif