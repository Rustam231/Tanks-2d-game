#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(int health,int damage,float speed)
	:Charachter(health,damage,speed)
{}

Player::~Player()
{
	cout << "Player is distructed" << endl;
}

void Player::load() {

    try
    {
        //Loads text to the screen
        if (font.loadFromFile("Assets/Fonts/arial.ttf"))
        {
            text.setFont(font);
            text.setFillColor(Color::Black);
            text.setScale(0.5f, 0.5f);
        }
        else
            throw "Font is not found";

        // Loads image from file
        if (texture.loadFromFile("Assets/Player/textures/tank.png"))
        {
            cout << "Tank image is loaded" << endl;
            sprite.setTexture(texture);

            sprite.scale(0.4f, 0.4f);
            sprite.setPosition(100.f, 100.f);
        }
        else
            throw "Player texture is not found";
    }
    catch (const char *error)
    {
        cout << "Error: " << error << endl;
    }
}

void Player::update(float deltaTime, RenderWindow& window,  Entity& player, Entity& enemy) {

    Vector2f position = sprite.getPosition();
    sprite.setOrigin(82.f / 2, 94.f / 2);
    Vector2f movement(0.f,0.f);

    // Check for keyboard input and collision between the player and window
    if(player.getHealth() > 0)
        if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))) {
            
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x)
                movement.x = 0;
            
            else
            {
                sprite.setRotation(-90.f);
                movement.x = 0.7f;
            }
        }
        else if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))) {

            if (sprite.getPosition().y + sprite.getGlobalBounds().height + 80.f > window.getSize().y)
                movement.y = 0;
            else
            {
                sprite.setRotation(0.f);
                movement.y = 0.7f;
            }
        }
        else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))) {

            if (sprite.getPosition().x < 20.f)
                movement.x = 0;
            else
            {
                sprite.setRotation(90.f);
                movement.x = -0.7f;
            }
        }
        else if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))) {

            if (sprite.getPosition().y < 20.f)
                movement.y = 0.f;
            else
            {
                sprite.setRotation(180.f);
                movement.y = -0.7f;
            }
        }

    // Apply movement with collision handling
    FloatRect next_pos = sprite.getGlobalBounds();
    next_pos.left += movement.x;
    next_pos.top += movement.y;

    // Check for collision with enemy
    bool colliding_x = next_pos.intersects(enemy.getSprite().getGlobalBounds()); // Check for horizontal intersection
    bool colliding_y = next_pos.intersects(enemy.getSprite().getGlobalBounds()); // Check for vertical intersection

    if(enemy.getHealth() > 0 && player.getHealth() > 0)
        if (colliding_x || colliding_y) {

            // Check if colliding within enemy bounds along intended movement
            if ((movement.x > 0 && sprite.getPosition().x < enemy.getSprite().getGlobalBounds().left + enemy.getSprite().getGlobalBounds().width - 20.0f) ||
                (movement.x < 0 && sprite.getPosition().x > enemy.getSprite().getGlobalBounds().left + 20.0f)) {

                movement.x = 0.0f; 
            }

            if ((movement.y > 0 && sprite.getPosition().y < enemy.getSprite().getGlobalBounds().top + enemy.getSprite().getGlobalBounds().height - 20.0f) ||
                (movement.y < 0 && sprite.getPosition().y > enemy.getSprite().getGlobalBounds().top + 20.0f)) { 

                movement.y = 0.0f; 
            }
        }

    sprite.setPosition(position + movement * getSpeed() * deltaTime);

    text.setPosition(player.getSprite().getPosition() - Vector2f(22, 38));
    text.setString(to_string(player.getHealth()));

    fireRateTimer += deltaTime;

    // Fires the bullets after pressing the left mouse button
    if (Mouse::isButtonPressed(Mouse::Button::Left) && fireRateTimer >= maxFireRate)
    {
        if (player.getSprite().getRotation() == 0.f)
        {
            direction = Vector2f(0.f, 0.5f);
        }
        else if (player.getSprite().getRotation() == 90.f)
        {
            direction = Vector2f(-0.5f, 0.f);
        }
        else if (player.getSprite().getRotation() == 180.f)
        {
            direction = Vector2f(0.f, -0.5f);
        }
        else
        {
            direction = Vector2f(0.5f, 0);
        }

    	bullets.push_back(Bullet());
    	int i = bullets.size() - 1;
        bullets[i].initialize(player,position,direction);
    	fireRateTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].loadPlayerBullet();
        bullets[i].update(deltaTime);

    	//Detects any collision between bullet and enemy
    	if(enemy.getHealth() > 0)
    	{
    		if (bullets[i].getGlobalBounds().intersects((bullets[i].getGlobalBounds(), enemy.getSprite().getGlobalBounds())))
    		{
    			// Reduces health after each collision
    			enemy.setHealth(enemy.getHealth() - player.getDamage());
    			bullets.erase(bullets.begin() + i);
    			cout << "Enemy health: " << enemy.getHealth() << endl;
    		}
    	}
    }
}

void Player::draw(RenderWindow& window, const Entity&, const Entity& player)
{   
    //Displaying each bullet
    if(player.getHealth() > 0)
    {
        for (int i = 0; i < bullets.size(); i++)
            bullets[i].draw(window);

        window.draw(text);
        window.draw(sprite);
    }
}