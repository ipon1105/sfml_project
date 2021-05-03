#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int FIELD_WIDTH = 4;
const int FIELD_HEIGHT = 4;
const int SIZE_TILE = 64;
const int WINDOW_WIDTH = FIELD_WIDTH*SIZE_TILE;
const int WINDOW_HEIGHT = FIELD_HEIGHT * SIZE_TILE;

int field[FIELD_WIDTH][FIELD_HEIGHT] = { 0 };

void fillMyMap() {
	
}

void puzzlePlay() {
	Texture texture;
	Sprite sprite;

	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\15.png");
	sprite.setTexture(texture);

	srand(time(0));

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Puzzle Game");

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}