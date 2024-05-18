#include "Entity.h"
#include <iostream>
using namespace std;

int Entity::numberOfCharachters = 0;

Entity::Entity(int health,int damage)
	:health(health),damage(damage)
{
	numberOfCharachters += 1;
}
Entity::~Entity()
{
	cout << "Entity is distructed" << endl;
}
// Setting and getting attributes
int Entity::getDamage() const {
	return damage;
}
int Entity::getHealth() const {
	return health;
}
Texture Entity::getTexture() const {
	return texture;
}
Sprite Entity::getSprite() const {
	return sprite;
}
int Entity::getNumberOfCharachters() {
	return numberOfCharachters;
}
void Entity::setHealth(int health) {
	this->health = health;
}
void Entity::setDamage(int damage)
{
	this->damage = damage;
}
void Entity::setPosition(const Vector2f& pos) {
	sprite.setPosition(pos);
}