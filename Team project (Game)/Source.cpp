#include<iostream>
#include <fstream>
#include "Enemy.h"
using namespace std;

// Redifining I/O stream function(endline manipulator)
ostream& newline(ostream& print)
{
	return print << "\n" << flush;
}

// Implementation of function template for writing and reading from the file
template<typename T>
void getInfo(T& enemy, T& player)
{
	// Writes current health and damage to the file about enemy
	ofstream outfile("charachter.txt");

	if (outfile.is_open(), ios::out)
	{
		outfile << T::getNumberOfCharachters() << " " << 100 - player.getHealth() << " " << enemy.getHealth() << " " << player.getHealth() << " " << 100 - enemy.getHealth();
		outfile.close();
	}

	// Gets info from the file and outputs to the terminal
	int currentEnemyHealth, currentEnemyDamage, numOfChars;
	int currentPlayerHealth, currentPlayerDamage;
	ifstream infile("charachter.txt");

	if (infile.is_open())
	{
		infile >> numOfChars >> currentEnemyDamage >> currentEnemyHealth >> currentPlayerHealth >> currentPlayerDamage;
		infile.close();
	}

	// Implementation of I/O stream
	cout << newline << "Number of charachters: " << numOfChars << newline;
	cout << "Enemy damage: " << scientific << currentEnemyDamage << newline;
	cout << "Enemy health: " << fixed << currentEnemyHealth << newline << newline;
	cout << "Player health: " << fixed << currentPlayerHealth << newline;
	cout << "Player damage: " << fixed << currentPlayerDamage << newline;
}

int main() {

	RenderWindow window(VideoMode(1920, 1080), "Tanks game", Style::Default);
	window.setFramerateLimit(240);

	//Stores actual time
	Clock clock;

	//Creating charachters
	Entity* enemy1 = new Enemy(100, 25, 0.7f);
	enemy1->setPosition(Vector2f(window.getSize().x - 30, window.getSize().y - 60));
	enemy1->load();

	/*Entity* enemy2 = new Enemy(100, 25, 0.7f);
	enemy2->getSprite().setPosition(1000, 1000);
	enemy2->load();*/

	Entity* player = new Player(100, 25, 0.7f);
	player->load();

	while (window.isOpen()) 
	{
		Event event;

		// Restarts timer every single frame
		Time deltaTimer = clock.restart();

		//Time it takes to load one frame
		float deltaTime = deltaTimer.asMilliseconds();
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// Updates enemy's and player's actions
		enemy1->update(deltaTime, window, *player, *enemy1);
		//enemy2->update(deltaTime, window, *player, *enemy2);
		player->update(deltaTime, window, *player,*enemy1);
		
		window.clear(Color::White);

		// Drawing enemy and player on the screen
		enemy1->draw(window, *player, *enemy1);
		//enemy2->update(deltaTime, window, *player, *enemy2);
		player->draw(window, *player, *player);

		window.display();
	}

	// Writes and reads info to the stream
	getInfo(*enemy1, *player);
	
	delete enemy1;
	delete player;
	//delete enemy2;
	return 0;
}
