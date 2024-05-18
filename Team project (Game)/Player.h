#ifndef PLAYER_H
#define PLAYER_H
#include "Bullet.h"
#include <iomanip>

// Implementation of hierarchy and multilevel inheritance
class Player : public Charachter {
private:
	Vector2f originalMovement;
	Vector2f overlap;
	std::vector<Bullet>bullets;

public:
	Player(int = 0, int = 0, float = 0);
	~Player();
	void draw(RenderWindow&, const Entity&, const Entity&) override;
	void load() override;
	void update(float, RenderWindow&, Entity&, Entity&) override;
};
#endif