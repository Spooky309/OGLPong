#include "ShaderManager.h"

ShaderProgram* ShaderManager::GetShaderProgram(const std::string& name) {
	// if a shader is already loaded, return the ptr
	// else, load it
	for (auto it : loadedProgs) {
		if (it->name == name) {
			return it;
		}
	}
	ShaderProgram* n = new ShaderProgram(name);
	loadedProgs.push_back(n);
	return n;
}