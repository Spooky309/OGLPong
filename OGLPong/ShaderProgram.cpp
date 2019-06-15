#include "ShaderProgram.h"
#include "IO.h"
#include <iostream>
#include <fstream>
ShaderProgram::ShaderProgram(const std::string& shadname) {
	std::ifstream vsi(SEIO::GetContentPath(shadname + ".vs"), std::ios::binary | std::ios::ate);
	std::ifstream fsi(SEIO::GetContentPath(shadname + ".fs"), std::ios::binary | std::ios::ate);
	std::size_t vlen = vsi.tellg();
	std::size_t flen = fsi.tellg();;
	vsi.seekg(std::ios::beg);
	fsi.seekg(std::ios::beg);
	// i'm not using strings for the source loading
	// because they'll have to be casted ptrs to const char** anyway...
	char* vsauce = (char*)malloc(vlen + 1);
	char* fsauce = (char*)malloc(flen + 1);
	vsi.read(vsauce, vlen);
	fsi.read(fsauce, flen);
	// add null terminators
	// the compiler warnings are lying, if these pts are null then something has gone very wrong...
	vsauce[vlen] = 0;
	fsauce[flen] = 0;
	// compile shaders and link program
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &vsauce, nullptr);
	glShaderSource(fs, 1, &fsauce, nullptr);
	glCompileShader(vs);
	glCompileShader(fs);
	shad = glCreateProgram();
	glAttachShader(shad, vs);
	glAttachShader(shad, fs);
	glLinkProgram(shad);

	// print any errors
	GLchar * log = (GLchar*)malloc(512);
	glGetShaderInfoLog(vs, 512, nullptr, log);
	std::cout << log << "\n";
	glGetShaderInfoLog(fs, 512, nullptr, log);
	std::cout << log << "\n";
	glGetProgramInfoLog(shad, 512, nullptr, log);
	std::cout << log << "\n";

	// store locations to PV and Model Matrix uniforms (todo: separate P and V, P should only set once)
	vpLoc = glGetUniformLocation(shad, "PV");
	mLoc = glGetUniformLocation(shad, "ModelMat");

	// clean up and set name
	glDeleteShader(vs);
	glDeleteShader(fs);
	free(vsauce);
	free(fsauce);
	free(log);
	vsi.close();
	fsi.close();
	name = shadname;
}

void ShaderProgram::Use() {
	if (shad)
		glUseProgram(shad);
}

GLuint ShaderProgram::GetUniformLoc(const std::string & name) const {
	if (shad)
		return glGetUniformLocation(shad, name.c_str());
	return 0;
}

void ShaderProgram::SetVPMat(const GLfloat * value) {
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, value);
}

void ShaderProgram::SetMMat(const GLfloat * value) {
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, value);
}