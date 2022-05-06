#pragma once
#include "data.h"

/*Data used for circular motion
Contains:
float rotation (in degrees)
float time (in seconds)
Notes:
Angle is from facing right*/
struct CircularMotionData
{
	float rotation = 0.f; //The angle that the motion ends at in relation to facing, in degrees
	float time = 0.f; //Time it takes to complete full motion
};

/*Data used for line motion
Contains:
Dim2Df translation (in pixels)
float time (in seconds)
Notes:
Translation is from facing right
Y is used as direction for motions
that are locked onto facing*/
struct LineMotionData
{
	Dim2Df translation = { 0.f, 0.f }; //Where the motion ends in relation to facing, in pixels
	float time = 0.f; //Time it takes to complete full motion
};

/*Motion of a sprite
Requirements:
All motion data in a single motion must either have
the exact same time, or not be required to (e.g. a
spin can keep going until the end of any motion)*/
struct Motion
{
	//Data
	const CircularMotionData* circleData{}; //Circular motion data
	const LineMotionData* lineData{}; //Line motion data
	const CircularMotionData* spinData{}; //Spin circular motion data

	//Setup bools
	bool circular = false; //Is this a circular motion
	bool line = false; //Is this a straight line motion
	bool spin = false; //Is this sprite spinning while in motion
	bool damage = false; //Can this motion deal damage
	bool loop = false; //Whether the motion keeps going or not

	//Operational bools
	bool active = false; //Whether this motion is currently active
	bool facingRight = true; //Whether this motion is facing right or not


	//Speed
	float circleSpeed = 0.f; //The speed of the motion's rotation, in degrees per second
	Dim2Df lineSpeed{}; //The speed of the motion's movement, in pixels per second
	float spinSpeed = 0.f; //The speed of the motion's spin, in degrees per second

	//Counters
	float circleTotal = 0.f; //The total change in motion's angle, in degrees
	Dim2Df lineTotal{}; //The total change in motion's position
	float spinTotal = 0.f; //The total change in the motion's spin, in degrees
	float timer = 0.f; //Keeps track of time elapsed since motion started

	//Initiates motion
	void Init(const GameData& game, const DirectionalAngle& facing, const float& attackSpeed, const int& swingDirection, const bool& followingFacing);

	//Updates motion totals
	void UpdateTotals(const GameData& game);

	//Updates the position of the global rect
	void UpdatePosition(sf::FloatRect& globalRect, const bool& followingFacing, const float& initialAngle, const float& radius, const DirectionalAngle& facing);

	//Resets the motion back to original values
	void ResetTotals();
};

namespace GC
{ 
	//Circular motion data
	//Normal attacks
	const CircularMotionData SWING_ARC = { 140.f, 0.3f }; //Weapon swing arc, movement and rotation of normal swing
	//Windup attacks
	const CircularMotionData WINDUP_ARC_SLOW = { -90.f, 1.f }; //Slow arc attack windup, movement and rotation
	const CircularMotionData WINDUP_ARC_FAST = { -90.f, 0.5f }; //Fast arc attack windup, movement and rotation
	const CircularMotionData WINDUP_SWING_ARC = { 90.f, 0.2f }; //Weapon swing arc, after windup

	//Line motion data
	//Normal attacks
	const LineMotionData THRUST_LINE = { { 16.f, 1.f }, 0.2f }; //Weapon thrust, movement of normal thrust
	//Windup attacks
	const LineMotionData WINDUP_LINE_SLOW = { { 8.f, -1.f }, 1.f }; //Slow pullback, attack windup
	const LineMotionData WINDUP_LINE_FAST = { { 8.f, -1.f }, 0.5f }; //Fast pullback, attack windup
	const LineMotionData WINDUP_THRUST = { { 32.f, 1.f }, 0.2f }; //Weapon thrust, after windup
	const LineMotionData WINDUP_ARC_SLOW_LINE = { { 4.f, -1.f }, 1.f }; //Slow arc attack windup's backward movement
	const LineMotionData WINDUP_ARC_FAST_LINE = { { 4.f, -1.f }, 0.5f }; //Fast arc attack windup's backward movement
	const LineMotionData WINDUP_SWING_LINE = { { 16.f, 1.f }, 0.2f }; //Weapon swing arc's forward movement
	//Projectiles
	const LineMotionData PROJECTILE_LINE_SLOW = { { 160.f, 1.f }, 1.f }; //Slow projectile
	const LineMotionData PROJECTILE_LINE_FAST = { { 240.f, 1.f }, 1.f }; //Fast projectile

	//Spin motion data
	//Windup attacks
	const CircularMotionData WINDUP_ARC_SPIN = { -180.f, 1.f }; //Slow arc attack windup, movement and rotation
	const CircularMotionData WINDUP_SWING_SPIN = { 180.f, 0.2f }; //Weapon swing spin, after windup
	//Spins
	const CircularMotionData SPIN_SLOW = { 360.f, 0.4f }; //Slow spin
	const CircularMotionData SPIN_FAST = { 360.f, 0.2f }; //Fast spin
	const CircularMotionData SPIN_HELL = { 3600.f, 1.f }; //Hell spin... of doom

	//Motions																								(bools: circular, line, spin, damage, loop)
	//Normal melee motions
	const Motion NORMAL_SWING_RELEASE = { &GC::SWING_ARC, {}, &GC::SWING_ARC,											true, false, true, true, false };
	const Motion NORMAL_THRUST_RELEASE = { {}, &GC::THRUST_LINE, {},													false, true, false, true, false };
	//Heavy melee motions
	const Motion HEAVY_SWING_WINDUP = { &GC::WINDUP_ARC_SLOW, &WINDUP_ARC_SLOW_LINE, &GC::WINDUP_ARC_SPIN,				true, true, true, false, false };
	const Motion HEAVY_SWING_RELEASE = { &GC::WINDUP_SWING_ARC, &WINDUP_SWING_LINE, &GC::WINDUP_SWING_SPIN,				true, true, true, true, false };
	const Motion HEAVY_THRUST_WINDUP = { {}, &GC::WINDUP_LINE_SLOW, {},													false, true, false, false, false };
	const Motion HEAVY_THRUST_RELEASE = { {}, &GC::WINDUP_THRUST, {},													false, true, false, true, false };
	//Normal projectile motions
	const Motion SPINNING_THROW_SLOW = { {}, &GC::PROJECTILE_LINE_SLOW, &GC::SPIN_SLOW,									false, true, true, true, false };
	const Motion STRAIGHT_THROW_SLOW = { {}, &GC::PROJECTILE_LINE_SLOW, {},												false, true, false, true, false };
	//Heavy projectile motions

	//Super attacks
	const Motion SWORD_OF_DOOM = { &GC::SPIN_HELL, &GC::PROJECTILE_LINE_FAST, &GC::SPIN_HELL,							true, true, true, true, false };
}