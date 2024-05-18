#ifndef CHARAHCTER_H
#define CHARAHCTER_H
#include "Entity.h"

// Implementation of single inheritance
class Charachter : public Entity
{
public:
	Charachter(int, int, float);
	~Charachter();
	float getSpeed() const;
	void setSpeed(float = 0);

protected:
	Vector2f direction;
	float maxFireRate = 700;
	float fireRateTimer;

private:
	float speed;
}; 
#endif
