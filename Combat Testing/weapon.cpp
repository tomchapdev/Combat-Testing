#include "weapon.h"
#include "maths.h"

//Initiates attack
void Attack::Init(const GameData& game, sf::Sprite& motionSprite, sf::FloatRect& entityRect, DirectionalAngle& entityFacing, float& entityAttackSpeed, float& holdDistance, Dim2Df& holdOrigin)
{
	active = true;
	motionFinished = false;
	sprite = &motionSprite;

	if (movingWithEntity)
	{
		originRect = &entityRect;
	}
	else
	{
		origin.x = motionSprite.getPosition().x + game.mapRect.left;
		origin.y = motionSprite.getPosition().y + game.mapRect.top;
	}
	
	facing = &entityFacing;
	attackSpeed = &entityAttackSpeed;
	radius = &holdDistance;
	originRectOffset = &holdOrigin;
 	initialAngle = GetFullAngleInDegrees(*facing);

	globalRect.left = sprite->getPosition().x + game.mapRect.left;
	globalRect.top = sprite->getPosition().y + game.mapRect.top;

	if (alternatingSwingDirection)
	{
		if (swingDirection == 1)
		{
			swingDirection = -1;
		}
		else
		{
			swingDirection = 1;
		}
	}

	motions[0].Init(game, *facing, *attackSpeed, swingDirection, followingFacing);

	if (arcCentredOnInitialAngle)
	{
		if (facing->direction == GC::NORTH || facing->direction == GC::EAST) //Right
		{
			initialAngle -= (motions[0].circleData->rotation / 2.f) * swingDirection;
		}
		else //Left
		{
			initialAngle += (motions[0].circleData->rotation / 2.f) * swingDirection;
		}
	}
}

//Updates attack
void Attack::UpdateAttack(const GameData& game)
{
	if (motions[0].active)
	{
		UpdateAttackMotion(game, motions[0]);

		/*if (!motions[0].active && hasTwoMotions)
		{
			motions[1].Init(game, *facing, *attackSpeed, swingDirection, followingFacing);

			if (motions[0].circular)
			{
				motions[1].circleTotal += motions[0].circleTotal;
			}
			if (motions[0].line)
			{
				if (followingFacing)
				{
					motions[1].lineTotal.x += motions[0].lineTotal.x * motions[0].lineData->translation.y;
					//motions[1].lineTotal.y += motions[0].lineTotal.y * motions[0].lineData->translation.y;
				}
				else
				{
					motions[1].lineTotal.x += motions[0].lineTotal.x;
					motions[1].lineTotal.y += motions[0].lineTotal.y;
				}
			}
			if (motions[0].spin)
			{
				motions[1].spinTotal += motions[0].spinTotal;
			}
		}*/
	}
	else if (!motions[0].active && hasTwoMotions && attackRelease)
	{
		motions[1].Init(game, *facing, *attackSpeed, swingDirection, followingFacing);

		if (motions[0].circular)
		{
			motions[1].circleTotal += motions[0].circleTotal;
		}
		if (motions[0].line)
		{
			if (followingFacing)
			{
				motions[1].lineTotal.x += motions[0].lineTotal.x * motions[0].lineData->translation.y;
			}
			else
			{
				motions[1].lineTotal.x = motions[0].lineTotal.x;
				motions[1].lineTotal.y = motions[0].lineTotal.y;
			}
		}
		if (motions[0].spin)
		{
			motions[1].spinTotal += motions[0].spinTotal;
		}

		attackRelease = false;
		UpdateAttackMotion(game, motions[1]);
	}
	else if (!motions[0].active && hasTwoMotions && !motions[1].active && !attackRelease && !motionFinished)
	{
		//Update the position and rotation of the not yet released attack
		if (movingWithEntity)
		{
			RepositionGlobalRectToEntity();
		}
		else
		{
			RepositionGlobalRectToOrigin();
		}

		if (followingFacing)
		{
			initialAngle = GetFullAngleInDegrees(*facing);
		}

		motions[0].UpdatePosition(globalRect, followingFacing, initialAngle, *radius, *facing);
		UpdateRotation(motions[0]);
		UpdateSpritePosition(game, *sprite, globalRect, localRect);
	}
	else if (motions[1].active && hasTwoMotions)
	{
		UpdateAttackMotion(game, motions[1]);

		if (!motions[1].active)
		{
			motionFinished = true;
		}
	}
	else if (!hasTwoMotions || motionFinished)
	{
		active = false;
		motions[0].ResetTotals();
		motions[1].ResetTotals();
	}
}

//Update loop for attack
void Attack::UpdateAttackMotion(const GameData& game, Motion& motion)
{
	if (motion.timer < 0.f)
	{
		motion.active = false;
	}
	else
	{
		//Setup
		motion.UpdateTotals(game);

		if (followingFacing)
		{
			initialAngle = GetFullAngleInDegrees(*facing);
		}

		//Motion position
		if (movingWithEntity)
		{
			RepositionGlobalRectToEntity();
		}
		else
		{
			RepositionGlobalRectToOrigin();
		}

		motion.UpdatePosition(globalRect, followingFacing, initialAngle, *radius, *facing);
		UpdateRotation(motion);
		UpdateSpritePosition(game, *sprite, globalRect, localRect);

		//Time
		if (!motion.loop)
		{
			//motion.timer -= game.elapsed;
			motion.timer -= (1.f / (float)GC::FRAMERATE);
		}
	}
}

//Moves the global rect to it's original position around the entity, used when moving with entity
void Attack::RepositionGlobalRectToEntity()
{
	globalRect.left = originRect->left + originRectOffset->x;
	globalRect.top = originRect->top + originRectOffset->y;
}

//Moves the global rect to it's original position
void Attack::RepositionGlobalRectToOrigin()
{
	globalRect.left = origin.x;
	globalRect.top = origin.y;
}

//Updates the rotation of the sprite
void Attack::UpdateRotation(const Motion& motion)
{
	if (motion.spin)
	{
		sprite->setRotation(initialAngle + motion.spinTotal);
	}
	else //if (followingFacing)
	{
		sprite->setRotation(initialAngle);
	}
}

//Immediately stops the attack and resets values
void Attack::Stop()
{
	motions[0].active = false;
}

//Initializes the weapon
void Weapon::Init(const char& type)
{

}

//Updates the position of the weapon
void Weapon::UpdateHoldPosition(const DirectionalAngle& facing, const sf::FloatRect& entityRect)
{
	Dim2Df finalPosition;
	finalPosition = CalculateCircularMotionVector(holdDistance, GetFullAngleInRads(facing));
	finalPosition.x += entityRect.left + holdOrigin.x;
	finalPosition.y += entityRect.top + holdOrigin.y;
	sprite.setPosition(finalPosition.x, finalPosition.y);
}

//Updates the rotation of the weapon
void Weapon::UpdateHoldRotation(const DirectionalAngle& facing)
{
	float rotation = GetFullAngleInDegrees(facing);

	//sprite.setRotation(rotation);

	if (rotation < GC::DEGREES_180)
	{
		sprite.setRotation(GC::WEAPON_HOVER_ROTATION);
	}
	else
	{
		sprite.setRotation(-GC::WEAPON_HOVER_ROTATION);
	}

	/*
	//Smooth weapon rotation, checking clockwise
	if (rotation < GC::DEGREES_180) //Right
	{
		if (rotation < GC::WEAPON_HOVER_ROTATION) //Top right
		{
			sprite.setRotation(rotation);
		}
		else if (rotation > (GC::DEGREES_180 - GC::WEAPON_HOVER_ROTATION)) //Bottom right
		{
			sprite.setRotation(GC::DEGREES_180 - rotation);
		}
		else
		{
			sprite.setRotation(GC::WEAPON_HOVER_ROTATION);
		}
	}
	else //Left
	{
		if (rotation > (GC::DEGREES_360 - GC::WEAPON_HOVER_ROTATION)) //Top left
		{
			sprite.setRotation(rotation);
		}
		else if (rotation < (GC::DEGREES_180 + GC::WEAPON_HOVER_ROTATION)) //Bottom left
		{
			sprite.setRotation(GC::DEGREES_180 - rotation);
		}
		else
		{
			sprite.setRotation(GC::DEGREES_360 - GC::WEAPON_HOVER_ROTATION);
		}
	}*/
}