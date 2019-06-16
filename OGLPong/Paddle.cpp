#include "Paddle.h"
#include "Game.h"
#include "Input.h"
Paddle::Paddle(const bool& p2) {
	player2 = p2;
	ourSprite = new Sprite(Game::Instance().GetTextureManager().GetTexture("paddle.png"));
	if (!p2) {
		ourSprite->SetPosition(glm::vec3(ourSprite->GetTexture()->GetWidth(), 768.0f / 2.0f, 0.0f));
	}
	else {
		ourSprite->SetPosition(glm::vec3(1024 - ourSprite->GetTexture()->GetWidth(), 768.0f/2.0f, 0.0f));
	}
}

void Paddle::Update(const double& dTime) {
	glm::vec3 nextPos = ourSprite->GetPosition();
	if (!player2) {
		if (Input::GetKey(GLFW_KEY_W)) {
			if (!(ourSprite->GetPosition().y > (768.0f) - (ourSprite->GetTexture()->GetHeight() / 2.0f))) {
				nextPos.y += moveSpeed * dTime;
			}
		}
		if (Input::GetKey(GLFW_KEY_S)) {
			if (!(ourSprite->GetPosition().y < ourSprite->GetTexture()->GetHeight() / 2.0f)) {
				nextPos.y -= moveSpeed * dTime;
			}
		}
	}
	else {
		if (Input::GetKey(GLFW_KEY_UP)) {
			if (!(ourSprite->GetPosition().y > (768.0f) - (ourSprite->GetTexture()->GetHeight() / 2.0f))) {
				nextPos.y += moveSpeed * dTime;
			}
		}
		if (Input::GetKey(GLFW_KEY_DOWN)) {
			if (!(ourSprite->GetPosition().y < ourSprite->GetTexture()->GetHeight() / 2.0f)) {
				nextPos.y -= moveSpeed * dTime;
			}
		}
	}
	ourSprite->SetPosition(nextPos);
}

Sprite* Paddle::GetSprite() {
	return ourSprite;
}