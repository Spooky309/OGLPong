#ifndef _H_TEX_
#define _H_TEX_
#include <string>
#include <png.h>
#include <glad/glad.h>
class Texture {
public:
	friend class TextureManager;
	GLuint GetTextureID() const;
	int GetWidth() const;
	int GetHeight() const;
	GLint GetFormat() const;
private:
	Texture(const std::string& name);
	void LoadFromPNG(const std::string& fullp);
	void LoadFromPCX(const std::string& fullp);
	unsigned char PCXReadByte(FILE* file);
	unsigned char PCXGetRLECount(FILE* file, unsigned char* outValue);
	void LoadFromTGA(const std::string& fullp);
	std::string name;
	uint32_t width;
	uint32_t height;
	GLint format;
	GLuint texID;
	unsigned char* data;
};
#endif