#ifndef _H_TEXMAN_
#define _H_TEXMAN_
#include <string>
#include <vector>
#include "Texture.h"
class TextureManager {
public:
	Texture* GetTexture(const std::string& name);
private:
	std::vector<Texture*> loadedTextures;
};
#endif