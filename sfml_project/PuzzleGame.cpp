#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;

const int FIELD_WIDTH = 4;
const int FIELD_HEIGHT = 4;
const int SIZE_TILE = 64;
const int WINDOW_WIDTH = FIELD_WIDTH*SIZE_TILE;
const int WINDOW_HEIGHT = FIELD_HEIGHT * SIZE_TILE;

String strWin1 = L"Вы победили.\nR - сыграть ещё раз.";

int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

bool tf = false;

void fillMyMap() {
	//Отчищаем карту
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++) field[i][j] = 0;

	//Рандомно её заполняем от 1 до 15
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++)
			while (true) {
				if (i == FIELD_HEIGHT -1 && j == FIELD_WIDTH -1) break;
				
				int randomNum = rand() % 15 + 1;
				bool again = false;

				for (auto& height : field)
					for (auto& width : height)
						if (width == randomNum) again = true;
				
				if (!again) { field[i][j] = randomNum; break; }
			}
}

void moveTurn(int x, int y) {
	if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) return;

	if (field[y][x] == 16) return;

	int x_16 = -1, y_16 = -1;
	
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++) if (field[i][j] == 0) {
			x_16 = j; 
			y_16 = i; 
			j = FIELD_WIDTH; 
			i = FIELD_HEIGHT; 
		}

	if ((x_16 == x && y_16 == y) || (x_16 != x && y_16 != y) || x_16==-1 || y_16 ==-1) return;

	if (y == y_16) 		
		while (x < x_16 || x > x_16) {
			if (x == x_16) break;

			int tmp = field[y][(x < x_16) ? (x_16 - 1) : (x_16 + 1)];
			field[y][(x < x_16) ? (x_16 - 1) : (x_16 + 1)] = field[y][x_16];
			field[y][x_16] = tmp;
			
			(x < x_16) ? x_16-- : x_16++;
		}
	else 
		while (y < y_16 || y > y_16) {
			if (y == y_16) break;

			int tmp = field[(y < y_16) ? (y_16 - 1) : (y_16 + 1)][x];
			field[(y < y_16) ? (y_16 - 1) : (y_16 + 1)][x] = field[y_16][x];
			field[y_16][x] = tmp;

			(y < y_16) ? y_16-- : y_16++;
		}
}

bool check1() {
	int now = 1;
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++) 
			if (now != field[i][j] && field[i][j] != 0) return false; else now++;
	
	return true;
}

void puzzlePlay() {
	Texture texture;
	Sprite sprite;
	Text text;
	Font font;

	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\15.png");
	sprite.setTexture(texture);font.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\resources\\20653.otf");
	text.setFont(font);
	text.setPosition(0, FIELD_HEIGHT * SIZE_TILE / 2);
	text.setFillColor(Color::Red);
	text.setCharacterSize(25);

	srand(time(0));
	fillMyMap();

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Puzzle Game");

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed) { 
				auto code = event.key.code;
				if (code == Keyboard::R) fillMyMap();
				if (code == Keyboard::K) {
					int n = 1;
					for (int i = 0; i < FIELD_HEIGHT; i++)
						for (int j = 0; j < FIELD_WIDTH; j++) {
							field[i][j] = n;
							n++;
						}
				}
			
				int x_16 = -1, y_16 = -1;
				for (int i = 0; i < FIELD_HEIGHT; i++)
					for (int j = 0; j < FIELD_WIDTH; j++) if (field[i][j] == 0) {
						x_16 = j;
						y_16 = i;
						j = FIELD_WIDTH;
						i = FIELD_HEIGHT;
					}

				if (x_16 == -1 || y_16 == -1) break;
				
				moveTurn((code == Keyboard::Right) ? x_16 + 1 : ((code == Keyboard::Left) ? x_16 - 1 : x_16), (code == Keyboard::Up) ? y_16 - 1 : ((code == Keyboard::Down) ? y_16 + 1 : y_16));
			}
			if (event.type == Event::MouseButtonPressed) {

				int x = Mouse::getPosition(window).x / SIZE_TILE,
					y = Mouse::getPosition(window).y / SIZE_TILE;

				if (event.key.code == Mouse::Left) moveTurn(x,y);
			}
		}

		tf = check1();
		window.clear();

		for (int i = 0; i < FIELD_HEIGHT; i++)
			for (int j = 0; j < FIELD_WIDTH; j++) {
				sprite.setTextureRect(IntRect(((field[i][j] - 1) % 4) * SIZE_TILE, ((field[i][j] - 1) / 4) * SIZE_TILE, SIZE_TILE, SIZE_TILE));
				sprite.setPosition(j * SIZE_TILE, i * SIZE_TILE);
				if (tf) {
					sprite.setColor(Color(255, 255, 255, 230));
					text.setString(strWin1);
					window.draw(text);
				}
				window.draw(sprite);
			}
		
		window.display();
	}
}