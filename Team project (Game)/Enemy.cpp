#include "Enemy.h"
#include <cmath>
#include <iostream>
using namespace std;

Enemy::Enemy(int health, int damage, float speed)
	: Charachter(health,damage,speed)
{}

Enemy::~Enemy()
{
	cout << "Enemy is distructed" << endl;
}

void Enemy::draw(RenderWindow& window, const Entity& player, const Entity&enemy) {
	
	//Draws enemy and bullets on the screen
	
	for (int i = 0; i < bullets.size(); i++)
		bullets[i].draw(window);
	
	if(enemy.getHealth() > 0)
	{

		window.draw(sprite);
		window.draw(text);
	}
}

void Enemy::load()
{
	// Implementation of exception handling
	try
	{
		//Sets the text
		if (font.loadFromFile("Assets/Fonts/arial.ttf"))
		{
			cout << "Font is loaded" << endl;
			text.setFont(font);
			text.setScale(0.5f, 0.5f);
			text.setFillColor(Color::Black);
		}
		else
			throw "Fonts are not found";

		//Sets enemy sprite
		if (texture.loadFromFile("Assets/Enemy/textures/enemy.png"))
		{
			cout << "Enemy is loaded" << endl;
			sprite.setTexture(texture);
			sprite.setScale(0.4f, 0.4f);
		}
		else
			throw "Texture is not found";
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
	}
}

void Enemy::update(float deltaTime,RenderWindow& window, Entity& player, Entity& enemy) {

	if (enemy.getHealth() > 0)
	{
		sprite.setOrigin(82.f / 2, 94.f / 2);
		previousPosition = sprite.getPosition();

		//Calculates direction of movement
		directionVertical = player.getSprite().getPosition() - sprite.getPosition();

		float threshold = 1.f;

		//Adjusts the direction of movement to get rid of diagonal movement
		if (abs(directionVertical.y) > threshold)
		{
			directionVertical.x = 0.0f;
		}
		else
			directionVertical.y = 0.0f;

		directionVertical = Math<Vector2f>::normalizeVector(directionVertical);
	}
		//Detects collision between player and enemy
		if (enemy.getHealth() > 0)
		{
			if (!enemy.getSprite().getGlobalBounds().intersects((player.getSprite().getGlobalBounds())))
			{
				sprite.move(directionVertical * getSpeed() * 0.4f * deltaTime);
			}
		}
		currentPosition = sprite.getPosition();

		//Changes orientation of enemy based on direction
		if (currentPosition.x > previousPosition.x)
			sprite.setRotation(-90.f);
		else if (currentPosition.x < previousPosition.x)
			sprite.setRotation(90.f);
		else if (currentPosition.y < previousPosition.y)
			sprite.setRotation(180.f);
		else if (currentPosition.y > previousPosition.y)
			sprite.setRotation(0.f);
		
		text.setPosition(enemy.getSprite().getPosition() - Vector2f(20, 35));
		text.setString(to_string(getHealth()));

		fireRateTimer += deltaTime;

		// Firing in the direction of player
		if (fireRateTimer >= maxFireRate && player.getHealth() > 0 && enemy.getHealth() > 0)
			if (enemy.getSprite().getPosition().x - player.getSprite().getPosition().x <= -1000 || enemy.getSprite().getPosition().x - player.getSprite().getPosition().x <= 1000)
			{
				if (enemy.getSprite().getRotation() == 0.f)
				{
					direction = Vector2f(0.f, 0.5f);
				}
				else if (enemy.getSprite().getRotation() == 90.f)
				{
					direction = Vector2f(-0.5f, 0.f);
				}
				else if (enemy.getSprite().getRotation() == 180.f)
				{
					direction = Vector2f(0.f, -0.5f);
				}
				else
				{
					direction = Vector2f(0.5f, 0);
				}

				// Creates new bullets for enemy
				bullets.push_back(Bullet());
				int i = bullets.size() - 1;
				bullets[i].initialize(enemy, sprite.getPosition(), direction);
				fireRateTimer = 0;
			}

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].loadEnemyBullet();
			bullets[i].update(deltaTime);

			//Detects any collision between bullet and enemy
			if (player.getHealth() > 0)
			{
				if (bullets[i].getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
				{
					// Reduces health after each collision
					player.setHealth(player.getHealth() - enemy.getDamage());
					bullets.erase(bullets.begin() + i);
					cout << "Player health: " << player.getHealth() << endl;
				}
			}
		}
}