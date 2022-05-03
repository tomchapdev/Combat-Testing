//#include "audio.h"
#include "player.h"
#include "rooms.h"
#include "ui.h"

//To find out how many lines of code, Ctrl + Shift + F, type "\n" in the search box and enable regular expressions

void GetCursorImage(sf::Cursor& cursor, sf::RenderWindow& window)
{
	sf::Image cursorImg;
	cursorImg.create(16, 16);
	cursorImg.loadFromFile("cursor.png");

	if (cursor.loadFromPixels(cursorImg.getPixelsPtr(), { 16, 16 }, { 0, 0 }))
	{
		window.setMouseCursor(cursor);
	}

}

int main()
{
	//Window
	sf::RenderWindow window;

	//Clock
	sf::Clock clock;
	srand((int)time(0)); //Sets random's seed to current time, for "true random"

	//Game data
	GameData gamedata;
	gamedata.Init(window);

	//Cursor
	sf::Cursor cursor;
	GetCursorImage(cursor, window);

	//Room
	Room startRoom;
	startRoom.Init(gamedata, 0, { 32, 32 });
	Room enemyRoom;
	enemyRoom.Init(gamedata, 1, { 32, 56 });
	Room itemRoom;
	itemRoom.Init(gamedata, 2, { 32, 8 });

	//Player
	Player player1;
	player1.Init(gamedata);

	window.setFramerateLimit(GC::FRAMERATE);

	//Start the game loop 
	while (window.isOpen()) //Could change this to a state manager?
	{
		// Clear screen
		window.clear(sf::Color::Black);
		//Clock
		gamedata.elapsed = clock.getElapsedTime().asSeconds();
		//std::cout << gamedata.elapsed << std::endl;
		clock.restart();

		player1.InputHandling(window, gamedata);
		player1.entity.Move(gamedata);
	
		// Update the window
		//Draw map, then enemies, then player
		//gamedata.RenderMap(window, (int)(player1.entity.globalRect.left + (player1.entity.bodyCentre.x / GC::SPRITE_SCALE)),
		//							(int)(player1.entity.globalRect.top + (player1.entity.bodyCentre.y / GC::SPRITE_SCALE)));
		gamedata.RenderMap(window, (int)((player1.entity.globalRect.left + player1.entity.bodyCentre.x) / GC::SPRITE_SCALE),
										(int)((player1.entity.globalRect.top + player1.entity.bodyCentre.y) / GC::SPRITE_SCALE));
		//Render animated tiles
		if (startRoom.WithinRenderedArea(gamedata))
		{
			startRoom.UpdateAnimatedTiles(gamedata, window);
		}
		if (enemyRoom.WithinRenderedArea(gamedata))
		{
			enemyRoom.UpdateAnimatedTiles(gamedata, window);
		}
		if (itemRoom.WithinRenderedArea(gamedata))
		{
			itemRoom.UpdateAnimatedTiles(gamedata, window);
		}

		//Render player last
		player1.entity.Render(window, gamedata);

		//gamedata.RenderCamera(window);
		window.display();
	}

	return EXIT_SUCCESS;
}