#include "TextureManager.h"

Texture* TextureManager::GetTexture(const std::string& name) {
	// if a texture is already loaded, return the existing one
	// else, load it
	for (auto it : loadedTextures) {
		if (it->name == name) {
			return it;
		}
	}
	Texture* t = new Texture(name);
	loadedTextures.push_back(t);
	return t;
}