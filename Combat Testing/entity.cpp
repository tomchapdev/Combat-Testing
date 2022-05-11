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
	Dim2Df origin = { globalRect.left + bodyCentre.x,
						globalRect.top + bodyCentre.y };

	//Get vector between points, then calculate directional angle using vector
	facing = CalculateDirectionalAngleFromVector(CalculateVectorBetweenPoints(origin, target));

	movementVector = CalculateVectorOfMagnitude(facing, speed);
}

//Move the entity and weapon
void Entity::Move(const GameData& game)
{
	frameMovementVector.x = (int)roundf(movementVector.x * game.elapsed);
	frameMovementVector.y = (int)roundf(movementVector.y * game.elapsed);

	CheckMapCollision(game);

	globalRect.left += frameMovementVector.x;
	globalRect.top += frameMovementVector.y;
}

//Checks if movement is valid, using rectangle intersections
void Entity::CheckMapCollision(const GameData& game)
{
	//Get movement booleans
	bool movingLeft = false, movingRight = false, movingUp = false, movingDown = false;

	if (frameMovementVector.x < 0)
	{
		movingLeft = true;
	}
	else if (frameMovementVector.x > 0)
	{
		movingRight = true;
	}
	if (frameMovementVector.y < 0)
	{
		movingUp = true;
	}
	else if (frameMovementVector.y > 0)
	{
		movingDown = true;
	}

	//Get collision rectangles, left and right rects based on the direction the entity is moving
	sf::IntRect collisionBox = { (int)floorf(globalRect.left) + collisionRect.left,
		(int)floorf(globalRect.top) + collisionRect.top + collisionRect.height - GC::FEET_COLLISION_HEIGHT,
		collisionRect.width, GC::FEET_COLLISION_HEIGHT };
	sf::IntRect leftTileRect = { 0, 0, 0, 0 };
	sf::IntRect rightTileRect = { 0, 0, 0, 0 };
	sf::IntRect intersection = { 0, 0, 0, 0 };
	Dim2Di leftPoint = { 0, 0 };
	Dim2Di rightPoint = { 0, 0 };
	unsigned char leftTile = 0;
	unsigned char rightTile = 0;
	bool collided = false;

	//C_FREE_MOVEMENT, C_WALL, C_WALL_TOP, C_WALL_SIDE_LEFT, C_WALL_SIDE_RIGHT, C_WALL_TOP_BOTTOM_LEFT, C_WALL_TOP_BOTTOM_RIGHT, C_FOUNTAIN_BASIN,
	//C_COLUMN_TOP, C_COLUMN_BASE, C_CORNER_BOTTOM_LEFT, C_CORNER_BOTTOM_RIGHT
	// 
	//Up - !Wall!, !fountain basin!, !column base!, !wall sides!
	//Down - !Wall!, !wall tops!, !wall corners (same as wall tops)!, !column top!
	//Left - !Wall!, !wall tops!, !wall sides!, !wall corners (same as wall sides)!, !fountain basin!, column base
	//Right - !Wall!, wall tops, wall sides, wall corners (same as wall sides), fountain basin, column base

	if (movingUp)
	{
		leftPoint = { collisionBox.left / GC::TILE_SIZE, (collisionBox.top + frameMovementVector.y) / GC::TILE_SIZE }; //Top left
		leftTile = game.collisionMap[leftPoint.y][leftPoint.x];

		if (leftTile == GC::C_WALL)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE + 1 };
		}
		else if (leftTile == GC::C_WALL_SIDE_LEFT)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
		}
		else if (leftTile == GC::C_FOUNTAIN_BASIN)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::FOUNTAIN_BASIN_HEIGHT };
		}
		else if (leftTile == GC::C_COLUMN_BASE)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::COLUMN_BASE_HEIGHT };
		}


		if (collisionBox.intersects(leftTileRect, intersection))
		{
			collided = true;
			frameMovementVector.y = 0;
		}

		if (!collided)
		{
			rightPoint = { (collisionBox.left + collisionBox.width) / GC::TILE_SIZE, (collisionBox.top + frameMovementVector.y) / GC::TILE_SIZE }; //Top right
			rightTile = game.collisionMap[rightPoint.y][rightPoint.x];

			if (rightTile == GC::C_WALL)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE + 1 };
			}
			else if (rightTile == GC::C_WALL_SIDE_RIGHT)
			{
				rightTileRect = { (rightPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE + 1 };
			}
			else if (rightTile == GC::C_FOUNTAIN_BASIN)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::FOUNTAIN_BASIN_HEIGHT };
			}
			else if (rightTile == GC::C_COLUMN_BASE)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::COLUMN_BASE_HEIGHT };
			}

			if (collisionBox.intersects(rightTileRect, intersection))
			{
				frameMovementVector.y = 0;
			}
		}

		collided = false;
	}
	else if (movingDown)
	{
		leftPoint = { collisionBox.left / GC::TILE_SIZE, (collisionBox.top + collisionBox.height + frameMovementVector.y) / GC::TILE_SIZE }; //Bottom right
		leftTile = game.collisionMap[leftPoint.y][leftPoint.x];

		if (leftTile == GC::C_WALL)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) - 1, GC::TILE_SIZE, GC::TILE_SIZE };
		}
		else if ((leftTile == GC::C_WALL_TOP) || (leftTile == GC::C_CORNER_BOTTOM_RIGHT))
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::WALL_TOP_HEIGHT + 1) };
		}
		else if (leftTile == GC::C_WALL_TOP_BOTTOM_RIGHT)
		{
			leftTileRect = { (leftPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1),
				(GC::WALL_SIDE_WIDTH + 1), (GC::WALL_TOP_HEIGHT + 1) };
		}
		else if (leftTile == GC::C_COLUMN_TOP)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::COLUMN_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::COLUMN_TOP_HEIGHT + 1) };
		}

		if (collisionBox.intersects(leftTileRect, intersection))
		{
			collided = true;
			frameMovementVector.y = 0;
		}
		

		if (!collided)
		{
			rightPoint = { (collisionBox.left + collisionBox.width) / GC::TILE_SIZE, (collisionBox.top + collisionBox.height + frameMovementVector.y) / GC::TILE_SIZE }; //Bottom left
			rightTile = game.collisionMap[rightPoint.y][rightPoint.x];

			if (rightTile == GC::C_WALL)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) - 1, GC::TILE_SIZE, GC::TILE_SIZE };
			}
			else if ((rightTile == GC::C_WALL_TOP) || (rightTile == GC::C_CORNER_BOTTOM_LEFT))
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::WALL_TOP_HEIGHT + 1) };
			}
			else if (rightTile == GC::C_WALL_TOP_BOTTOM_LEFT)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1),
					(GC::WALL_SIDE_WIDTH + 1), (GC::WALL_TOP_HEIGHT + 1) };
			}
			else if (rightTile == GC::C_COLUMN_TOP)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::COLUMN_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::COLUMN_TOP_HEIGHT + 1) };
			}

			if (collisionBox.intersects(rightTileRect, intersection))
			{
				frameMovementVector.y = 0;
			}
		}

		collided = false;
	}

	//Reset collision rects
	leftTileRect = { 0, 0, 0, 0 };
	rightTileRect = { 0, 0, 0, 0 };

	if (movingLeft)
	{
		leftPoint = { (collisionBox.left + frameMovementVector.x) / GC::TILE_SIZE, (collisionBox.top + collisionBox.height - 1) / GC::TILE_SIZE }; //Bottom left
		leftTile = game.collisionMap[leftPoint.y][leftPoint.x];

		if (leftTile == GC::C_WALL)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE };
		}
		else if ((leftTile == GC::C_WALL_TOP) || (leftTile == GC::C_CORNER_BOTTOM_RIGHT))
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::WALL_TOP_HEIGHT + 1) };
		}
		else if (leftTile == GC::C_WALL_SIDE_LEFT)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
		}
		else if (leftTile == GC::C_WALL_SIDE_RIGHT)
		{
			leftTileRect = { (leftPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), leftPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
		}
		else if (leftTile == GC::C_WALL_TOP_BOTTOM_LEFT)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1),
				(GC::WALL_SIDE_WIDTH + 1), (GC::WALL_TOP_HEIGHT + 1) };
		}
		else if (leftTile == GC::C_COLUMN_TOP)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, (leftPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::COLUMN_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::COLUMN_TOP_HEIGHT + 1) };
		}

		//More to go here soon

		if (collisionBox.intersects(leftTileRect, intersection))
		{
			collided = true;
			frameMovementVector.x = 0;
		}

		if (!collided)
		{
			rightPoint = { (collisionBox.left + frameMovementVector.x) / GC::TILE_SIZE, (collisionBox.top + 1) / GC::TILE_SIZE }; //Top left
			rightTile = game.collisionMap[rightPoint.y][rightPoint.x];

			if (rightTile == GC::C_WALL)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE - 1 };
			}
			else if (rightTile == GC::C_WALL_SIDE_LEFT)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
			}
			else if (rightTile == GC::C_WALL_SIDE_RIGHT)
			{
				rightTileRect = { (rightPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), rightPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
			}
			else if (rightTile == GC::C_FOUNTAIN_BASIN)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::FOUNTAIN_BASIN_HEIGHT - 1 };
			}
			else if (rightTile == GC::C_COLUMN_BASE)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::COLUMN_BASE_HEIGHT + 1 };
			}

			if (collisionBox.intersects(rightTileRect, intersection))
			{
				frameMovementVector.x = 0;
			}
		}

		collided = false;
	}
	else if (movingRight)
	{
		leftPoint = { (collisionBox.left + collisionBox.width + frameMovementVector.x) / GC::TILE_SIZE, (collisionBox.top + 1) / GC::TILE_SIZE }; //Top right
		leftTile = game.collisionMap[leftPoint.y][leftPoint.x];

		if (leftTile == GC::C_WALL)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE - 1 };
		}
		else if (leftTile == GC::C_WALL_SIDE_LEFT)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
		}
		else if (leftTile == GC::C_WALL_SIDE_RIGHT)
		{
			leftTileRect = { (leftPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), leftPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
		}
		else if (leftTile == GC::C_FOUNTAIN_BASIN)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::FOUNTAIN_BASIN_HEIGHT - 1 };
		}
		else if (leftTile == GC::C_COLUMN_BASE)
		{
			leftTileRect = { leftPoint.x * GC::TILE_SIZE, leftPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::COLUMN_BASE_HEIGHT + 1 };
		}
		//More to go here soon

		if (collisionBox.intersects(leftTileRect, intersection))
		{
			collided = true;
			frameMovementVector.x = 0;
		}

		if (!collided)
		{
			rightPoint = { (collisionBox.left + collisionBox.width + frameMovementVector.x) / GC::TILE_SIZE, (collisionBox.top + collisionBox.height - 1) / GC::TILE_SIZE }; //Bottom right
			rightTile = game.collisionMap[rightPoint.y][rightPoint.x];

			if (rightTile == GC::C_WALL)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::TILE_SIZE, GC::TILE_SIZE };
			}
			else if ((rightTile == GC::C_WALL_TOP) || (leftTile == GC::C_CORNER_BOTTOM_RIGHT))
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::WALL_TOP_HEIGHT + 1) };
			}
			else if (rightTile == GC::C_WALL_SIDE_LEFT)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, rightPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
			}
			else if (rightTile == GC::C_WALL_SIDE_RIGHT)
			{
				rightTileRect = { (rightPoint.x * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_SIDE_WIDTH + 1), rightPoint.y * GC::TILE_SIZE, GC::WALL_SIDE_WIDTH + 1, GC::TILE_SIZE };
			}
			else if (rightTile == GC::C_WALL_TOP_BOTTOM_LEFT)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::WALL_TOP_HEIGHT + 1),
					(GC::WALL_SIDE_WIDTH + 1), (GC::WALL_TOP_HEIGHT + 1) };
			}
			else if (rightTile == GC::C_COLUMN_TOP)
			{
				rightTileRect = { rightPoint.x * GC::TILE_SIZE, (rightPoint.y * GC::TILE_SIZE) + GC::TILE_SIZE - (GC::COLUMN_TOP_HEIGHT + 1), GC::TILE_SIZE, (GC::COLUMN_TOP_HEIGHT + 1) };
			}

			if (collisionBox.intersects(rightTileRect, intersection))
			{
				frameMovementVector.x = 0;
			}
		}

		collided = false;
	}
}

//Render the entity if it's on the rendered map area
void Entity::Render(sf::RenderWindow& window, const GameData& game)
{
	//Check if in rendered area
	nearPlayer = UpdateSpritePosition(game, sprite, globalRect, localRect);

	/*if (nearPlayer && weapon.visible && !weapon.attacking)
	{
		UpdateSpritePosition(game, weapon.sprite, weapon.globalRect, weapon.localRect);
	}*/

	if (nearPlayer || isPlayer)
	{
		anim.UpdateAnimation(sprite, game.elapsed);

		//Flip and move sprite based on facing
		if ((facing.direction == GC::NORTH) || (facing.direction == GC::EAST))
		{
			if (!facingRight)
			{
				sprite.setScale(1.f, 1.f);
				bodyCentre.x = globalRect.width - bodyCentre.x;
				facingRight = true;
			}
		}
		else
		{
			if (facingRight)
			{
				sprite.setScale(-1.f, 1.f);
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
void Entity::UpdateAttacks(const GameData& game, std::vector<Projectile>& proj)
{
	if (weapon.attack0.active)
	{
		weapon.attack0.UpdateAttack(game, proj);
	}
	else if (weapon.hasTwoAttacks && weapon.attack1.active)
	{
		weapon.attack1.UpdateAttack(game, proj);
	}
	else
	{
		weapon.attacking = false;
		canAttack = true;
	}
}

//Update the weapon's state
void Entity::UpdateWeapon(const GameData& game, std::vector<Projectile>& proj)
{
	float x = 0.f, y = 0.f;

	if (weapon.attacking)
	{
		UpdateAttacks(game, proj);

		//Weapon movement correction
		if (moving && weapon.visible)
		{
			x -= frameMovementVector.x;
			y -= frameMovementVector.y;
		}
	}
	else
	{
		weapon.UpdateHoldPosition(game, facing, localRect);
		weapon.UpdateHoldRotation(facing);
	}

	//Weapon bobbing along to sprite's animation, this needs replacing with a more entity-agnostic method
	if (weapon.visible)
	{
		if (anim.currentFrame == 5)
		{
			y -= 1;
		}
		else if (anim.currentFrame == 7)
		{
			y += 1;
		}
		else if (anim.currentFrame < 4 && anim.currentFrame != 0)
		{
			y -= (anim.currentFrame % 2) - 2;
		}
	}

	weapon.sprite.move({ x, y });
}

void Entity::TakeDamage()
{

}