#ifndef _H_SPRITE_
#define _H_SPRITE_
#include "TextureManager.h"
#include "ShaderManager.h"
#include <glm/glm.hpp>
class Sprite {
public:
	Sprite(Texture* initTexture);
	void SetPosition(const glm::vec3& newPos);
	void SetRotation(const glm::vec3& euler);
	glm::vec3& GetPosition();
	Texture* GetTexture();
	glm::mat4& GetMMat();
private:
	Texture* ourTexture;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 qScale;
	glm::mat4 mMat;
};

#endif