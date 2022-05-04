#include "data.h"

//Functions

//Initializes game session
void GameData::Init(sf::RenderWindow& window)
{
	//Resolution
	screenResolution.x = sf::VideoMode::getDesktopMode().width;
	screenResolution.y = sf::VideoMode::getDesktopMode().height;

	//Window
	window.create(sf::VideoMode(screenResolution.x, screenResolution.y), "DD Combat Testing", sf::Style::Fullscreen);

	//Spritesheets
	spritesheet.create(512, 512);
	spritesheet.loadFromFile("spritesheet.png");
	spritesheetImg.create(512, 512);
	spritesheetImg.loadFromFile("spritesheet.png");


	//Map
	mapRect.width = GC::MAP_DRAW_SIZE.x;
	mapRect.height = GC::MAP_DRAW_SIZE.y;

	//Map & Camera Textures
	mapTexture.create(GC::MAP_SIZE_PIXELS, GC::MAP_SIZE_PIXELS);
	tileTexture.create(GC::TILE_SIZE, GC::TILE_SIZE);
	doorTexture.create(GC::DOOR_TILESIZE.x, GC::DOOR_TILESIZE.y);
	doorOpenTexture.create(GC::DOOR_TILESIZE.y, GC::DOOR_TILESIZE.y); //32 x 32 centre
	doorOpenTexture.loadFromImage(spritesheetImg, GC::TILELIST[66].rect); //Always the same
	wallsideTexture.create(GC::WALL_SIDE_WIDTH, GC::TILE_SIZE);
	walltopTexture.create(GC::TILE_SIZE, GC::WALL_TOP_HEIGHT);
	lavaFountainTexture.create(GC::FOUNTAIN_ANIM_LAVA_RECT.width, GC::FOUNTAIN_ANIM_LAVA_RECT.height);
	lavaFountainTexture.loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_LAVA_RECT);
	waterFountainTexture.create(GC::FOUNTAIN_ANIM_WATER_RECT.width, GC::FOUNTAIN_ANIM_WATER_RECT.height);
	waterFountainTexture.loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_WATER_RECT);
	sf::Texture fountainTop;
	fountainTop.create(GC::FOUNTAIN_ANIM_TOP_RECT.width, GC::FOUNTAIN_ANIM_TOP_RECT.height);
	fountainTop.loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_TOP_RECT);
	waterFountainTexture.update(fountainTop);

	//Entity Textures
	playerTexture.create(GC::KNIGHT_ANIM_RECT.width, GC::KNIGHT_ANIM_RECT.height);
	playerTexture.loadFromImage(spritesheetImg, GC::KNIGHT_ANIM_RECT);
	swordTexture.create(GC::SWORD_RECT.width, GC::SWORD_RECT.height);
	swordTexture.loadFromImage(spritesheetImg, GC::SWORD_RECT);

	//Scaling
	if ((screenResolution.x == 3840) && (screenResolution.y == 2160))
	{
		scaling = GC::SCALE_2160;
	}
	else if ((screenResolution.x == 2560) && (screenResolution.y == 1440))
	{
		scaling = GC::SCALE_1440;
	}
	else if ((screenResolution.x == 1920) && (screenResolution.y == 1080))
	{
		scaling = GC::SCALE_1080;
	}

	//Camera
	cameraRect.width = (int)(screenResolution.x / scaling);
	cameraRect.height = (int)(screenResolution.y / scaling);

	camera.setSize((float)cameraRect.width, (float)cameraRect.height);
	camera.setCenter((float)(GC::MAP_DRAW_SIZE.x / 2 * GC::SPRITE_SCALE), (float)(GC::MAP_DRAW_SIZE.y / 2 * GC::SPRITE_SCALE));
	window.setView(camera);

	//Sprites
	mapSprite.setTexture(mapTexture);
	mapSprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
}

//Renders the map onto the camera, based on player position
void GameData::RenderMap(sf::RenderWindow& window, const float& x, const float& y, const Dim2Df& movement)
{
	int halfWidth = GC::MAP_DRAW_SIZE.x / 2, halfHeight = GC::MAP_DRAW_SIZE.y / 2, xPixel = (int)roundf(x / GC::SPRITE_SCALE), yPixel = (int)roundf(y / GC::SPRITE_SCALE);
	bool moveCameraLeft = false, moveCameraRight = false, moveCameraUp = false, moveCameraDown = false;

	//Map
	//X axis
	if (xPixel <= halfWidth)
	{
		mapRect.left = 0;
		moveCameraRight = true;
	}
	else if ((xPixel + halfWidth) >= GC::MAP_SIZE_PIXELS)
	{
		mapRect.left = GC::MAP_SIZE_PIXELS - GC::MAP_DRAW_SIZE.x;
		moveCameraLeft = true;
	}
	else
	{
		mapRect.left = xPixel - halfWidth;
	}

	//Y axis
	if (yPixel <= halfHeight)
	{
		mapRect.top = 0;
		moveCameraDown = true;
	}
	else if ((yPixel + halfHeight) >= GC::MAP_SIZE_PIXELS)
	{
		mapRect.top = GC::MAP_SIZE_PIXELS - GC::MAP_DRAW_SIZE.y;
		moveCameraUp = true;
	}
	else
	{
		mapRect.top = yPixel - halfHeight;
	}

	//Map sprite
	mapSprite.setTextureRect(mapRect);
	mapSprite.setPosition((float)mapOffset.x, (float)mapOffset.y);
	window.draw(mapSprite);

	mapRectScaled.left = mapRect.left * GC::SPRITE_SCALE;
	mapRectScaled.top = mapRect.top * GC::SPRITE_SCALE;
	mapRectScaled.width = mapRect.width * GC::SPRITE_SCALE;
	mapRectScaled.height = mapRect.height * GC::SPRITE_SCALE;

	//Camera
	halfWidth = cameraRect.width / 2, halfHeight = cameraRect.height / 2;
	float centreX = x - mapRectScaled.left - 1.f, centreY = y - mapRectScaled.top - 1.f;

	if (moveCameraLeft || moveCameraRight || moveCameraUp || moveCameraDown)
	{
		//Move camera to
		if (moveCameraLeft)
		{
			centreX = (float)(GC::MAP_DRAW_SIZE.x * GC::SPRITE_SCALE) - halfWidth;
		}
		else if (moveCameraRight)
		{
			centreX = (float)halfWidth;
		}

		if (moveCameraUp)
		{
			centreY = (float)(GC::MAP_DRAW_SIZE.y * GC::SPRITE_SCALE) - halfHeight;
		}
		else if (moveCameraDown)
		{
			centreY = (float)halfHeight;
		}
	}
	else
	{

	}
	
	camera.setCenter(centreX, centreY);
}

//Checks if renderable and updates position of the sprite based on global position
//Returns true if sprite is inside the map area and therefore drawable
bool UpdateSpritePosition(const GameData& game, sf::Sprite& sprite, const sf::FloatRect& globalRect, sf::FloatRect& localRect)
{
	bool nearPlayer = false;

	//Check if entity is wholly inside the drawn map area
	if ((globalRect.left > game.mapRectScaled.left) && ((globalRect.left + globalRect.width) < (game.mapRectScaled.left + game.mapRectScaled.width))
		&& (globalRect.top > game.mapRectScaled.top) && ((globalRect.top + globalRect.height) < (game.mapRectScaled.top + game.mapRectScaled.height)))
	{
		nearPlayer = true;
		
		//Set position on rendered map
		localRect = globalRect;
		localRect.left -= game.mapRectScaled.left;
		localRect.top -= game.mapRectScaled.top;
		sprite.setPosition(localRect.left, localRect.top);
	}
	
	return nearPlayer;
}