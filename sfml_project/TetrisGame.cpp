#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace sf;

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 20;
const int WINDOW_HEIGHT = 480;
const int WINDOW_WIDTH = 320;

int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
int figures[7][4] = {
		1,3,5,7, // длинная палка
		2,4,5,7, // лесенка
		3,5,4,6, // лесенка наоборот
		3,5,4,7, // полу-крестик
		2,3,5,7, // буквой L
		3,5,7,6, // буквой J
		2,3,4,5, // квадрат
};

float timer = 0;
float delay = 0.3;

int colorNum = 2;	//цвет фигуры
int n = 1;			//тип фигуры
int dx = 0;			//смещение по горизонтали

bool rotate = false;
bool beginGame = true;

struct Point {
	int x, y;
};

Point now[4], tmp[4];

//Проверка столкновения
bool check()
{
	for (int i = 0; i < 4; i++)
		if (now[i].x < 0 || now[i].x >= FIELD_WIDTH || now[i].y >= FIELD_HEIGHT) return 0;
		else if (field[now[i].y][now[i].x]) return 0;

	return 1;
}

//Основной код игры
void tetrisPlay() {
	Clock   clock;
	Texture texture;
	Texture texture_background;
	Texture texture_frame;
	Sprite  sprite;
	Sprite  sprite_background;
	Sprite  sprite_frame;
	
	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\tiles.png");
	texture_background.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\background.png");
	texture_frame.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\frame.png");

	sprite.setTexture(texture);
	sprite_background.setTexture(texture_background);
	sprite_frame.setTexture(texture_frame);
	
	srand(time(0));
	n = rand() % 7;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris Game");
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Up) rotate = true;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;
		}

		//Ускорение
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		
		//Движение
		for (int i = 0; i < 4; i++) {
			tmp[i] = now[i];
			now[i].x += dx;
		}
		
		//Проверка столкновения
		if (!check()) {
			for (int i = 0; i < 4; i++)
				now[i] = tmp[i];
		}

		if (rotate)
		{
			for (int i = 0; i < 4; i++)
			{
				int x = now[i].y - now[1].y; // y - y0
				int y = now[i].x - now[1].x; // x - x0
				now[i].x = now[1].x - x;
				now[i].y = now[1].y + y;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++)
					now[i] = tmp[i];
			}
		}

		//Гравитация
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { tmp[i] = now[i]; now[i].y += 1; }
			if (!check())
			{
				for (int i = 0; i < 4; i++) field[tmp[i].y][tmp[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					now[i].x = figures[n][i] % 2;
					now[i].y = figures[n][i] / 2;
				}

			}
			timer = 0;

		}

		//инициализация нового объекта
		if (beginGame) {
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++) {
				now[i].x = figures[(int)n][i] % 2;
				now[i].y = figures[(int)n][i] / 2;
			}
		}
		rotate = false;dx = 0;delay = 0.3;

		int k = FIELD_HEIGHT - 1;
		for (int i = FIELD_HEIGHT - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < FIELD_WIDTH; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < FIELD_WIDTH) k--;
		}

		window.clear(Color::White);
		window.draw(sprite_background);
		for (int i = 0;i < FIELD_HEIGHT;i++){
			for (int j = 0; j < FIELD_WIDTH; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(28, 31);
				window.draw(sprite);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			sprite.setPosition(now[i].x * 18, now[i].y * 18);
			sprite.move(28, 31);

			window.draw(sprite);
		}
		window.draw(sprite_frame);
		window.display();
	}
}
