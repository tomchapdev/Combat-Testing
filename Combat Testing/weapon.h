#pragma once
#include "motion.h"

//Projectile data
struct ProjectileData
{

};

//Attack
struct Attack
{
	//Motion
	Motion motions[GC::MAX_MOTIONS];

	//Setup bools
	bool movingWithEntity = false; //If this motion is moving with the entity
	bool followingFacing = false; //If the attack is actively following the entity facing
	bool hasTwoMotions = false; //If this is the first of two motions
	bool arcCentredOnInitialAngle = false; //If this attack is centred on the initial angle
	bool alternatingSwingDirection = false; //If this attack's inital position and direction changes on each swing

	//Operational bools
	bool active = false;
	bool attackRelease = false;
	bool motionFinished = false;

	//Positioning
	sf::FloatRect globalRect{};
	sf::FloatRect localRect{};
	Dim2Df origin{};
	float initialAngle = 0.f;
	char swingDirection = 1;

	//Pointers
	sf::Sprite* sprite{};
	sf::FloatRect* originRect{};
	Dim2Df* originRectOffset{};
	DirectionalAngle* facing{};
	float* radius{};
	float* attackSpeed{};

	//Initiates attack
	void Init(const GameData& game, sf::Sprite& motionSprite, sf::FloatRect& entityRect, DirectionalAngle& entityFacing, float& entityAttackSpeed, float& holdDistance, Dim2Df& holdVector);

	//Updates attack
	void UpdateAttack(const GameData& game);

	//Update loop for attack
	void UpdateAttackMotion(const GameData& game, Motion& motion);

	//Moves the global rect to it's original position around the entity
	void RepositionGlobalRectToEntity();

	//Moves the global rect to it's original position
	void RepositionGlobalRectToOrigin();

	//Updates the rotation of the sprite
	void UpdateRotation(const Motion& motion);
};

//Weapon
struct Weapon
{
	//Attacks
	Attack attack0{}; //Normal attack
	Attack attack1{}; //Heavy attack

	//Setup bools
	bool hasTwoAttacks = false; //Weapon has a second attack or not
	bool visible = false; //Holding a weapon or not

	//Main stats
	float range = 0.f; //How far the weapon can reach
	short int damage = 1; //How much damage this
	short int knockbackStrength = 0; //Power of knockback this weapon can inflict

	//SFML
	sf::Texture* texture{}; //Weapon texture
	sf::Sprite sprite{}; //Weapon sprite

	//Operating bools
	bool attacking = false; //In attack animation
	bool active = false; //Is weapon currently being held

	//Position
	float holdDistance = 0.f; //How far away the weapon is held
	Dim2Df holdOrigin = { 0.f, 0.f }; //The point that the weapon will rotate around, from top left of entity's sprite
	Dim2Df holdVector = { 0.f, 0.f }; //Vector from origin, where the weapon will be held
	sf::FloatRect globalRect = { 0.f, 0.f, 0.f, 0.f };
	sf::FloatRect localRect = { 0.f, 0.f, 0.f, 0.f };

	//Functions

	//Initializes the weapon from a template
	void Init(const char& type);

	//Updates the position of the weapon
	void UpdateHoldPosition(const DirectionalAngle& facing, const sf::FloatRect& entityRect);

	//Updates the rotation of the weapon
	void UpdateHoldRotation(const DirectionalAngle& facing);
};

namespace GC
{
	//Attacks															(bools: movingWithEntity, followingFacing, hasTwoMotions, arcCentredOnInitialAngle, hasRandomSwingDirection)
	const Attack NORMAL_SWING_ATTACK = { {GC::NORMAL_SWING_RELEASE},							true, false, false, true, true };
	const Attack HEAVY_SWING_ATTACK = { {GC::HEAVY_SWING_WINDUP, GC::HEAVY_SWING_RELEASE},		true, true, true, false, false };
	const Attack HEAVY_THRUST_ATTACK = { {GC::HEAVY_THRUST_WINDUP, GC::HEAVY_THRUST_RELEASE},	true, true, true, false, false };
	const Attack NORMAL_THRUST_ATTACK = { {GC::NORMAL_THRUST_RELEASE},							true, true, false, false, false };
	const Attack SWORD_OF_DOOM_ATTACK = { {GC::SWORD_OF_DOOM},									false, true, false, false, false };

	//Weapons
	//const Weapon;
}