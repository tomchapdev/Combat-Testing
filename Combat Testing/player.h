#pragma once
#include "enemy.h"

struct Player
{
	//SFML
	sf::Mouse mouse{}; //Player mouse

	//Positioning
	Dim2Df movementInput = { 0.f, 0.f }; //Player movement inputs

	//Main stats
	float speed = 0.f; //Player speed
	float knockbackPower = 100.f; //How fast the knocked enemy is
	float heavyAttackMultiplier = 2.f; //Damage multiplier of heavy attacks

	//Structs
	Entity entity{};

	//Initializes player
	void Init(GameData& game);

	//Get inputs and react
	void InputHandling(sf::RenderWindow& window, GameData& game);

	//Controls for keyboard
	void KeyboardControls(const sf::Event& event, GameData& game);

	//Find movement vector based on booleans
	void KeyboardMovement(const sf::Event& event);

	//Find the entity's facing angle based on mouse position
	void GetMouseAngle(GameData& game);

	//Controls for gamepad
	void GamepadControls(const sf::Event& event);

	//Checks attack collision against enemies
	void CheckAttackCollision(std::vector<Enemy>& enemies);

	//Updates player state
	void Update(sf::RenderWindow& window, GameData& gamedata, std::vector<Projectile> projectiles, std::vector<Enemy>& enemies);
};