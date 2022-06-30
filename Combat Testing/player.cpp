#include "player.h"
#include "maths.h"

//Functions

//Initializes player
void Player::Init(GameData& game)
{
	//Positioning
	entity.bodyCentre = Dim2Df(GC::PLAYER_BODY_CENTRE); //DUPLICATED INFORMATION, NOT NECESSARY

	//Entity stats
	entity.isPlayer = true;
	entity.health = 10;
	entity.speed = 130.f;
	entity.collisionRect = GC::PLAYER_BODY_RECT;
	entity.anim.data = &GC::PLAYER_ANIM_IDLE;

	//Weapon stats
	entity.weapon.active = true;
	entity.weapon.visible = true;
	entity.weapon.holdDistance = GC::WEAPON_HOVER * GC::TILE_SIZE;
	entity.weapon.hasTwoAttacks = true;
	entity.weapon.attack0 = GC::NORMAL_SWING_ATTACK;
	entity.weapon.attack1 = GC::HEAVY_SWING_ATTACK;
	//entity.weapon.Init(0); //Needs altering when I add weapon templates

	//SFML
	entity.texture = &game.textures[GC::PLAYER_TEXTURE];
	entity.sprite.setTexture(*entity.texture);
	entity.sprite.setTextureRect({ 0, 0, 16, 22 });
	entity.sprite.setOrigin(entity.bodyCentre);
	entity.sprite.setPosition(684.f, 684.f);

	entity.weapon.texture = &game.textures[GC::SPRITESHEET_TEXTURE];
	entity.weapon.sprite.setTexture(*entity.weapon.texture);
	entity.weapon.sprite.setTextureRect(GC::SWORD_RECT);
	entity.weapon.sprite.setOrigin(GC::SWORD_ORIGIN);
	entity.weapon.sprite.setPosition(684.f, 684.f);
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		entity.weapon.attack0 = GC::NORMAL_STRAIGHT_THROW_ATTACK;
		entity.weapon.attack1 = GC::NORMAL_SPINNING_THROW_ATTACK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//entity.weapon.active = true;
		entity.weapon.visible = true;
		entity.weapon.entityIsWeapon = false;
		entity.weapon.holdDistance = GC::WEAPON_HOVER * GC::TILE_SIZE;
		entity.weapon.hasTwoAttacks = true;
		entity.weapon.attack0 = GC::NORMAL_SWING_ATTACK;
		entity.weapon.attack1 = GC::HEAVY_SWING_ATTACK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//entity.weapon.active = true;
		entity.weapon.visible = false;
		entity.weapon.entityIsWeapon = true;
		entity.weapon.holdDistance = 0.f;
		entity.weapon.hasTwoAttacks = true;
		entity.weapon.attack0 = GC::HORN_STAB;
		entity.weapon.attack1 = GC::CHARGE;
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

	//entity.moving = true;
	if (entity.moving)
	{
		//Find movement vector
		DirectionalAngle dirAngle;

		if (movingRight && movingUp) //North directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::NORTH;
			entity.movementVector = CalculateVectorOfMagnitude(dirAngle, entity.speed);
		}
		else if (movingRight && movingDown) //East directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::EAST;
			entity.movementVector = CalculateVectorOfMagnitude(dirAngle, entity.speed);
		}
		else if (movingLeft && movingDown) //South directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::SOUTH;
			entity.movementVector = CalculateVectorOfMagnitude(dirAngle, entity.speed);
		}
		else if (movingLeft && movingUp) //West directional angle
		{
			dirAngle.angle = GC::RADS_45DEGREES;
			dirAngle.direction = GC::WEST;
			entity.movementVector = CalculateVectorOfMagnitude(dirAngle, entity.speed);
		}
		else if (movingUp) //North
		{
			entity.movementVector = { 0.f, -entity.speed };
		}
		else if (movingRight) //East
		{
			entity.movementVector = { entity.speed, 0.f };
		}
		else if (movingDown) //South
		{
			entity.movementVector = { 0.f, entity.speed };
		}
		else //West
		{
			entity.movementVector = { -entity.speed, 0.f };
		}
	}
}

//Find the entity's facing angle based on mouse position
void Player::GetMouseAngle(GameData& game)
{
	//Find origin and target points
	Dim2Df centre = { (float)(game.screenResolution.x / 2), (float)(game.screenResolution.y / 2) };
	Dim2Df mousePosition = { (float)mouse.getPosition().x, (float)mouse.getPosition().y };

	//Get vector between points, then calculate directional angle using vector
	entity.facing = CalculateDirectionalAngleFromVector(CalculateVectorBetweenPoints(centre, mousePosition));
}

//Controls for gamepad
void Player::GamepadControls(const sf::Event& event)
{

}