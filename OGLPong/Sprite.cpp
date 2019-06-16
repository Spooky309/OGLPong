#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
Sprite::Sprite(Texture* initTexture) {
	ourTexture = initTexture;
	//qScale = glm::vec3((float)initTexture->GetWidth() / 1024.0f, 
	//				   (float)initTexture->GetHeight() / 768.0f, 
	//				   0.0f);
	qScale = glm::vec3((float)initTexture->GetWidth()/2.0f, (float)initTexture->GetHeight()/2.0f, 0.0f);
	mMat = glm::mat4(1.0f);
	mMat = glm::translate(mMat, glm::vec3(1024.0f / 2.0f, 768.0f / 2.0f, 0.0f));
	mMat = glm::scale(mMat, qScale);
	
}

void Sprite::SetPosition(const glm::vec3& newPos) {
	position = newPos;
	mMat = glm::mat4(1.0f);
	mMat = glm::translate(mMat, position);
	mMat = glm::scale(mMat, qScale);
}

void Sprite::SetRotation(const glm::vec3& euler) {
	rotation = euler;
}

Texture* Sprite::GetTexture() {
	return ourTexture;
}

glm::mat4& Sprite::GetMMat() {
	return mMat;
}

glm::vec3& Sprite::GetPosition() {
	return position;
}