#ifndef _H_PADDLE_
#define _H_PADDLE_
#include "Sprite.h"
class Paddle {
public:
	Paddle(const bool& p2);
	void Update(const double& dTime);
	Sprite* GetSprite();
private:
	Sprite* ourSprite;
	const float moveSpeed = 400.0f;
	bool player2;
};

#endif