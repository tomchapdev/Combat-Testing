#pragma once
#include "entity.h"

//Structs

struct Player
{
	//SFML
	sf::Mouse mouse{}; //Player mouse

	//Positioning
	Dim2Df movementInput = { 0.f, 0.f }; //Player movement inputs

	//Structs
	Entity entity{};
	//Weapon ability;

	//Functions

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
};