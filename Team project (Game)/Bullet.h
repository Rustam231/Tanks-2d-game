#ifndef BULLET_H
#define BULLET_H
#include "Math.h"

class Bullet
{
private:
	Sprite newBullet;
	Vector2f direction;
	float speed = 0.5f;
	Texture texture;

public:
	Bullet(float = 0.7f);
	~Bullet();
	void draw(RenderWindow&);
	void loadPlayerBullet();
	void loadEnemyBullet();
	void initialize(const Entity&, const Vector2f&, const Vector2f&);
	void update(float);

	inline const FloatRect& getGlobalBounds()
	{
		return newBullet.getGlobalBounds();
	}
};
#endif
