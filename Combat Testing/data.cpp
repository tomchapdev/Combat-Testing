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

	//Vectors
	textures.resize(GC::NUM_TEXTURES);
	collisionMap.resize(GC::MAP_SIZE_TILES);
	for (unsigned char index = 0; index < GC::MAP_SIZE_TILES; ++index)
	{
		collisionMap[index].resize(GC::MAP_SIZE_TILES);
	}

	//Spritesheets
	textures[GC::SPRITESHEET_TEXTURE].create(512, 512);
	textures[GC::SPRITESHEET_TEXTURE].loadFromFile("spritesheet.png");
	spritesheetImg.create(512, 512);
	spritesheetImg.loadFromFile("spritesheet.png");

	//Map & Camera Textures
	textures[GC::MAP_FLOOR_TEXTURE].create(GC::MAP_SIZE_PIXELS, GC::MAP_SIZE_PIXELS);
	textures[GC::TILE_TEXTURE].create(GC::TILE_SIZE, GC::TILE_SIZE);
	textures[GC::DOOR_TEXTURE].create(GC::DOOR_TILESIZE.x, GC::DOOR_TILESIZE.y);
	textures[GC::DOOR_OPEN_TEXTURE].create(GC::DOOR_TILESIZE.y, GC::DOOR_TILESIZE.y); //32 x 32 centre
	textures[GC::DOOR_OPEN_TEXTURE].loadFromImage(spritesheetImg, GC::TILE_LIST[66].rect); //Always the same
	textures[GC::WALL_SIDE_TEXTURE].create(GC::WALL_SIDE_WIDTH, GC::TILE_SIZE);
	textures[GC::WALL_TOP_TEXTURE].create(GC::TILE_SIZE, GC::WALL_TOP_HEIGHT);
	textures[GC::LAVA_FOUNTAIN_TEXTURE].create(GC::FOUNTAIN_ANIM_LAVA_RECT.width, GC::FOUNTAIN_ANIM_LAVA_RECT.height);
	textures[GC::LAVA_FOUNTAIN_TEXTURE].loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_LAVA_RECT);
	textures[GC::WATER_FOUNTAIN_TEXTURE].create(GC::FOUNTAIN_ANIM_WATER_RECT.width, GC::FOUNTAIN_ANIM_WATER_RECT.height);
	textures[GC::WATER_FOUNTAIN_TEXTURE].loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_WATER_RECT);

	//Water fountain texture correction
	sf::Texture fountainTop;
	fountainTop.create(GC::FOUNTAIN_ANIM_TOP_RECT.width, GC::FOUNTAIN_ANIM_TOP_RECT.height);
	fountainTop.loadFromImage(spritesheetImg, GC::FOUNTAIN_ANIM_TOP_RECT);
	textures[GC::WATER_FOUNTAIN_TEXTURE].update(fountainTop);

	//Entity Textures
	textures[GC::PLAYER_TEXTURE].create(GC::KNIGHT_ANIM_RECT.width, GC::KNIGHT_ANIM_RECT.height);
	textures[GC::PLAYER_TEXTURE].loadFromImage(spritesheetImg, GC::KNIGHT_ANIM_RECT);

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
	camera.setCenter(684.f, 684.f);
	window.setView(camera);

	//Sprites
	mapSprite.setTexture(textures[GC::MAP_FLOOR_TEXTURE], true);
}

//Renders the map onto the camera, based on player position
void GameData::RenderMap(sf::RenderWindow& window, const Dim2Df position)
{
	window.draw(mapSprite);
	camera.setCenter(position);
	window.setView(camera);
}