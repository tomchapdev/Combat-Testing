#include "rooms.h"

//Initializes the tilemap editor
void Room::Init(GameData& game, const int& roomNumber, const Dim2Di& position)
{
	data = &GC::ROOM_LIST[roomNumber];

	//Position
	rect.left = position.x;
	rect.top = position.y;
	GetTypeDimensions(rect.width, rect.height);

	//Draw tiles
	char tileID = 0;
	for (int y = 0; y < rect.height; ++y)
	{
		for (int x = 0; x < rect.width; ++x)
		{
			tileID = data->tilemap[y][x];
			if (tileID < GC::DOOR_START_NUM)
			{
				TileDrawing(game, x, y, tileID);
				CheckForAnimatedTiles(game, x, y, tileID);
			}
		}
	}

	//Draw doors
	FindDoors();
	int doorID;

	for (int z = 0; z < doorCounter; ++z)
	{
		doorID = data->tilemap[doorsList[z].top][doorsList[z].left];
		game.doorTexture.loadFromImage(game.spritesheetImg, GC::TILELIST[doorID].rect);
		game.mapTexture.update(game.doorTexture, (rect.left + doorsList[z].left) * GC::TILE_SIZE, (rect.top + doorsList[z].top) * GC::TILE_SIZE);
	}
}

//Finds doors in this room
void Room::FindDoors()
{
	bool firstDoor = true;

	for (int y = 0; y < rect.height; ++y)
	{
		for (int x = 0; x < rect.width; ++x)
		{
			if (data->tilemap[y][x] >= GC::DOOR_START_NUM)
			{
				if (firstDoor)
				{
					doorsList[doorCounter] = { x, y, 4, 2 };
					doorCounter += 1;
					firstDoor = false;
				}
				else if (!CheckIfFoundDoor(doorsList, doorCounter, x, y))
				{
					doorsList[doorCounter] = { x, y, 4, 2 };
					doorCounter += 1;
				}
			}
		}
	}
}

//Check if this door tile is part of an already found door
bool Room::CheckIfFoundDoor(sf::IntRect* doorsList, const int& doorCounter, const int& x, const int& y)
{
	bool found = false;
	for (int z = 0; z < doorCounter; ++z)
	{
		if ((x >= doorsList[z].left) && (x < (doorsList[z].left + doorsList[z].width)))
		{
			if ((y >= doorsList[z].top) && (y < (doorsList[z].top + doorsList[z].height)))
			{
				found = true;
			}
		}
	}
	return found;
}

//Changes variables to dimensions of the room
void Room::GetTypeDimensions(int& width, int& height)
{
	if (data->type == GC::R32X32)
	{
		width = 32;
		height = 32;
	}
	else if (data->type == GC::R16X16)
	{
		width = 16;
		height = 16;
	}
	else if (data->type == GC::R32X16)
	{
		width = 32;
		height = 16;
	}
	else if (data->type == GC::R16X32)
	{
		width = 16;
		height = 32;
	}
}

//Updates the 
void Room::TileDrawing(GameData& game, const int& x, const int& y, const char& tileID)
{
	//Complicated alterations based on tile ID
	bool requiresFloor = false, wallside = false, walltop = false, corner = false, right = false;
	int correction = 0;
	Tile tile = GC::TILELIST[tileID];

	TileDrawingBools(tile, requiresFloor, wallside, walltop, corner, right);

	if (requiresFloor && (y != 0))
	{
		DrawRandomFloor(game, x, y);

		//Draw tile
		if (wallside)
		{
			tile.rect.width = GC::WALL_SIDE_WIDTH;

			if (right)
			{
				correction = GC::TILE_SIZE - GC::WALL_SIDE_WIDTH;

				tile.rect.left += correction;
				game.wallsideTexture.loadFromImage(game.spritesheetImg, tile.rect);

				tile.rect.left -= correction;
				game.mapTexture.update(game.wallsideTexture, ((rect.left + x) * GC::TILE_SIZE) + correction, (rect.top + y) * GC::TILE_SIZE);
			}
			else
			{
				game.wallsideTexture.loadFromImage(game.spritesheetImg, tile.rect);
				game.mapTexture.update(game.wallsideTexture, (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE);
			}
		}
		else if (walltop)
		{
			tile.rect.height = GC::WALL_TOP_HEIGHT;
			correction = GC::TILE_SIZE - GC::WALL_TOP_HEIGHT;

			tile.rect.top += correction;
			game.walltopTexture.loadFromImage(game.spritesheetImg, tile.rect);

			tile.rect.top -= correction;
			game.mapTexture.update(game.walltopTexture, (rect.left + x) * GC::TILE_SIZE, ((rect.top + y) * GC::TILE_SIZE) + correction);
		}
		else if (corner)
		{
			//Wall top
			tile.rect.height = GC::WALL_TOP_HEIGHT;
			correction = GC::TILE_SIZE - GC::WALL_TOP_HEIGHT;

			tile.rect.top += correction;
			game.walltopTexture.loadFromImage(game.spritesheetImg, tile.rect);

			tile.rect.top -= correction;
			game.mapTexture.update(game.walltopTexture, (rect.left + x) * GC::TILE_SIZE, ((rect.top + y) * GC::TILE_SIZE) + correction);

			//Wall side
			tile.rect.height = GC::TILE_SIZE;
			tile.rect.width = GC::WALL_SIDE_WIDTH;

			if(right)
			{
				correction = GC::TILE_SIZE - GC::WALL_SIDE_WIDTH;

				tile.rect.left += correction;
				game.wallsideTexture.loadFromImage(game.spritesheetImg, tile.rect);

				tile.rect.left -= correction;
				game.mapTexture.update(game.wallsideTexture, ((rect.left + x) * GC::TILE_SIZE) + correction, (rect.top + y) * GC::TILE_SIZE);
			}
			else
			{
				game.wallsideTexture.loadFromImage(game.spritesheetImg, tile.rect);
				game.mapTexture.update(game.wallsideTexture, (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE);
			}
		}
		else
		{
			game.tileTexture.loadFromImage(game.spritesheetImg, tile.rect);
			game.mapTexture.update(game.tileTexture, (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE);
		}
	}
	else //No extra drawing required for this tile
	{
		game.tileTexture.loadFromImage(game.spritesheetImg, tile.rect);
		game.mapTexture.update(game.tileTexture, (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE);
	}
}

//Gets booleans for current tile
void Room::TileDrawingBools(const Tile& tile, bool& requiresFloor, bool& wallside, bool& walltop, bool& corner, bool& right)
{
	if ((tile.ID >= GC::WALL_TOP_RANGE.x) && (tile.ID <= GC::WALL_TOP_RANGE.y))
	{
		requiresFloor = true;
		walltop = true;
	}
	else if ((tile.ID >= GC::WALL_SIDE_RANGE.x) && (tile.ID <= GC::WALL_SIDE_RANGE.y))
	{
		requiresFloor = true;

		if (tile.ID < GC::WALL_SIDE_RANGE.x + 2)
		{
			walltop = true;
		}
		else if (tile.ID == GC::WALL_SIDE_RANGE.x + 2)
		{
			wallside = true;
			right = true;
		}
		else
		{
			wallside = true;
		}
	}
	else if ((tile.ID >= GC::WALL_CORNER_RANGE.x) && (tile.ID <= GC::WALL_CORNER_RANGE.y))
	{
		requiresFloor = true;

		if (tile.ID < GC::WALL_CORNER_RANGE.x + 2)
		{
			walltop = true;
		}
		else if (tile.ID == GC::WALL_CORNER_RANGE.x + 3)
		{
			corner = true;
			right = true;
		}
		else
		{
			corner = true;
		}
	}
	else if ((tile.ID >= GC::WALL_INCORNER_RANGE.x) && (tile.ID <= GC::WALL_INCORNER_RANGE.y))
	{
		requiresFloor = true;

		if (tile.ID > GC::WALL_CORNER_RANGE.x + 1)
		{
			walltop = true;
		}
		else if (tile.ID == GC::WALL_CORNER_RANGE.x + 1)
		{
			corner = true;
			right = true;
		}
		else
		{
			corner = true;
		}
	}
	else if (tile.ID == 21) //Wall column top
	{
		requiresFloor = true;
	}
}

//Draws a random floor at a specific locations
void Room::DrawRandomFloor(GameData& game, const int& x, const int& y)
{
	//Get random floor, approx 10% chance to be a blemished floor, 90% to be Floor 1
	int floorID = std::rand() % (GC::FLOOR_RANGE.y * 2);

	if (floorID < GC::FLOOR_RANGE.x)
	{
		floorID = GC::FLOOR_RANGE.x;
	}
	else if (floorID > GC::FLOOR_RANGE.y)
	{
		floorID = GC::FLOOR_RANGE.x;
	}

	//Draw random floor
	game.tileTexture.loadFromImage(game.spritesheetImg, GC::TILELIST[floorID].rect);
	game.mapTexture.update(game.tileTexture, (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE);
}

//Checks for animated tiles
void Room::CheckForAnimatedTiles(GameData& game, const int& x, const int& y, const char& tileID)
{
	if (tileID == 9) //Lava fountain
	{
		AnimatedTiles animTile;

		animTile.sprite.setTexture(game.lavaFountainTexture);
		animTile.sprite.setTextureRect({0, 0, GC::TILE_SIZE, GC::FOUNTAIN_ANIM_LAVA_RECT.height});
		animTile.anim = {&GC::FOUNTAIN_ANIM_LAVA, 0, 0.f};
		//animTile.globalRect = { (rect.left + x) * GC::TILE_SIZE, (rect.top + y) * GC::TILE_SIZE,
		//						GC::FOUNTAIN_ANIM_LAVA_RECT.width, GC::FOUNTAIN_ANIM_LAVA_RECT.height };

		animTile.sprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
		animTile.globalRect = { (int)(rect.left + x) * GC::SCALED_TILE,
								(int)((rect.top + y) * GC::SCALED_TILE) - GC::FOUNTAIN_ANIM_TOP_RECT.height,
								GC::FOUNTAIN_ANIM_LAVA_RECT.width, GC::FOUNTAIN_ANIM_LAVA_RECT.height };


		animatedTiles.push_back(animTile);
		std::cout << "Lava fountain created!" << std::endl;
	}
	else if (tileID == 11) //Water fountain
	{
		AnimatedTiles animTile;

		animTile.sprite.setTexture(game.waterFountainTexture);
		animTile.sprite.setTextureRect({ 0, 0, GC::TILE_SIZE, GC::FOUNTAIN_ANIM_WATER_RECT.height });
		animTile.anim = { &GC::FOUNTAIN_ANIM_WATER, 0, 0.f };

		animTile.sprite.setScale(GC::SPRITE_SCALE, GC::SPRITE_SCALE);
		animTile.globalRect = { (int)(rect.left + x) * GC::SCALED_TILE,
								(int)((rect.top + y) * GC::SCALED_TILE) - GC::FOUNTAIN_ANIM_TOP_RECT.height,
								GC::FOUNTAIN_ANIM_WATER_RECT.width, GC::FOUNTAIN_ANIM_WATER_RECT.height };

		animatedTiles.push_back(animTile);
		std::cout << "Water fountain created!" << std::endl;
	}
}

//Updates animated tiles
void Room::UpdateAnimatedTiles(const GameData& game, sf::RenderWindow& window)
{
	bool animVisible = false;

	for (int x = 0; x != animatedTiles.size(); ++x)
	{
		animVisible = UpdateSpritePosition(game, animatedTiles[x].sprite, (sf::FloatRect)animatedTiles[x].globalRect, animatedTiles[x].localRect);


		if (animVisible)
		{
			animatedTiles[x].anim.UpdateAnimation(animatedTiles[x].sprite, game.elapsed);
			window.draw(animatedTiles[x].sprite);
			animVisible = false;
		}
	}
}

//Checks if the room is within the rendered map area
bool Room::WithinRenderedArea(const GameData& game)
{
	//To ensure the room is at least 3 tiles into the rendered area
	int offset = 3;

	//Check all 4 corners of the room to see if the room is being rendered
	if (game.mapRect.contains({(rect.left + offset) * GC::TILE_SIZE, (rect.top + offset) * GC::TILE_SIZE }) ||
		game.mapRect.contains({ (rect.left + rect.width - offset) * GC::TILE_SIZE, (rect.top + offset) * GC::TILE_SIZE }) ||
		game.mapRect.contains({ (rect.left + offset) * GC::TILE_SIZE, (rect.top + rect.height - offset) * GC::TILE_SIZE }) ||
		game.mapRect.contains({ (rect.left + rect.width - offset) * GC::TILE_SIZE, (rect.top + rect.height - offset) * GC::TILE_SIZE }))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Finds enemy spawn locations
void Room::FindSpawners()
{

}