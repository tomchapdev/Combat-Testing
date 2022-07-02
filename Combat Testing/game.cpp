#include "game.h"

//Initializes game session
void Game::Init(sf::RenderWindow& window)
{
	//Game data
	gamedata.Init(window);

	//Rooms
	Room startRoom;
	startRoom.Init(gamedata, 0, { 32, 32 });
	Room enemyRoom;
	enemyRoom.Init(gamedata, 1, { 32, 56 });
	Room itemRoom;
	itemRoom.Init(gamedata, 2, { 32, 8 });

	roomList.resize(3);
	roomList[0] = startRoom;
	roomList[1] = enemyRoom;
	roomList[2] = itemRoom;

	//Player
	player1.Init(gamedata);
	gamedata.playerHit = &player1.hit;

	//Enemy
	Enemy enemy1;
	enemy1.ID = 1;
	enemy1.Init(gamedata, { 700.f, 700.f });

	enemyList.resize(10);
	enemyList[0] = enemy1;

	//Projectiles
	projectiles.resize(GC::MAX_PROJECTILES);
	InitProjectiles(gamedata, projectiles);

	//Random
	srand((int)time(0)); //Sets random's seed to current time, for "true random"
}

//Main game loop
void Game::GameLoop(sf::RenderWindow& window)
{
	//Clock
	gamedata.elapsed = clock.getElapsedTime().asSeconds();
	if (gamedata.elapsed > GC::APPROX_ELAPSED)
	{
		gamedata.elapsed = GC::APPROX_ELAPSED; //Clamp elapsed time, for testing purposes
	}
	clock.restart();

	//Player input
	player1.Update(window, gamedata, projectiles, enemyList);

	//Enemy
	enemyList[0].Update(gamedata, projectiles, player1.entity);

	//Update the window
	gamedata.RenderMap(window, player1.entity.sprite.getPosition());

	//Render animated tiles
	roomList[0].UpdateAnimatedTiles(gamedata, window);
	roomList[1].UpdateAnimatedTiles(gamedata, window);
	roomList[2].UpdateAnimatedTiles(gamedata, window);

	//Render enemies
	if (enemyList[0].active)
	{
		enemyList[0].entity.Render(window, gamedata);
	}

	//Render Projectiles
	UpdateProjectiles(gamedata, window, projectiles);

	//Render player last
	player1.entity.Render(window, gamedata);
}