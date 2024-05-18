#include "Bullet.h"
#include <iostream>
using namespace std;

Bullet::Bullet(float speed)
	:speed(speed)
{}

Bullet::~Bullet()
{
}

void Bullet::initialize(const Entity& player, const Vector2f&position, const Vector2f&direction)
{   
	// Initializes parameter for each bullet
	this->direction = direction;
	newBullet.setScale(0.5f, 0.5f);
	newBullet.setPosition(position);
	newBullet.setRotation(player.getSprite().getRotation() + 180.f);
	this->direction = Math<Vector2f>::normalizeVector(this->direction);
}

// Updates position of fired bullet
void Bullet::update(float deltaTime)
{
	newBullet.move(speed * deltaTime*direction);
}

// Sets the sprite for the bullet fired by player
void Bullet::loadPlayerBullet()
{
	// Checks if file for player bullet exists
	try
	{
		if (texture.loadFromFile("Assets/Bullet/textures/bullet.png"))
		{
			newBullet.setTexture(texture);
		}
		else
			throw "Text for firing player is not found";
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
	}
}

// Sets the sprite for the bullet fired by enemy
void Bullet::loadEnemyBullet()
{
	// Checks if file for enemy bullet exists
	try
	{
		if (texture.loadFromFile("Assets/Bullet/textures/bullet2.png"))
		{
			newBullet.setTexture(texture);
		}
		else
			throw "Text for firing enemy is not found";
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
	}
}

// Displays bullet on the screen
void Bullet::draw(RenderWindow&window)
{
	window.draw(newBullet);
}

