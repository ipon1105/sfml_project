#include <SFML/Graphics.hpp>
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
int dx = 0;

float timer = 0;
float delay = 0.3;

bool rotate = false;

struct Point {
	int x, y;
};

Point a[4], b[4];

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= FIELD_WIDTH || a[i].y >= FIELD_HEIGHT) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
}

void tetrisPlay() {
	Clock   clock;
	Texture texture;
	Sprite  sprite;
	
	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\tiles.png", IntRect(0, 0, 18, 18));
	sprite.setTexture(texture);

	srand(time(0));
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris Game");
	
	int n = 3;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}

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

		//Движение
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}

		//Проверка столкновения
		if (!check()) {
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		//Вращение//Point p = a[1];//
		if (rotate)
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - a[1].y; // y - y0
				int y = a[i].x - a[1].x; // x - x0
				a[i].x = a[1].x - x;
				a[i].y = a[1].y + y;
			}

		//Гравитация
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 1;
			timer = 0;
		}

		rotate = false;
		dx = 0;

		window.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(sprite);
		}
		window.display();
	}
}
