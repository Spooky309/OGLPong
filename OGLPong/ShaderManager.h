#ifndef _H_SHADMAN_
#define _H_SHADMAN_
#include "ShaderProgram.h"
#include <string>
#include <vector>
class ShaderManager {
public:
	ShaderProgram* GetShaderProgram(const std::string& name);
private:
	std::vector<ShaderProgram*> loadedProgs;
};

#endif