#include "weapon.h"
#include "maths.h"

//Updates the projectile
void Projectile::Update(const GameData& game)
{
	//Motion
	if (motion.timer < 0.f)
	{
		active = false;
		motion.active = false;
	}
	else
	{
		//Setup
		motion.UpdateTotals(game);
		RepositionGlobalRectToOrigin(globalRect, sprite, origin);

		motion.UpdatePosition(globalRect, followingFacing, *facing, angle, {});
		UpdateRotation(motion, sprite, angle);
		UpdateSpritePosition(game, sprite, globalRect, localRect);
		
		//COLLISION DETECTION NEEDS TO GO HERE!

		//Time
		if (!motion.loop)
		{
			//motion.timer -= game.elapsed;
			motion.timer -= (1.f / (float)GC::FRAMERATE);
		}
	}
}

//Renders the projectile
void Projectile::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

//Initiates attack
void Attack::Init(const GameData& game, sf::Sprite& motionSprite, sf::FloatRect& entityRect, DirectionalAngle& entityFacing, float& entityAttackSpeed, float& holdDistance, Dim2Df& holdOrigin, const bool& eIsWep)
{
	active = true;
	motionFinished = false;
	sprite = &motionSprite;
	entityIsWeapon = eIsWep;

	if (entityIsWeapon || movingWithEntity)
	{
		originRect = &entityRect;
	}
	if (!movingWithEntity)
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
void Attack::UpdateAttack(const GameData& game, std::vector<Projectile>& projList)
{
	if (motions[0].active) //First motion
	{
		UpdateAttackMotion(game, motions[0]);
	}
	else if (!motions[0].active && hasTwoMotions && attackRelease) //Initiate second motion
	{
		motions[1].Init(game, *facing, *attackSpeed, swingDirection, followingFacing);

		if (motions[0].circular)
		{
			motions[1].circleTotal = motions[0].circleTotal;
		}
		if (motions[0].line)
		{
			if (followingFacing)
			{
				motions[1].lineTotal.x = motions[0].lineTotal.x * motions[0].lineData->translation.y;
			}
			else
			{
				motions[1].lineTotal.x = motions[0].lineTotal.x;
				motions[1].lineTotal.y = motions[0].lineTotal.y;
			}
		}
		if (motions[0].spin)
		{
			motions[1].spinTotal = motions[0].spinTotal;
		}

		attackRelease = false;
		UpdateAttackMotion(game, motions[1]);
	}
	else if (!motions[0].active && hasTwoMotions && !motions[1].active && !attackRelease && !motionFinished) //Holding attack after first motion
	{
		if (movingWithEntity)
		{
			RepositionGlobalRectToEntity();
		}
		else
		{
			RepositionGlobalRectToOrigin(globalRect, *sprite, origin);
		}

		if (followingFacing)
		{
			initialAngle = GetFullAngleInDegrees(*facing);
		}

		motions[0].UpdatePosition(globalRect, followingFacing, *facing, initialAngle, *radius);
		UpdateSpritePosition(game, *sprite, globalRect, localRect);

		if (entityIsWeapon)
		{
			UpdateRotation(motions[0], *sprite, GC::ZERO);
		}
		else
		{
			UpdateRotation(motions[0], *sprite, initialAngle);
		}
	}
	else if (motions[1].active && hasTwoMotions) //Second motion
	{
		UpdateAttackMotion(game, motions[1]);

		if (!motions[1].active)
		{
			motionFinished = true;
		}
	}
	else if (!hasTwoMotions || motionFinished) //Finish motion
	{
		if (summonProjectile)
		{
			SpawnProjectiles(game, projList);
		}

		Stop();
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
			RepositionGlobalRectToOrigin(globalRect, *sprite, origin);
		}

		motion.UpdatePosition(globalRect, followingFacing, *facing, initialAngle, *radius);

		if (entityIsWeapon)
		{
			*originRect = globalRect;
		}

		UpdateSpritePosition(game, *sprite, globalRect, localRect);

		if (entityIsWeapon)
		{
			UpdateRotation(motion, *sprite, GC::ZERO);
		}
		else
		{
			UpdateRotation(motion, *sprite, initialAngle);
		}

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
	globalRect.left = originRect->left + originRectOffset->x - sprite->getOrigin().x;
	globalRect.top = originRect->top + originRectOffset->y - sprite->getOrigin().y;
}

//Adds projectiles to the list
void Attack::SpawnProjectiles(const GameData& game, std::vector<Projectile>& projList)
{
	//Setup
	unsigned char projectileCount = projectileData->num;
	short index = 0;
	bool hasSpread;
	std::vector<float> spreadList(projectileCount);

	//Calculate spread
	if (projectileCount > 1)
	{
		hasSpread = true;
		bool unevenProjectileNum = projectileCount % 2;
		unsigned char spreadCounter = projectileCount;

		while (spreadCounter > 0)
		{
			float spread = projectileData->spread;

			if (unevenProjectileNum)
			{
				//Evenly spread around the initialAngle except from the last projectile
				if (spreadCounter != 1)
				{
					spread *= spreadCounter / 2;

					if ((spreadCounter % 2) == 1)
					{
						spread *= -1;
					}
				}
				else
				{
					spread = 0.f;
				}
			}
			else
			{
				//Evenly spread around the initialAngle
				spread *= (spreadCounter + 1) / 2;

				if ((spreadCounter % 2) == 1)
				{
					spread *= -1;
				}
			}

			spreadList[spreadCounter - 1] = spread;
			spreadCounter -= 1;
		}
	}
	else
	{
		hasSpread = false;
	}

	//Find an 
	while (projectileCount > 0)
	{
		if (projList[index].active)
		{
			index += 1;
		}
		else if (index < GC::MAX_PROJECTILES)
		{
			projList[index].active = true;
			projList[index].motion = *projectileData->motion;
			projList[index].damage = projectileData->baseDamage;
			projList[index].sprite.setTextureRect(*projectileData->textureRect);

			projList[index].sprite.setOrigin(projList[index].sprite.getGlobalBounds().width / 2.0f, projList[index].sprite.getGlobalBounds().height / 2.0f);
			//projList[index].sprite.setPosition({ localRect.left + projList[index].sprite.getOrigin().x, localRect.top + projList[index].sprite.getOrigin().y });
			projList[index].sprite.setPosition(sprite->getPosition());
			projList[index].globalRect = globalRect;

			/*projList[index].origin.x = globalRect.left + projList[index].sprite.getOrigin().x;
			projList[index].origin.y = globalRect.top + projList[index].sprite.getOrigin().y;*/

			if (hasSpread)
			{
				projList[index].angle = initialAngle + spreadList[projectileCount - 1];
			}
			else
			{
				projList[index].angle = initialAngle;
			}
			ConstrainAngle(projList[index].angle, false);

			projList[index].motion.Init(game, GetDirectionalAngleFrom360Angle(projList[index].angle, false), *attackSpeed, 1, true);
			projList[index].sprite.setRotation(projList[index].angle);
			projList[index].followingFacing = followingFacing; //Need to change this

			if (followingFacing)
			{
				projList[index].facing = facing;
			}

			projectileCount -= 1;
			index += 1;
		}
		else
		{
			break;
		}
	}
}

//Immediately stops the attack and resets values
void Attack::Stop()
{
	active = false;
	motions[0].ResetTotals();
	motions[1].ResetTotals();
}

//Initializes the weapon from a template
void Weapon::Init(const char& type)
{

}

//Updates the position of the weapon
void Weapon::UpdateHoldPosition(const GameData& game, const DirectionalAngle& facing, const sf::FloatRect& entityRect)
{
	//Calculate position
	Dim2Df position;
	position = CalculateCircularMotionVector(holdDistance, GetFullAngleInRads(facing));
	position.x += entityRect.left + holdOrigin.x;
	position.y += entityRect.top + holdOrigin.y;

	//Set position
	sprite.setPosition(position.x, position.y);
}

//Updates the rotation of the weapon
void Weapon::UpdateHoldRotation(const DirectionalAngle& facing)
{
	float rotation = GetFullAngleInDegrees(facing);

	if (rotation < GC::DEGREES_180)
	{
		sprite.setRotation(GC::WEAPON_HOVER_ROTATION);
	}
	else
	{
		sprite.setRotation(-GC::WEAPON_HOVER_ROTATION);
	}
}

//Moves the global rect to it's original position
void RepositionGlobalRectToOrigin(sf::FloatRect& globalRect, sf::Sprite& sprite, const Dim2Df& origin)
{
	sprite.setPosition(origin);
	globalRect = sprite.getGlobalBounds();
}

//Updates the rotation of the sprite
void UpdateRotation(const Motion& motion, sf::Sprite& sprite, const float& initialAngle)
{
	if (motion.spin)
	{
		sprite.setRotation(initialAngle + motion.spinTotal);
	}
	else //if (followingFacing)
	{
		sprite.setRotation(initialAngle);
	}
}

//Initializes all projectiles
void InitProjectiles(const GameData& game, std::vector<Projectile>& projList)
{
	for (short index = 0; index < GC::MAX_PROJECTILES; ++index)
	{
		projList[index].sprite.setTexture(game.textures[GC::SPRITESHEET_TEXTURE]);
	}
}

//Updates all active projectiles
void UpdateProjectiles(const GameData& game, sf::RenderWindow& window, std::vector<Projectile>& projList)
{
	for (short index = 0; index < GC::MAX_PROJECTILES; ++index)
	{
		if (projList[index].active)
		{
			projList[index].Update(game);
			projList[index].Render(window);
		}
	}
}