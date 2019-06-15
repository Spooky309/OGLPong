#ifndef _H_SHADPROG_
#define _H_SHADPROG_
#include <string>
#include <glad/glad.h>
class ShaderProgram {
public:
	void Use();
	GLuint GetUniformLoc(const std::string& name) const;
	void SetVPMat(const GLfloat* value);
	void SetMMat(const GLfloat* value);
	friend class ShaderManager;
private:
	// I only want the shader manager to be able to construct these
	ShaderProgram(const std::string& shadname);
	GLuint shad;
	GLuint vpLoc;
	GLuint mLoc;
	std::string name;
};

#endif