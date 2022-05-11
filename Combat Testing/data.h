#pragma once
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include "SFML/Graphics.hpp"

using Dim2Df = sf::Vector2f;
using Dim2Di = sf::Vector2i;

//Angle from clockwise NESW axis, calculated in radians
//Notes: Can be converted to degrees for SFML, be wary of conversion usage
struct DirectionalAngle
{
	float angle = 0.f; //Angle in radians
	char direction = 0; //Direction of the angle, default is North
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
	std::vector<std::vector<unsigned char>> tilemap = {
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

	//Vectors
	std::vector<sf::Texture> textures; //Vector of all textures
	std::vector<std::vector<char>> collisionMap; //Vector of map collision data

	//Images
	sf::Image spritesheetImg{}; //Spritesheet in Image format, for texture.loadFromImage()

	//Sprites
	sf::Sprite mapSprite{}; //Sprite for the environment

	//Timers
	float elapsed = 0.f; //Time elapsed since last frame

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
	const unsigned char FRAMERATE = 60; //Game refresh rate
	const float APPROX_ELAPSED = 1.f / (float)GC::FRAMERATE; //Approximate elapsed time


	//Textures
	const char MAX_TEXTURES = 10; //Maximum number of textures required to run the game

	//Tile
	const char TILE_SIZE = 16; //Tile size, in pixels
	const Dim2Di DOOR_TILESIZE = { 64, 32 }; //Door size, in pixels
	const unsigned char TILE_NUM = 67; //Total number of tiles
	const unsigned char DOOR_START_NUM = TILE_NUM - 3; //Where the doors start on the tile list
	const Dim2Di WALL_RANGE = { 1, 20 }; //Where the wall tiles are in the list
	const Dim2Di FLOOR_RANGE = { 32, 39 }; //Where the floor tiles are in the list
	const Dim2Di WALL_SIDE_RANGE = { 45, 50 }; //Where the wall sides are in the list
	const Dim2Di WALL_TOP_RANGE = { 51, 57 }; //Where the wall tops are in the list
	const Dim2Di WALL_CORNER_RANGE = { 58, 61 }; //Where the wall corners are in the list
	const char WALL_SIDE_WIDTH = 5; //Width of a wall side, in pixels
	const char WALL_TOP_HEIGHT = 4; //Width of a wall top, in pixels
	const AnimationData FOUNTAIN_ANIM_LAVA = { 0, 2, 0.3f }; //Animation data for lava fountain
	const sf::IntRect FOUNTAIN_ANIM_LAVA_RECT = { 64, 9, 48, 27 }; //Where the animation is on the spritesheet
	const AnimationData FOUNTAIN_ANIM_WATER = { 0, 2, 0.3f }; //Animation data for water fountain
	const sf::IntRect FOUNTAIN_ANIM_WATER_RECT = { 64, 41, 48, 27 }; //Where the animation is on the spritesheet, minus the fountain top
	const sf::IntRect FOUNTAIN_ANIM_TOP_RECT = { 64, 9, 48, 7 }; //Fountain top rect, for drawing onto the water fountain's texture
	const char FOUNTAIN_BASIN_HEIGHT = 9;
	const char COLUMN_BASE_HEIGHT = 5;
	const char COLUMN_TOP_HEIGHT = 12;
	const char DOOR_OPEN_WIDTH = 7;
	const std::vector<Tile> TILE_LIST = {
		{0, "Darkness", {95, 495, 16, 16} },
		{1, "Wall Left", {16, 16, 16, 16} },
		{2, "Wall Mid", {32, 16, 16, 16} },
		{3, "Wall Right", {48, 16, 16, 16} },
		{4, "Wall Hole 1", {48, 32, 16, 16} },
		{5, "Wall Hole 2", {48, 48, 16, 16} },
		{6, "Wall Banner Blue", {32, 32, 16, 16} },
		{7, "Wall Banner Green", {16, 48, 16, 16} },
		{8, "Wall Banner Yellow", {32, 48, 16, 16} },
		{9, "Wall Banner Red", {16, 32, 16, 16} },
		{10, "Wall Corner Left", {32, 128, 16, 16} },
		{11, "Wall Corner Right", {48, 128, 16, 16} },
		{12, "Wall Corner Front Left", {32, 160, 16, 16} },
		{13, "Wall Corner Front Right", {48, 160, 16, 16} },
		{14, "Wall In Corner Mid Left", {80, 144, 16, 16} },
		{15, "Wall In Corner Mid Right", {64, 144, 16, 16} },
		{16, "Wall Column Mid", {96, 96, 16, 16} },
		{17, "Column Mid", {80, 96, 16, 16} },
		{18, "Lava Fountain Mid", {64, 16, 16, 16} }, //3 frame animation
		{19, "Water Fountain Mid", {64, 48, 16, 16} }, //3 frame animation
		{20, "Wall Goo", {64, 80, 16, 16} },
		{21, "Column Top", {80, 80, 16, 16} },
		{22, "Wall Column Top", {96, 80, 16, 16} },
		{23, "Fountain Top", {64, 0, 16, 16} },
		{24, "Wall Column Base", {96, 112, 16, 16} },
		{25, "Column Base", {80, 112, 16, 16}},
		{26, "Lava Fountain Basin", {64, 32, 16, 16} }, //3 frame animation
		{27, "Water Fountain Basin", {64, 64, 16, 16} }, //3 frame animation
		{28, "Wall Goo Floor", {64, 96, 16, 16} },
		{29, "Edge", {96, 128, 16, 16} },
		{30, "Wall Column Top w/ Floor", {0, 80, 16, 16} },
		{31, "Fountain Top w/ Floor", {0, 96, 16, 16} },
		{32, "Floor 1", {16, 64, 16, 16} },
		{33, "Floor 2", {32, 64, 16, 16} },
		{34, "Floor 3", {48, 64, 16, 16} },
		{35, "Floor 4", {16, 80, 16, 16} },
		{36, "Floor 5", {32, 80, 16, 16} },
		{37, "Floor 6", {48, 80, 16, 16} },
		{38, "Floor 7", {16, 96, 16, 16} },
		{39, "Floor 8", {32, 96, 16, 16} },
		{40, "Enemy Spawner", {0, 64, 16, 16} },
		{41, "Floor Spikes", {16, 176, 16, 16} }, //4 frame animation
		{42, "Floor Ladder", {48, 96, 16, 16} },
		{43, "Hole", {96, 144, 16, 16} },
		{44, "Stairs", {80, 176, 16, 16} },
		{45, "Wall Side Top Right", {0, 112, 16, 16} },
		{46, "Wall Side Top Left", {16, 112, 16, 16} },
		{47, "Wall Side Mid Right", {0, 128, 16, 16} },
		{48, "Wall Side Front Right", {0, 144, 16, 16} },
		{49, "Wall Side Mid Left", {16, 128, 16, 16} },
		{50, "Wall Side Front Left", {16, 144, 16, 16} },
		{51, "Wall Top Left", {16, 0, 16, 16} },
		{52, "Wall Top Mid", {32, 0, 16, 16} },
		{53, "Wall Top Right", {48, 0, 16, 16} },
		{54, "Wall Corner Top Left", {32, 112, 16, 16} },
		{55, "Wall Corner Top Right", {48, 112, 16, 16} },
		{56, "Wall In Corner T Top Left", {80, 160, 16, 16} },
		{57, "Wall In Corner T Top Right", {64, 160, 16, 16} },
		{58, "Wall Corner Bottom Left", {32, 144, 16, 16} },
		{59, "Wall In Corner L Top Left", {80, 128, 16, 16} },
		{60, "Wall Corner Bottom Right", {48, 144, 16, 16} },
		{61, "Wall In Corner L Top Right", {64, 128, 16, 16}},
		{62, "Blank", {0, 426, 16, 16}},
		{63, "Blank", {0, 426, 16, 16}},
		{64, "Door Up", {16, 208, 64, 32}},
		{65, "Door Down", {16, 240, 64, 32}},
		{66, "Door Open", {80, 208, 32, 32}}
	}; //{60, "", {}},
	enum TILES {
		T_DARKNESS, T_WALL_LEFT, T_WALL_MID, T_WALL_RIGHT, T_WALL_HOLE_1, T_WALL_HOLE_2, T_WALL_BANNER_BLUE, T_WALL_BANNER_GREEN,
		T_WALL_BANNER_YELLOW, T_WALL_BANNER_RED, T_WALL_CORNER_LEFT, T_WALL_CORNER_RIGHT, T_WALL_CORNER_FRONT_LEFT, T_WALL_CORNER_FRONT_RIGHT,
		T_WALL_IN_CORNER_MID_LEFT, T_WALL_IN_CORNER_MID_RIGHT, T_WALL_COLUMN_MID, T_COLUMN_MID, T_LAVA_FOUNTAIN_MID, T_WATER_FOUNTAIN_MID, T_WALL_GOO,
		T_COLUMN_TOP, T_WALL_COLUMN_TOP, T_FOUNTAIN_TOP, T_WALL_COLUMN_BASE, T_COLUMN_BASE, T_LAVA_FOUNTAIN_BASIN, T_WATER_FOUNTAIN_BASIN, T_WALL_GOO_FLOOR,
		T_EDGE, T_WALL_COLUMN_TOP_FLOOR, T_FOUNTAIN_TOP_FLOOR, T_FLOOR_1, T_FLOOR_2, T_FLOOR_3, T_FLOOR_4, T_FLOOR_5, T_FLOOR_6, T_FLOOR_7, T_FLOOR_8,
		T_ENEMY_SPAWNER, T_FLOOR_SPIKES, T_FLOOR_LADDER, T_HOLE, T_STAIRS, T_WALL_SIDE_TOP_RIGHT, T_WALL_SIDE_TOP_LEFT, T_WALL_SIDE_MID_RIGHT,
		T_WALL_SIDE_FRONT_RIGHT, T_WALL_SIDE_MID_LEFT, T_WALL_SIDE_FRONT_LEFT, T_WALL_TOP_LEFT, T_WALL_TOP_MID, T_WALL_TOP_RIGHT, T_WALL_CORNER_TOP_LEFT,
		T_WALL_CORNER_TOP_RIGHT, T_WALL_IN_CORNER_T_TOP_LEFT, T_WALL_IN_CORNER_T_TOP_RIGHT, T_WALL_CORNER_BOTTOM_LEFT, T_WALL_IN_CORNER_L_TOP_LEFT,
		T_WALL_CORNER_BOTTOM_RIGHT, T_WALL_IN_CORNER_L_TOP_RIGHT, T_BLANK_1, T_BLANK_2, T_DOOR_UP, T_DOOR_DOWN
	};


	//Room
	const char ROOM_NUM = 3; //Number of rooms
	const char ROOM_MAX_SIZE = 32; //Max size of a room, in tiles
	const char ROOM_MAX_DOORS = 4; //Max doors in a room
	const Dim2Di ROOM_TYPE_0 = { 32, 32 };
	const Dim2Di ROOM_TYPE_1 = { 16, 16 };
	const Dim2Di ROOM_TYPE_2 = { 32, 16 };
	const Dim2Di ROOM_TYPE_3 = { 16, 32 };
	const std::vector<RoomData> ROOM_LIST = {
		{1, {{54, 23, 52, 22, 64, 64, 64, 64, 22, 52, 52, 52, 23, 52, 52, 55},
			{14, 19, 02, 16, 64, 64, 64, 64, 16, 02, 04, 02, 18, 02, 02, 15},
			{49, 27, 32, 24, 32, 38, 39, 32, 24, 32, 32, 32, 26, 32, 32, 47},
			{49, 32, 32, 32, 32, 32, 32, 32, 36, 32, 32, 32, 33, 32, 32, 47},
			{49, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47},
			{49, 32, 32, 32, 32, 33, 32, 32, 38, 32, 32, 32, 32, 39, 32, 47},
			{49, 32, 32, 36, 32, 32, 32, 32, 32, 32, 37, 35, 32, 32, 32, 47},
			{49, 32, 32, 32, 32, 32, 37, 32, 32, 32, 32, 32, 32, 32, 32, 47},
			{49, 34, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 32, 32, 47},
			{49, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47},
			{49, 32, 32, 32, 37, 35, 32, 32, 32, 39, 32, 32, 32, 32, 32, 47},
			{49, 32, 32, 32, 38, 39, 32, 32, 32, 32, 32, 32, 35, 32, 32, 47},
			{49, 32, 37, 32, 32, 32, 32, 33, 32, 36, 32, 32, 32, 32, 32, 47},
			{59, 52, 52, 52, 52, 52, 52, 30, 65, 65, 65, 65, 30, 52, 52, 61},
			{01, 02, 04, 02, 02, 05, 02, 16, 65, 65, 65, 65, 16, 02, 02, 03},
			{00, 00, 00, 00, 00, 00, 00, 25, 49, 36, 32, 47, 25, 00, 00, 00}}},
		{1, {{54, 23, 52, 23, 52, 23, 52, 22, 64, 64, 64, 64, 22, 52, 23, 55},
			{14, 18, 02, 18, 02, 18, 02, 16, 64, 64, 64, 64, 16, 02, 18, 15},
			{49, 26, 32, 26, 32, 26, 32, 24, 32, 32, 32, 32, 24, 32, 26, 47},
			{49, 32, 40, 32, 32, 32, 33, 32, 32, 34, 32, 35, 32, 32, 32, 47},
			{49, 32, 34, 37, 35, 32, 32, 40, 38, 32, 32, 32, 40, 38, 39, 47},
			{49, 32, 32, 38, 39, 32, 32, 32, 32, 32, 33, 32, 34, 32, 32, 47},
			{49, 32, 36, 40, 32, 34, 32, 39, 32, 40, 32, 32, 32, 32, 32, 47},
			{49, 32, 35, 32, 32, 32, 32, 32, 32, 37, 35, 32, 32, 33, 32, 47},
			{49, 32, 40, 32, 32, 38, 32, 36, 32, 38, 39, 32, 40, 32, 32, 47},
			{49, 32, 32, 32, 32, 32, 32, 40, 32, 32, 32, 32, 36, 32, 32, 47},
			{49, 36, 32, 38, 32, 32, 32, 32, 32, 32, 32, 34, 32, 32, 32, 47},
			{49, 32, 40, 32, 32, 36, 32, 34, 32, 32, 38, 32, 32, 39, 32, 47},
			{49, 32, 32, 33, 32, 32, 32, 32, 40, 32, 32, 32, 40, 32, 32, 47},
			{49, 32, 32, 32, 40, 32, 37, 35, 32, 32, 34, 32, 32, 36, 32, 47},
			{59, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 61},
			{01, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 03}}},
		{1, {{54, 52, 23, 52, 23, 52, 23, 52, 52, 23, 52, 23, 52, 23, 52, 55},
			{14, 02, 19, 02, 19, 02, 19, 05, 02, 19, 02, 19, 02, 19, 02, 15},
			{49, 36, 27, 32, 27, 32, 27, 32, 32, 27, 32, 27, 36, 27, 32, 47},
			{49, 32, 32, 37, 32, 34, 32, 32, 33, 32, 32, 34, 38, 32, 32, 47},
			{49, 32, 32, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47},
			{49, 32, 32, 32, 32, 32, 34, 32, 35, 32, 32, 32, 32, 33, 32, 47},
			{49, 32, 32, 32, 32, 32, 32, 32, 32, 36, 32, 32, 32, 32, 32, 47},
			{49, 32, 32, 34, 32, 32, 32, 33, 32, 32, 34, 32, 32, 32, 32, 47},
			{49, 38, 32, 32, 32, 32, 32, 39, 32, 32, 32, 32, 32, 32, 32, 47},
			{49, 32, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 36, 32, 47},
			{49, 32, 32, 32, 34, 32, 32, 36, 32, 32, 33, 32, 32, 39, 32, 47},
			{49, 32, 32, 33, 35, 32, 32, 32, 32, 32, 37, 32, 32, 32, 34, 47},
			{49, 34, 32, 32, 32, 32, 34, 32, 33, 32, 32, 36, 32, 32, 32, 47},
			{49, 32, 36, 32, 32, 32, 32, 32, 32, 32, 32, 34, 32, 32, 32, 47},
			{59, 52, 52, 52, 65, 65, 65, 65, 52, 52, 52, 52, 52, 52, 52, 61},
			{01, 02, 05, 02, 65, 65, 65, 65, 02, 02, 02, 04, 02, 02, 02, 03}}} };

	//Map
	const unsigned char MAP_SIZE_TILES = 128; //Maximum size of the map, in tiles
	const short MAP_SIZE_PIXELS = MAP_SIZE_TILES * TILE_SIZE; //Maximum size of map, in pixels

	//Entity
	const unsigned char FEET_COLLISION_HEIGHT = 2;

	//Player
	const unsigned char PLAYER_ANIM_FRAMES = 9; //Number of frames
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
	const unsigned char MAX_MOTIONS = 2;

	//Projectiles
	const short MAX_PROJECTILES = 512;

	//Enums
	enum GAME_STATE { MAIN_MENU, PLAYING, WIN, LOSE }; //Current game state
	enum DIRECTIONS { NORTH, EAST, SOUTH, WEST }; //NESW directions
	enum TEXTURE_LIST {
		SPRITESHEET_TEXTURE, MAP_FLOOR_TEXTURE, TILE_TEXTURE, DOOR_TEXTURE, DOOR_OPEN_TEXTURE, WALL_SIDE_TEXTURE, WALL_TOP_TEXTURE, WATER_FOUNTAIN_TEXTURE,
		LAVA_FOUNTAIN_TEXTURE, PLAYER_TEXTURE
	};
	enum ATTACK_TYPES { ARC, CHARGE, POINT, AREA, PROJECTILE }; //Type of attack
	enum ENTITY_STATES { STATIONARY, MOVING, ATTACKING_STATIONARY, ATTACKING_MOVING, DODGING }; //Current enemy state
	enum ENTITY_WEIGHTS { LIGHT, MEDIUM, HEAVY }; //Weight of entity, reduces knockback
	enum WEAPON_STATES { HOLDING, CHARGING_ARC }; //Current weapon state
	enum PLAYER_INPUT { KEYBOARD, GAMEPAD }; //Player input states
	enum ROOM_TYPES { R32X32, R16X16, R32X16, R16X32 }; //Room types
	enum ATTACK_INPUTS { FIRST_ATTACK, SECOND_ATTACK }; //Attack inputs
	enum COLLISION_TYPES {
		C_FREE_MOVEMENT, C_WALL, C_WALL_TOP, C_WALL_SIDE_LEFT, C_WALL_SIDE_RIGHT, C_WALL_TOP_BOTTOM_LEFT, C_WALL_TOP_BOTTOM_RIGHT, C_FOUNTAIN_BASIN,
		C_COLUMN_TOP, C_COLUMN_BASE, C_CORNER_BOTTOM_LEFT, C_CORNER_BOTTOM_RIGHT
	}; //Collision map types
}

//Updates position of a sprite based on global position
//Returns true if sprite is inside the map area and therefore drawable
bool UpdateSpritePosition(const GameData& game, sf::Sprite& sprite, const sf::FloatRect& globalRect, sf::FloatRect& localRect);