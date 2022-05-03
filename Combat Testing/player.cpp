#include "player.h"
#include "maths.h"

//Functions

//Initializes player
void Player::Init(GameData& game)
{
	//Positioning
	entity.bodyCentre.x = (float)GC::PLAYER_BODY_CENTRE.x * GC::SPRITE_SCALE;
	entity.bodyCentre.y = (float)GC::PLAYER_BODY_CENTRE.y * GC::SPRITE_SCALE;
	entity.localRect = { (float)((game.mapRect.width / 2 * GC::SPRITE_SCALE) - entity.bodyCentre.x),
							(float)((game.mapRect.height / 2 * GC::SPRITE_SCALE) - entity.bodyCentre.y),
							(float)GC::PLAYER_DIMENSIONS.x, (float)GC::PLAYER_DIMENSIONS.y };

	//Entity stats
	entity.isPlayer = true;
	entity.health = 10;
	entity.speed = 160.f * GC::SPRITE_SCALE;
	entity.globalRect = { 684.f * GC::SPRITE_SCALE, 684.f * GC::SPRITE_SCALE, (float)GC::PLAYER_DIMENSIONS.x * GC::SPRITE_SCALE, (float)GC::PLAYER_DIMENSIONS.y * GC::SPRITE_SCALE };
	entity.anim.data = &GC::PLAYER_ANIM_IDLE;

	//Weapon stats
	entity.weapon.active = true;
	entity.weapon.visible = true;
	entity.weapon.holdDistance = GC::WEAPON_HOVER * GC::TILE_SIZE * GC::SPRITE_SCALE;
	entity.weapon.holdOrigin = entity.bodyCentre;
	entity.weapon.hasTwoAttacks = true;
	entity.weapon.attack0 = GC::NORMAL_SWING_ATTACK;
	entity.weapon.attack1 = GC::HEAVY_SWING_ATTACK;
	//float scale = 2.f;
	//entity.weapon.sprite.setScale(scale, scale);
	//entity.attackSpeed = 2;

	//SFML
	entity.texture = &game.playerTexture;
	entity.sprite.setTexture(*entity.texture);
	entity.sprite.setTextureRect({0, 0, 16, 22});
	entity.weapon.sprite.setOrigin({(float)GC::PLAYER_BODY_CENTRE.x, (float)GC::PLAYER_BODY_CENTRE.y });
	entity.sprite.setPosition(entity.localRect.left, entity.localRect.top);
	entity.sprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);

	entity.weapon.texture = &game.swordTexture;
	entity.weapon.sprite.setTexture(*entity.weapon.texture);
	entity.weapon.sprite.setOrigin({ 5.f, 18.f });
	entity.weapon.sprite.setPosition(entity.localRect.left, entity.localRect.top);
	entity.weapon.sprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
}

//Get inputs and react
void Player::InputHandling(sf::RenderWindow& window, GameData& game)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		//Exit application
		if ((event.type == sf::Event::Closed) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		//Play inputs
		if (game.input == GC::GAMEPAD)
		{
			GamepadControls(event);
		}
		else
		{
			KeyboardControls(event, game);
		}
	}
}

//Controls for keyboard
void Player::KeyboardControls(const sf::Event& event, GameData& game)
{
	//Movement
	KeyboardMovement(event);

	//Entity facing
	GetMouseAngle(game);

	//Attacks
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (entity.canAttack && !entity.weapon.attacking)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				entity.InitAttack(game, GC::FIRST_ATTACK);
				entity.weapon.attack0.attackRelease = false;
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				entity.InitAttack(game, GC::SECOND_ATTACK);
				entity.weapon.attack1.attackRelease = false;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			entity.weapon.attack0.attackRelease = true;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			entity.weapon.attack1.attackRelease = true;
		}
	}

	//Attack swapping for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		entity.weapon.attack0 = GC::NORMAL_SWING_ATTACK;
		entity.weapon.attack1 = GC::HEAVY_SWING_ATTACK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		entity.weapon.attack0 = GC::NORMAL_THRUST_ATTACK;
		entity.weapon.attack1 = GC::HEAVY_THRUST_ATTACK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		entity.weapon.attack0 = GC::SWORD_OF_DOOM_ATTACK;
	}
	
	//Speed testing
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Num1)
		{
			entity.speed -= 10.f;
		}
		else if (event.key.code == sf::Keyboard::Num2)
		{
			entity.speed += 10.f;
		}
	}
}

//Find movement vector based on isKeyPressed booleans
void Player::KeyboardMovement(const sf::Event& event)
{
	//Movement booleans
	bool movingLeft = false; //Player is moving left
	bool movingRight = false; //Player is moving right
	bool movingUp = false; //Player is moving up
	bool movingDown = false; //Player is moving down

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movingLeft = true;
		//std::cout << "MovingLeft = true" << std::endl;
	}
	else
	{
		movingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movingRight = true;
		//std::cout << "MovingRight = true" << std::endl;
	}
	else
	{
		movingRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movingUp = true;
		//std::cout << "MovingUp = true" << std::endl;
	}
	else
	{
		movingUp = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movingDown = true;
		//std::cout << "MovingDown = true" << std::endl;
	}
	else
	{
		movingDown = false;
	}

	//Opposite directions cancel each other out
	if (movingLeft && movingRight)
	{
		movingLeft = false;
		movingRight = false;
	}
	if (movingUp && movingDown)
	{
		movingUp = false;
		movingDown = false;
	}

	//Update movement bool and animation
	if (movingUp || movingDown || movingLeft || movingRight)
	{
		if (!entity.moving)
		{
			entity.moving = true;
			entity.anim.data = &GC::PLAYER_ANIM_MOVE;
			entity.anim.currentFrame = entity.anim.data->startFrame;
		}
	}
	else
	{
		if (entity.moving)
		{
			entity.moving = false;
			entity.anim.data = &GC::PLAYER_ANIM_IDLE;
			entity.anim.currentFrame = entity.anim.data->startFrame;
		}
	}

	if (entity.moving)
	{
		//Find movement vector
		DirectionalAngle dirAngle;

		if (movingRight && movingUp) //North directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::NORTH;
			entity.movementVector = CalculateMagnitudeVector(dirAngle, entity.speed);
		}
		else if (movingRight && movingDown) //East directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::EAST;
			entity.movementVector = CalculateMagnitudeVector(dirAngle, entity.speed);
		}
		else if (movingLeft && movingDown) //South directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::SOUTH;
			entity.movementVector = CalculateMagnitudeVector(dirAngle, entity.speed);
		}
		else if (movingLeft && movingUp) //West directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::WEST;
			entity.movementVector = CalculateMagnitudeVector(dirAngle, entity.speed);
		}
		else if (movingUp) //North
		{
			entity.movementVector = { GC::ZERO, -entity.speed };
		}
		else if (movingRight) //East
		{
			entity.movementVector = { entity.speed, GC::ZERO };
		}
		else if (movingDown) //South
		{
			entity.movementVector = { GC::ZERO, entity.speed };
		}
		else //West
		{
			entity.movementVector = { -entity.speed, GC::ZERO };
		}
	}
}

//Find the entity's facing angle based on mouse position
void Player::GetMouseAngle(GameData& game)
{
	//Find origin and target points
	Dim2Df centre = { (float)(game.screenResolution.x / 2), (float)(game.screenResolution.y / 2)};
	Dim2Df mousePosition = { (float)mouse.getPosition().x, (float)mouse.getPosition().y };

	//Get vector between points, then calculate directional angle using vector
	entity.facing = CalculateDirectionalAngleFromVector( CalculateVectorBetweenPoints(centre, mousePosition) );
}

//Controls for gamepad
void Player::GamepadControls(const sf::Event& event)
{

}