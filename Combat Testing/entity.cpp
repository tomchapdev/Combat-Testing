#include "entity.h"
#include "maths.h"

//Functions

//Initiates an attack
void Entity::InitAttack(const GameData& game, const char& attack)
{
	canAttack = false;
	weapon.attacking = true;

	if (attack == GC::FIRST_ATTACK)
	{
		weapon.attack0.Init(game, weapon.sprite, globalRect, facing, attackSpeed, weapon.holdDistance, weapon.holdOrigin);
	}
	else if (weapon.hasTwoAttacks && attack == GC::SECOND_ATTACK)
	{
		weapon.attack1.Init(game, weapon.sprite, globalRect, facing, attackSpeed, weapon.holdDistance, weapon.holdOrigin);
	}
}

//Initiates a knockback
void Entity::InitKnockback()
{

}

//Updates movement vector based on target coords
void Entity::UpdateMovementVector(const Dim2Df& target)
{
	//Find origin
	Dim2Df origin = {	globalRect.left + bodyCentre.x,
						globalRect.top + bodyCentre.y};

	//Get vector between points, then calculate directional angle using vector
	facing = CalculateDirectionalAngleFromVector( CalculateVectorBetweenPoints(origin, target) );

	movementVector = CalculateVectorOfMagnitude(facing, speed);
}

//Move the entity and weapon
void Entity::Move(GameData& game)
{
	//float moveX = movementVector.x * GC::APPROX_ELAPSED, moveY = movementVector.y * GC::APPROX_ELAPSED;
	float moveX = movementVector.x * game.elapsed, moveY = movementVector.y * game.elapsed;

	if (moving)
	{
		globalRect.left += moveX;
		globalRect.top += moveY;
	}

	float x = 0.f, y = 0.f;

	if (weapon.attacking)
	{
		UpdateAttacks(game);

		//Weapon movement correction
		if (moving)
		{
			x -= moveX;
			y -= moveY;
		}
	}
	else
	{
		weapon.UpdateHoldPosition(facing, localRect);
		weapon.UpdateHoldRotation(facing);
	}

	//Weapon bobbing
	if (anim.currentFrame == 5)
	{
		y -= GC::SPRITE_SCALE;
	}
	else if (anim.currentFrame == 7)
	{
		y += GC::SPRITE_SCALE;
	}
	else if (anim.currentFrame < 4 && anim.currentFrame != 0)
	{
		y -= ((anim.currentFrame % 2) - 2) * GC::SPRITE_SCALE;
	}
	
	weapon.sprite.move({ x, y });
}

//Render the entity if it's on the rendered map area
void Entity::Render(sf::RenderWindow& window, const GameData& game)
{
	//Check if in rendered area
	if (isPlayer)
	{
		nearPlayer = UpdateSpritePosition(game, sprite, globalRect, localRect);
		
		if (nearPlayer && weapon.visible && !weapon.attacking)
		{
			UpdateSpritePosition(game, weapon.sprite, weapon.globalRect, weapon.localRect);
		}
	}

	if (nearPlayer || isPlayer)
	{
		anim.UpdateAnimation(sprite, game.elapsed);

		//Flip and move sprite based on facing
		if ((facing.direction == GC::NORTH) || (facing.direction == GC::EAST))
		{
			if (!facingRight)
			{
				sprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
				bodyCentre.x = globalRect.width - bodyCentre.x;
				facingRight = true;
			}
		}
		else
		{
			if (facingRight)
			{
				sprite.setScale(-GC::SPRITE_SCALE, GC::SPRITE_SCALE);
				bodyCentre.x = globalRect.width - bodyCentre.x;
				facingRight = false;
			}

			//Adjust for drawing, this is because scale -1 flips the sprite but also alters where it draws the sprite
			sprite.move(globalRect.width, 0.f);
		}

		if (weapon.visible)
		{
			if ((facing.direction == GC::WEST) || (facing.direction == GC::NORTH))
			{
				window.draw(weapon.sprite);
				window.draw(sprite);
			}
			else
			{
				window.draw(sprite);
				window.draw(weapon.sprite);
			}
		}
		else
		{
			window.draw(sprite);
		}

		if (!facingRight)
		{
			//Re-adjust for correct collision etc
			sprite.move(-globalRect.width, 0.f);
		}

	}
}

//Updates any ongoing attacks
void Entity::UpdateAttacks(const GameData& game)
{
	if (weapon.attack0.active)
	{
		weapon.attack0.UpdateAttack(game);
	}
	else if (weapon.hasTwoAttacks && weapon.attack1.active)
	{
		weapon.attack1.UpdateAttack(game);
	}
	else
	{
		weapon.attacking = false;
		canAttack = true;
	}
}

void Entity::TakeDamage()
{

}