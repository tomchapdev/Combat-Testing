//#include "audio.h"
#include "player.h"
#include "rooms.h"
#include "ui.h"

//To find out how many lines of code, Ctrl + Shift + F, type "\n" in the search box and enable regular expressions

// !!!! USEFUL SHIT !!!! LEARN THESE !!!!
//Click on symbol name and press F12 to go to definition
//Ctrl + Left click = the same as F12
//Crtl + K and Crtl + O to swap between header and source file
//Crtl-Shift-B to build the project
//F5 to build and run the project
//To change multiple symbols at once:
//SHIFT + ALT + . = Select occurence
//SHIFT + ALT + , = Deselect 1 occurence
//Shift + Alt + Up Arrow = Select vertically upwards
//Shift + Alt + Down Arrow = Select vertically downwards
//CTRL + R, CTRL + R = Rename variable
//CTRL + , = Search for thing in project
//CTRL + K, CTRL + C = Comment
//CTRL + K, CTRL + U = uncomment
//CRTL + SHIFT + V - Clipboard history
// SHIFT + END selects up to the end of the line
// SHIFT + HOME selects up to the beginning of the line
// !!!! FUCKIN LEARN THESE !!!!

void GetCursorImage(sf::Cursor& cursor, sf::RenderWindow& window)
{
	sf::Image tempCursor;
	tempCursor.create(16, 16);
	tempCursor.loadFromFile("cursor.png");

	if (cursor.loadFromPixels(tempCursor.getPixelsPtr(), { 16, 16 }, { 0, 0 }))
	{
		window.setMouseCursor(cursor);
	}
}

int main()
{
	//Window
	sf::RenderWindow window;

	//Game data
	GameData gamedata;
	gamedata.Init(window);

	//Clock
	sf::Clock clock;
	srand((int)time(0)); //Sets random's seed to current time, for "true random"

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

	//Projectiles
	std::vector<Projectile> projectiles(GC::MAX_PROJECTILES);

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
		gamedata.RenderMap(window, player1.entity.globalRect.left + player1.entity.bodyCentre.x, player1.entity.globalRect.top + player1.entity.bodyCentre.y, player1.entity.movementVector);

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
		window.display();
	}

	return EXIT_SUCCESS;
}