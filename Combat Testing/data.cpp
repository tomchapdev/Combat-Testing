#include "data.h"

//Functions

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
	cameraResolution.x = (int)(screenResolution.x / scaling);
	cameraResolution.y = (int)(screenResolution.y / scaling);

	camera.setSize((float)cameraResolution.x, (float)cameraResolution.y);
	camera.setCenter((float)(GC::MAP_DRAW_SIZE.x / 2 * GC::SPRITE_SCALE), (float)(GC::MAP_DRAW_SIZE.y / 2 * GC::SPRITE_SCALE));
	window.setView(camera);

	//Sprites
	mapSprite.setTexture(mapTexture);
	mapSprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
}

//Updates which part of the map is shown, based on the player's x and y coordinates
void GameData::UpdateMapVisibility(const int& x, const int& y)
{
	//Map
	int halfWidth = GC::MAP_DRAW_SIZE.x / 2, halfHeight = GC::MAP_DRAW_SIZE.y / 2;
	bool moveCamera = false;

	//X axis
	if (x <= halfWidth)
	{
		mapRect.left = 0;
		mapRect.width = x + halfWidth;
		mapOffset.x = GC::MAP_DRAW_SIZE.x - mapRect.width;
	}
	else if ((x + halfWidth) >= GC::MAP_SIZE_PIXELS)
	{
		mapRect.left = x - halfWidth;
		mapRect.width = GC::MAP_SIZE_PIXELS - x - halfWidth;
		mapOffset.x = 0;
	}
	else
	{
		mapRect.left = x - halfWidth;
		mapRect.width = GC::MAP_DRAW_SIZE.x;
		mapOffset.x = 0;
	}

	//Y axis
	if (y <= halfHeight)
	{
		mapRect.top = 0;
		mapRect.height = y + halfHeight;
		mapOffset.y = GC::MAP_DRAW_SIZE.y - mapRect.height;
	}
	else if ((y + halfHeight) >= GC::MAP_SIZE_PIXELS)
	{
		mapRect.top = y - halfHeight;
		mapRect.height = GC::MAP_SIZE_PIXELS - y - halfHeight;
		mapOffset.y = 0;
	}
	else
	{
		mapRect.top = y - halfHeight;
		mapRect.height = GC::MAP_DRAW_SIZE.y;
		mapOffset.y = 0;
	}

	//Map sprite
	mapSprite.setTextureRect(mapRect);
	mapSprite.setPosition((float)mapOffset.x, (float)mapOffset.y);

	mapRectScaled.left = mapRect.left * GC::SPRITE_SCALE;
	mapRectScaled.top = mapRect.top * GC::SPRITE_SCALE;
	mapRectScaled.width = mapRect.width * GC::SPRITE_SCALE;
	mapRectScaled.height = mapRect.height * GC::SPRITE_SCALE;

	//camera.setCenter((float)(GC::MAP_DRAW_SIZE.x / 2), (float)(GC::MAP_DRAW_SIZE.y / 2));
}

//Renders the map
void GameData::RenderMap(sf::RenderWindow& window, const int& x, const int& y)
{
	UpdateMapVisibility(x, y);
	window.draw(mapSprite);
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