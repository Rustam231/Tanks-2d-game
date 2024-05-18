#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
using namespace sf;

// Abstract class
class Entity {
public:
	Entity(int = 0, int = 0);
	~Entity();
	void setDamage(int);
	void setHealth(int);
	void setPosition(const Vector2f&);
	int getHealth() const;
	int getDamage() const;
	Texture getTexture() const;
	Sprite getSprite() const;
	static int getNumberOfCharachters();

	// Functions don't have an implementation
	virtual void draw(RenderWindow&, const Entity&, const Entity&) = 0;
	virtual void load() = 0;
	virtual void update(float,RenderWindow&, Entity&, Entity&) = 0;

protected:
	Sprite sprite;
	Texture texture;
	Text text;
	Font font;

private:
	int health;
	int damage;
	static int numberOfCharachters;
};
#endif