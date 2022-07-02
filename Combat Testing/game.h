#pragma once
//#include "audio.h"
#include "player.h"
#include "rooms.h"
#include "ui.h"

struct Game
{
	//Game setup
	GameData gamedata{};
	Player player1;
	std::vector<Dim2Df> spawnPoints;
	std::vector<Enemy> enemyList;
	std::vector<Projectile> projectiles;
	std::vector<Room> roomList;

	//SFML
	sf::Clock clock;

	//Other stuff currently unknown to those who seek to wield it

	//Initializes the game session
	void Init(sf::RenderWindow& window);

	//Main game loop
	void GameLoop(sf::RenderWindow& window);
};