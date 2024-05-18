#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"

// Implementation of hierarchy and multilevel inheritance
class Enemy : public Charachter
{
private:
	Vector2f directionVertical;
	Vector2f previousPosition;
	Vector2f currentPosition;
	std::vector<Bullet>bullets;

public:
	Enemy(int=0,int=0,float=0);
	~Enemy();
	void draw(RenderWindow&, const Entity& ,const Entity&) override;
	void load() override;
	void update(float, RenderWindow&, Entity&, Entity&) override;
};
#endif
