#pragma once
#include "data.h"
#include "graphics.h"

//An interactive game room
struct Room
{
	//Data
	const RoomData* data{}; //Room data

	//Main stats
	char ID = 0; //Which
	sf::IntRect rect = { 0, 0, 0, 0 }; //Where the room is on the global map, in tiles
	std::vector<sf::IntRect> doorsList = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }; //List of door positions

	//Counters
	int doorCounter = 0; //How many doors are in this room

	//Bools
	bool isOpen = true; //If doors are open or not
	bool hasAnimatedTiles = false; //If the room has animations or not
	bool visible = false; //If the room is within the rendered map area

	//Structs
	std::vector<AnimatedTiles> animatedTiles; //Vector of all the animated tiles in this room

	//Initializes the room
	void Init(GameData& game, const int& roomNumber, const Dim2Di& position);

	//Finds doors in this room
	void FindDoors();

	//Check if this door tile is part of an already found door
	bool CheckIfFoundDoor(std::vector<sf::IntRect>& doorsList, const int& doorCounter, const int& x, const int& y);

	//Changes variables to dimensions of the room
	void GetTypeDimensions(int& width, int& height);

	//Draws the tile onto the game map
	void TileDrawing(GameData& game, const int& x, const int& y, const char& tileID);

	//Gets booleans for current tile
	void TileDrawingBools(const Tile& tile, bool& requiresFloor, bool& wallside, bool& walltop, bool& corner, bool& right);

	//Draws a random floor at a specific locations
	void DrawRandomFloor(GameData& game, const int& x, const int& y);

	//Alters the collision map based on the tile
	void AlterCollisionMap(GameData& game, const int& x, const int& y, const char& tileID);

	//Checks for animated tiles
	void CheckForAnimatedTiles(GameData& game, const int& x, const int& y, const char& tileID);

	//Updates animated tiles
	void UpdateAnimatedTiles(const GameData& game, sf::RenderWindow& window);

	//Finds enemy spawn locations
	void FindSpawners();
};

namespace GC //Global constants
{
	const char DOOR_TILE_WIDTH = 4;
	const char DOOR_TILE_HEIGHT = 2;
}