#include "Input.h"
#include <string.h>

bool Input::keys[512];
bool Input::lKeys[512];
bool Input::nkeys[512];
bool Input::GetKeyDown(const unsigned int& key) {
	return keys[key] && !lKeys[key];
}

bool Input::GetKey(const unsigned int& key) {
	return keys[key];
}

bool Input::GetKeyUp(const unsigned int& key) {
	return !keys[key] && lKeys[key];
}

void Input::GLFWKeyCallback(GLFWwindow* wind, int key, int, int action, int) {
	if (action == GLFW_PRESS) {
		keys[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

void Input::Update() {
	memcpy(lKeys, keys, 512 * sizeof(bool));
	//memcpy(keys, nkeys, 512 * sizeof(bool));
}