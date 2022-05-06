#pragma once
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include "SFML/Graphics.hpp"

//Structs

//Angle from clockwise NESW axis, calculated in radians
//Notes: Can be converted to degrees for SFML, be wary of conversion usage
struct DirectionalAngle
{
	float angle = 0.f; //Angle in radians
	char direction = 0; //Direction of the angle, default is North
};

//Dimensions in 2D as int
struct Dim2Di
{
	int x = 0;
	int y = 0;
};

//Dimensions in 2D as float
struct Dim2Df
{
	float x = 0.f;
	float y = 0.f;
};

//Tile used for tilemap
struct Tile
{
	char ID = 0; //Could be removed? Or kept for readability?
	char name[32] = "";
	sf::IntRect rect{};
};

//Data used for room generation
struct RoomData
{
	char type = 0;
	char tilemap[32][32] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
};

//Data used for animations
struct AnimationData
{
	char startFrame = 0; //Frame that the animation starts from
	char endFrame = 0; //Frame that the animation ends on
	float frameChange = 0.f; //How frequent the frames will change, in seconds
};

//Data for current game session
struct GameData
{
	//Window and camera
	Dim2Di screenResolution = { 0, 0 }; //Resolution of the player's screen
	float scaling = 0.f; //Sprite scaling, varies based on the screen
	sf::IntRect mapRect = { 0, 0, 0, 0 }; //Position and area of the map texture being drawn to the screen, in pixels
	sf::IntRect cameraRect = { 0, 0, 0, 0 }; //Global position and area of the camera, in pixels
	sf::View camera{}; //View for the window, zoomed in so that the map and sprites can be drawn in pixels

	//States
	char gameState = 0; //Current game state
	char input = 0; //Keyboard or controller

	//Textures
	sf::Texture spritesheet{}; //Spritesheet, not including menu UI
	sf::Texture mapTexture{}; //Environment texture for this level's map

	//Additional textures and images only for updating/drawing
	sf::Image spritesheetImg{}; //Spritesheet in Image format, for texture.loadFromImage()
	sf::Texture tileTexture{}; //For drawing tiles to the map
	sf::Texture doorTexture{}; //For drawing doors to the map
	sf::Texture doorOpenTexture{}; //For drawing open doors to the map
	sf::Texture wallsideTexture{}; //For drawing wall sides to the map
	sf::Texture walltopTexture{}; //For drawing wall tops to the map
	sf::Texture waterFountainTexture{}; //For drawing animated water fountain
	sf::Texture lavaFountainTexture{}; //For drawing animated lava fountain
	sf::Texture playerTexture{}; //For drawing player
	sf::Texture swordTexture{}; //For drawing the sword
	//sf::Texture smallEnemyTexture; //For drawing small enemies
	//sf::Texture mediumEnemyTexture; //For drawing medium enemies
	//sf::Texture largeEnemyTexture; //For drawing large enemies

	//Sprites
	sf::Sprite mapSprite{}; //Sprite for the environment

	//Timers
	float elapsed = 0.f; //Time elapsed since last frame

	//Functions

	//Initializes game session
	void Init(sf::RenderWindow& window);

	//Renders the map onto the camera, based on player position
	void RenderMap(sf::RenderWindow& window, const float& x, const float& y, const Dim2Df& movement);
};

//Global constants
namespace GC
{
	//Screen
	const float SCALE_1080 = 5.f; //View zoom at 1080p
	const float SCALE_1440 = 3.2f; //View zoom at 1440p
	const float SCALE_2160 = 5.f; //View zoom at 2160p
	/*Area of the map that is drawn, centred on the player
	This gives plenty of extra room to allow partially on-screen elements
	to be easily found and drawn onto the screen with minimal excess.*/
	const Dim2Di MAP_DRAW_SIZE = { 464, 290 }; //Area of the map around the player that is drawn
	const short int FRAMERATE = 60; //Game refresh rate

	//Tile
	const short int TILE_SIZE = 16; //Tile size, in pixels
	const Dim2Di DOOR_TILESIZE = { 64, 32 }; //Door size, in pixels
	const short int TILE_NUM = 67; //Total number of tiles
	const short int DOOR_START_NUM = TILE_NUM - 3; //Where the doors start on the tile list
	const Dim2Di FLOOR_RANGE = { 26, 33 }; //Where the floor tiles are in the list
	const Dim2Di WALL_TOP_RANGE = { 1, 3 }; //Where the wall tops are in the list
	const Dim2Di WALL_SIDE_RANGE = { 36, 41 }; //Where the wall sides are in the list
	const Dim2Di WALL_CORNER_RANGE = { 42, 45 }; //Where the wall corners are in the list
	const Dim2Di WALL_INCORNER_RANGE = { 50, 54 }; //Where the wall inside corners are in the list
	const short WALL_SIDE_WIDTH = 5; //Width of a wall side, in pixels
	const int WALL_TOP_HEIGHT = 4; //Width of a wall top, in pixels
	const AnimationData FOUNTAIN_ANIM_LAVA = {0, 2, 0.3f}; //Animation data for lava fountain
	const sf::IntRect FOUNTAIN_ANIM_LAVA_RECT = { 64, 9, 48, 27 }; //Where the animation is on the spritesheet
	const AnimationData FOUNTAIN_ANIM_WATER = { 0, 2, 0.3f }; //Animation data for water fountain
	const sf::IntRect FOUNTAIN_ANIM_WATER_RECT = { 64, 41, 48, 27 }; //Where the animation is on the spritesheet, minus the fountain top
	const sf::IntRect FOUNTAIN_ANIM_TOP_RECT = { 64, 9, 48, 7 }; //Fountain top rect, for drawing onto the water fountain's texture

	//Room
	const short int ROOM_NUM = 3; //Number of rooms
	const short int ROOM_MAX_SIZE = 32; //Max size of a room, in tiles
	const short int ROOM_MAX_DOORS = 4; //Max doors in a room
	const Dim2Di ROOM_TYPE_0 = { 32, 32 };
	const Dim2Di ROOM_TYPE_1 = { 16, 16 };
	const Dim2Di ROOM_TYPE_2 = { 32, 16 };
	const Dim2Di ROOM_TYPE_3 = { 16, 32 };

	//Map
	const short int MAP_SIZE_TILES = 128; //Maximum size of the map, in tiles
	const short int MAP_SIZE_PIXELS = MAP_SIZE_TILES * TILE_SIZE; //Maximum size of map, in pixels

	//Player
	const int PLAYER_ANIM_FRAMES = 9; //Number of frames
	const sf::IntRect KNIGHT_ANIM_RECT = { 128, 106, 144, 22 }; //Where the animation is on the spritesheet
	enum PLAYER_ANIMATION { IDLE = 0, MOVE = 4, DODGE = 8 }; //Animation frame
	const AnimationData PLAYER_ANIM_IDLE = { IDLE, MOVE - 1, 0.12f }; //Idle animation data for the player
	const AnimationData PLAYER_ANIM_MOVE = { MOVE, DODGE - 1, 0.12f }; //Idle animation data for the player
	const sf::IntRect PLAYER_BODY_RECT = { 0, 6, 16, 16 }; //Where the character's body is on the un-scaled sprite
	const Dim2Di PLAYER_BODY_CENTRE = { 8, 14 }; //Where the centre of the character's body is on the un-scaled sprite
	const Dim2Di PLAYER_DIMENSIONS = { 16, 22 }; //Dimensions of the player texture

	//Enemy

	//Weapon
	const sf::IntRect SWORD_RECT = { 323, 26, 10, 21 }; //Where the sword is on the spritesheet
	const float WEAPON_HOVER = 0.5f; //Hover distance from centre, in tiles
	const float WEAPON_HOVER_ROTATION = 30.f; //Hover rotation, in degrees

	//Attack
	const short MAX_MOTIONS = 2;

	//Tile database
	const Tile TILELIST[TILE_NUM] = {
		{0, "Darkness", {95, 495, 16, 16}},
		{1, "Wall Top Left", {16, 0, 16, 16}},
		{2, "Wall Top Mid", {32, 0, 16, 16}},
		{3, "Wall Top Right", {48, 0, 16, 16} },
		{4, "Wall Left", {16, 16, 16, 16}},
		{5, "Wall Mid", {32, 16, 16, 16}},
		{6, "Wall Right", {48, 16, 16, 16}},
		{7, "Fountain Top", {64, 0, 16, 16}},
		{8, "Lava Fountain Basin", {64, 32, 16, 16}}, //3 frame animation
		{9, "Lava Fountain Mid", {64, 16, 16, 16}}, //3 frame animation
		{10, "Water Fountain Basin", {64, 64, 16, 16}}, //3 frame animation
		{11, "Water Fountain Mid", {64, 48, 16, 16}}, //3 frame animation
		{12, "Wall Hole 1", {48, 32, 16, 16}},
		{13, "Wall Hole 2", {48, 48, 16, 16}},
		{14, "Wall Banner Blue", {32, 32, 16, 16}},
		{15, "Wall Banner Green", {16, 48, 16, 16}},
		{16, "Wall Banner Yellow", {32, 48, 16, 16}},
		{17, "Wall Banner Red", {16, 32, 16, 16}},
		{18, "Column Top", {80, 80, 16, 16}},
		{19, "Column Mid", {80, 96, 16, 16}},
		{20, "Column Base", {80, 112, 16, 16}},
		{21, "Wall Column Top", {96, 80, 16, 16}},
		{22, "Wall Column Mid", {96, 96, 16, 16}},
		{23, "Wall Column Base", {96, 112, 16, 16}},
		{24, "Wall Goo", {64, 80, 16, 16}},
		{25, "Wall Goo Floor", {64, 96, 16, 16}},
		{26, "Floor 1", {16, 64, 16, 16}},
		{27, "Floor 2", {32, 64, 16, 16}},
		{28, "Floor 3", {48, 64, 16, 16}},
		{29, "Floor 4", {16, 80, 16, 16}},
		{30, "Floor 5", {32, 80, 16, 16}},
		{31, "Floor 6", {48, 80, 16, 16}},
		{32, "Floor 7", {16, 96, 16, 16}},
		{33, "Floor 8", {32, 96, 16, 16}},
		{34, "Floor Spikes", {16, 176, 16, 16}}, //4 frame animation
		{35, "Floor Ladder", {48, 96, 16, 16}},
		{36, "Wall Side Top Right", {0, 112, 16, 16}},
		{37, "Wall Side Top Left", {16, 112, 16, 16}},
		{38, "Wall Side Mid Right", {0, 128, 16, 16}},
		{39, "Wall Side Mid Left", {16, 128, 16, 16}},
		{40, "Wall Side Front Right", {0, 144, 16, 16}},
		{41, "Wall Side Front Left", {16, 144, 16, 16}},
		{42, "Wall Corner Top Left", {32, 112, 16, 16}},
		{43, "Wall Corner Top Right", {48, 112, 16, 16}},
		{44, "Wall Corner Bottom Left", {32, 144, 16, 16}},
		{45, "Wall Corner Bottom Right", {48, 144, 16, 16}},
		{46, "Wall Corner Left", {32, 128, 16, 16}},
		{47, "Wall Corner Right", {48, 128, 16, 16}},
		{48, "Wall Corner Front Left", {32, 160, 16, 16}},
		{49, "Wall Corner Front Right", {48, 160, 16, 16}},
		{50, "Wall In Corner L Top Left", {80, 128, 16, 16}},
		{51, "Wall In Corner L Top Right", {64, 128, 16, 16}},
		{52, "Wall In Corner T Top Left", {80, 160, 16, 16}},
		{53, "Wall In Corner T Top Right", {64, 160, 16, 16}},
		{54, "Wall In Corner Mid Left", {80, 144, 16, 16}},
		{55, "Wall In Corner Mid Right", {64, 144, 16, 16}},
		{56, "Hole", {96, 144, 16, 16}},
		{57, "Stairs", {80, 176, 16, 16}},
		{58, "Edge", {96, 128, 16, 16}},
		{59, "Wall Column Top w/ Floor", {0, 80, 16, 16}},
		{60, "Fountain Top w/ Floor", {0, 96, 16, 16}},
		{61, "Blank", {0, 426, 16, 16}},
		{62, "Blank", {0, 426, 16, 16}},
		{63, "Enemy Spawner", {0, 64, 16, 16}},
		{64, "Door Up", {16, 208, 64, 32}},
		{65, "Door Down", {16, 240, 64, 32}},
		{66, "Door Open", {80, 208, 32, 32}}
	}; //{60, "", {}},

	//Tilemap database
	const RoomData ROOM_LIST[ROOM_NUM] = {
		{1, {{42, 02, 07, 21, 64, 64, 64, 64, 21, 02, 02, 02, 02, 07, 02, 43},
			{46, 12, 11, 22, 64, 64, 64, 64, 22, 05, 05, 13, 05, 9, 05, 47},
			{39, 26, 10, 23, 26, 26, 26, 26, 23, 26, 26, 26, 26, 8, 26, 38},
			{39, 26, 26, 26, 26, 26, 30, 26, 32, 33, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 27, 26, 26, 26, 26, 26, 26, 26, 28, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 28, 26, 26, 26, 26, 26, 27, 26, 26, 38},
			{39, 30, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 31, 29, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 26, 26, 27, 26, 26, 26, 26, 26, 38},
			{39, 26, 28, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 32, 33, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 31, 29, 26, 26, 28, 26, 26, 26, 26, 38},
			{44, 02, 02, 02, 02, 02, 02, 59, 65, 65, 65, 65, 59, 02, 02, 45},
			{48, 05, 05, 05, 13, 05, 05, 22, 65, 65, 65, 65, 22, 12, 05, 49}}},
		{1, {{42, 02, 02, 02, 02, 02, 02, 21, 64, 64, 64, 64, 21, 02, 02, 43},
			{46, 13, 05, 05, 05, 24, 05, 22, 64, 64, 64, 64, 22, 05, 13, 47},
			{39, 26, 27, 26, 26, 25, 26, 23, 26, 31, 29, 26, 23, 26, 26, 38},
			{39, 26, 63, 26, 28, 26, 29, 26, 26, 26, 26, 26, 27, 26, 26, 38},
			{39, 26, 26, 32, 33, 26, 26, 26, 28, 26, 26, 26, 26, 63, 26, 38},
			{39, 26, 26, 26, 26, 26, 27, 26, 26, 26, 30, 31, 29, 28, 26, 38},
			{39, 26, 30, 26, 28, 26, 26, 26, 26, 26, 26, 32, 33, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 63, 26, 28, 26, 26, 30, 26, 26, 38},
			{39, 26, 28, 63, 26, 26, 30, 26, 26, 26, 26, 27, 63, 26, 26, 38},
			{39, 26, 27, 26, 26, 32, 33, 26, 26, 26, 33, 26, 26, 26, 30, 38},
			{39, 26, 26, 26, 26, 26, 26, 31, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 32, 26, 26, 26, 26, 27, 26, 26, 26, 26, 28, 26, 26, 38},
			{39, 26, 26, 28, 63, 26, 26, 63, 26, 30, 26, 63, 31, 29, 26, 38},
			{39, 26, 26, 26, 26, 30, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{44, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 45},
			{48, 05, 13, 05, 24, 05, 05, 05, 13, 05, 05, 24, 05, 05, 12, 49}}},
		{1, {{42, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 43},
			{46, 05, 12, 05, 05, 05, 24, 05, 05, 05, 13, 05, 12, 05, 05, 47},
			{39, 26, 26, 26, 26, 26, 25, 26, 26, 26, 26, 26, 26, 30, 26, 38},
			{39, 26, 30, 26, 26, 29, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 28, 26, 26, 26, 26, 27, 26, 29, 26, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 26, 26, 33, 26, 26, 33, 26, 26, 38},
			{39, 26, 31, 26, 26, 27, 26, 30, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 32, 26, 26, 26, 26, 26, 26, 26, 26, 30, 26, 28, 26, 38},
			{39, 26, 26, 26, 26, 26, 26, 26, 26, 26, 31, 29, 26, 26, 26, 38},
			{39, 26, 28, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 26, 26, 26, 26, 30, 26, 26, 26, 26, 28, 26, 27, 26, 26, 38},
			{39, 26, 26, 27, 26, 31, 29, 26, 26, 26, 26, 26, 26, 26, 26, 38},
			{39, 31, 26, 26, 26, 32, 33, 26, 26, 26, 26, 26, 26, 32, 26, 38},
			{44, 02, 02, 59, 65, 65, 65, 65, 59, 02, 02, 02, 02, 02, 02, 45},
			{04, 13, 05, 22, 65, 65, 65, 65, 22, 05, 13, 05, 05, 05, 24, 06},
			{00, 00, 00, 20, 00, 00, 00, 00, 20, 00, 00, 00, 00, 00, 00, 00}}} };

	//Enums
	enum GAME_STATE {MAIN_MENU, PLAYING, WIN, LOSE}; //Current game state
	enum DIRECTIONS { NORTH, EAST, SOUTH, WEST }; //NESW directions
	enum ATTACK_TYPES { ARC, CHARGE, POINT, AREA, PROJECTILE }; //Type of attack
	enum ENTITY_STATES { STATIONARY, MOVING, ATTACKING_STATIONARY, ATTACKING_MOVING, DODGING }; //Current enemy state
	enum ENTITY_WEIGHTS { LIGHT, MEDIUM, HEAVY }; //Weight of entity, reduces knockback
	enum WEAPON_STATES { HOLDING, CHARGING_ARC }; //Current weapon state
	enum PLAYER_INPUT { KEYBOARD, GAMEPAD }; //Player input states
	enum ROOM_TYPES {R32X32, R16X16, R32X16, R16X32}; //Room types
	enum ATTACK_INPUTS {FIRST_ATTACK, SECOND_ATTACK}; //Attack inputs
}

//Updates position of a sprite based on global position
//Returns true if sprite is inside the map area and therefore drawable
bool UpdateSpritePosition(const GameData& game, sf::Sprite& sprite, const sf::FloatRect& globalRect, sf::FloatRect& localRect);