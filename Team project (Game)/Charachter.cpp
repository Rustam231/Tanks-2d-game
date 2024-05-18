#include "Charachter.h"
#include <iostream>
using namespace std;

Charachter::Charachter(int health,int damage,float speed)
	: Entity(health,damage), speed(speed)
{}
Charachter::~Charachter()
{
	cout << "Charachter is destroyed" << endl;
}
// Gets and sets speeds
float Charachter::getSpeed() const {
	return speed;
}
void Charachter::setSpeed(float speed)
{
	this->speed = speed;
}
