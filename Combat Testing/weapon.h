#pragma once
#include "motion.h"

//Data used for projectiles
//Setup:
//const Motion* motion, const sf::IntRect* textureRect, char damage, char num, char spread
struct ProjectileData
{
	const Motion* motion; //Motion of this projectile
	float radius = 0.f; //Radius of any circular motion
	char baseDamage = 0; //Base damage of the projectile
	char num = 0; //Number of projectiles in this attack
	float spread = 0.f; //How far apart the extra projectiles are spread, from the initial angle, in degrees
};

//Projectile
struct Projectile
{
	//Setup stats
	Motion motion{};
	char damage = 0;

	//Setup bools
	bool followingFacing = true; //If the projectile is actively following the entity facing

	//Operational bools
	bool active = false;

	//Positioning
	Dim2Df origin = { 0.f, 0.f };
	float angle = 0.f;

	//Pointers
	DirectionalAngle* facing = nullptr;
	ProjectileData data{};

	//Functional variables
	sf::Sprite sprite{};

	//Updates the projectile
	void Update(const GameData& game);

	//Renders the projectile
	void Render(sf::RenderWindow& window);
};

//Attack
struct Attack
{
	//Setup stats
	Motion motions[GC::MAX_MOTIONS]; //Attack motions
	const ProjectileData* projectileData = nullptr; //Data of this attack's projectile
	short range = 0; //Attack range, in pixels (0 means default weapon range, -1 means unlimited)

	//Setup bools
	bool summonProjectile = false; //If this attack summons a projectile after the motion has finished
	bool movingWithEntity = false; //If this motion is moving with the entity
	bool followingFacing = false; //If the attack is actively following the entity facing
	bool hasTwoMotions = false; //If this is the first of two motions
	bool arcCentredOnInitialAngle = false; //If this attack is centred on the initial angle
	bool alternatingSwingDirection = false; //If this attack's inital position and direction changes on each swing

	//Operational bools
	bool active = false; //If attack is active
	bool attackRelease = false; //If second motion should begin
	bool motionFinished = false; //If all motions for this attack are finished
	bool entityIsWeapon = false; //If the entity sprite is the attacking object

	//Positioning
	Dim2Df origin{};
	float initialAngle = 0.f;
	char swingDirection = 1;

	//Pointers
	sf::Sprite* sprite = nullptr;
	sf::Sprite* entitySprite = nullptr;
	Dim2Df* originRectOffset = nullptr;
	DirectionalAngle* facing = nullptr;
	float* radius = nullptr;
	float* attackSpeed = nullptr;

	//Initiates attack
	void Init(const GameData& game, sf::Sprite& motionSprite, sf::Sprite* eSprite, DirectionalAngle& entityFacing, float& entityAttackSpeed, float& holdDistance, const bool& eIsWep);

	//Updates attack
	void UpdateAttack(const GameData& game, std::vector<Projectile>& projList);

	//Update loop for attack
	void UpdateAttackMotion(const GameData& game, Motion& motion);

	//Adds projectiles to the list
	void SpawnProjectiles(const GameData& game, std::vector<Projectile>& projList);

	//Immediately stops the attack and resets values
	void Stop();
};

//Weapon
struct Weapon
{
	//Attacks
	Attack attack0{}; //Normal attack
	Attack attack1{}; //Heavy attack

	//Setup bools
	bool hasTwoAttacks = false; //Weapon has a second attack or not
	bool entityIsWeapon = false; //If entity is the weapon

	//Operational bools
	bool visible = false; //Holding a weapon or not

	//SFML
	sf::Texture* texture = nullptr; //Weapon texture
	sf::Sprite sprite{}; //Weapon sprite
	
	//Operating bools
	bool attacking = false; //In attack animation
	bool active = false; //Is weapon currently being held

	//Position
	float holdDistance = 0.f; //How far away the weapon is held

	//Initializes the weapon from a template
	void Init(const char& type);

	//Updates the position of the weapon
	void UpdateHoldPosition(const DirectionalAngle& facing, const Dim2Df holdOrigin);

	//Updates the rotation of the weapon
	void UpdateHoldRotation(const DirectionalAngle& facing);
};

//Updates the rotation of the sprite
void UpdateRotation(const Motion& motion, sf::Sprite& sprite, const float& initialAngle);

//Initializes all projectiles
void InitProjectiles(const GameData& game, std::vector<Projectile>& projList);

//Updates all active projectiles
void UpdateProjectiles(const GameData& game, sf::RenderWindow& window, std::vector<Projectile>& projList);

namespace GC
{
	//Projectile data
	const ProjectileData PROJECTILE_DATA_STRAIGHT_THROW = { &STRAIGHT_THROW_SLOW, 0.f, 1, 1, 18.f };
	const ProjectileData PROJECTILE_DATA_SPINNING_THROW = { &SPINNING_THROW_SLOW, 0.f, 1, 1, 18.f };

	//Attacks										(bools: summonProjectile, movingWithEntity, followingFacing, hasTwoMotions, arcCentredOnInitialAngle, hasRandomSwingDirection)
	//Swing
	const Attack NORMAL_SWING_ATTACK = { {NORMAL_SWING_RELEASE}, {}, 0,												false, true, false, false, true, true }; //Normal swing attack
	const Attack HEAVY_SWING_ATTACK = { {HEAVY_SWING_WINDUP, GC::HEAVY_SWING_RELEASE}, {}, 12,						false, true, true, true, false, false }; //Heavy swing attack
	//Thrust
	const Attack NORMAL_THRUST_ATTACK = { {NORMAL_THRUST_RELEASE}, {}, 16,											false, true, true, false, false, false }; //Normal thrust attack
	const Attack HEAVY_THRUST_ATTACK = { {HEAVY_THRUST_WINDUP, HEAVY_THRUST_RELEASE}, {}, 24,						false, true, true, true, false, false }; //Heavy thrust attack
	//Throw
	const Attack NORMAL_STRAIGHT_THROW_ATTACK = { {THROW_PROJECTILE_FAST}, &PROJECTILE_DATA_STRAIGHT_THROW, -1,		true, true, true, false, false, false }; //Normal throw attack
	const Attack NORMAL_SPINNING_THROW_ATTACK = { {THROW_PROJECTILE_FAST}, &PROJECTILE_DATA_SPINNING_THROW, -1,		true, true, true, false, false, false }; //Normal spinning throw attack
	//Shoot

	//Special
	const Attack SWORD_OF_DOOM_ATTACK = { {SWORD_OF_DOOM}, {}, 240,													false, false, true, false, false, false }; //Sword of doom attack

	//Enemy attacks
	const Attack HORN_STAB = { {HORN_STAB_JUMP}, {}, 64,															false, false, false, false, false, false }; //Horn stab jump attack
	const Attack CHARGE = { {CHARGE_WINDUP, CHARGE_RELEASE}, {}, 160,												false, false, false, true, false, false }; //Horn charge attack

	//Weapons															(bools: hasTwoAttacks, entityIsWeapon)
	const Weapon RUSTED_SWORD = { NORMAL_SWING_ATTACK, HEAVY_THRUST_ATTACK,		true, false };
	const Weapon BIG_FANCY_SWORD = { NORMAL_SWING_ATTACK, HEAVY_SWING_ATTACK,	true, false };
	const Weapon SPEAR = { NORMAL_THRUST_ATTACK, HEAVY_THRUST_ATTACK,			true, false };
	const Weapon IMP_WEAPON = { HORN_STAB, CHARGE,								true, true };
}