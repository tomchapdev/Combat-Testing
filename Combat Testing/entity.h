#pragma once
#include "weapon.h"
#include "graphics.h"

//Structs

//Knockback
struct Knockback
{
	//Bools
	bool immovable = false; //If entity is immune to knockback
	bool active = false; //In knockback animation

	//Main stats
	float force = 0.f; //Current force of the knockback
	float deceleration = 0.f; //Resistance to knockback
	DirectionalAngle facing{};

	//Structs
	Dim2Df movementVector{ 0.f, 0.f }; //Movement vector of knockback
};

//An interactive creature
struct Entity
{
	//SFML
	sf::Texture* texture;
	sf::Sprite sprite;

	//Bools
	bool isPlayer = false; //Player or Enemy
	bool isAlive = true; //Alive or dead
	bool canAttack = true; //Ability to attack
	bool invulnerable = false; //Can be damaged or not
	bool moving = false; //Moving or still
	bool facingRight = true; //Facing right or left
	bool nearPlayer = false; //In the rendered map area or not

	//Main stats
	short int health = 0; //Hit points
	float speed = 0.f; //Movement speed
	float attackSpeed = 1.f; //Attack speed multiplier
	float power = 1.f; //Damage multiplier

	//Positioning
	Dim2Df bodyCentre = { 0, 0 }; //Player sprite's body centre
	Dim2Df movementVector = { 0.f, 0.f }; //Current movement values
	Dim2Di frameMovementVector = { 0, 0 }; //Current movement this frame
	sf::IntRect collisionRect = { 0, 0, 0, 0 }; //Collision rect of the sprite

	//Structs
	Knockback knock; //Knockback
	DirectionalAngle facing; //Direction the entity is facing
	Weapon weapon; //Weapon the entity is holding
	Animation anim; //Animation of the entity

	//Functions

	//Initiates an attack
	void InitAttack(const GameData& game, const char& attack);

	//Initiates a knockback
	void InitKnockback();

	//Updates movement vector based on target coords
	void UpdateMovementVector(const Dim2Df& target);

	//Moves the entity
	void Move(const GameData& game);

	//Checks if movement is valid, using rectangle intersections
	void CheckMapCollision(const GameData& game);

	//Renders the entity
	void Render(sf::RenderWindow& window, const GameData& game);

	//Updates any ongoing attacks
	void UpdateAttacks(const GameData& game, std::vector<Projectile>& proj);

	//Update the weapon's state
	void UpdateWeapon(const GameData& game, std::vector<Projectile>& proj);

	//Entity takes damage
	void TakeDamage();

};

namespace GC
{
	//const float KNIGHT_
}