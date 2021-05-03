#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 10;
const int SIZE_TILE = 32;
const int WINDOW_WIDTH = FIELD_WIDTH * SIZE_TILE;
const int WINDOW_HEIGHT = FIELD_HEIGHT * SIZE_TILE;

enum field
{
	empty,	//0 = пустое место
	one,	//1
	two,	//2
	three,	//3
	four,   //4
	five,	//5
	six,	//6
	seven,	//7
	eight,	//8
	bomb,	//9 = бомба
	block,	//10 = закрытый блок
	flag	//11 = флаг
};

int fieldDown[FIELD_WIDTH][FIELD_HEIGHT] = { 0 };
int fieldUp[FIELD_WIDTH][FIELD_HEIGHT] = { 0 };
int bombCount = 10;

String strWin = L"Вы победили.";
String strLose = L"Вы проиграли.";
String strR = L"Нажмите R, что бы сыграть ещё раз.";

bool live = true;

void fillMap() {
	live = true;

	//Отчищаем карты
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++) {
			fieldDown[i][j] = empty; 
			fieldUp[i][j] = block; 
		}

	//Добавляем на карту бомбы
	for (int i = 0; i < bombCount; i++)
	{
		do
		{
			int x = rand() % FIELD_WIDTH, y = rand() % FIELD_HEIGHT;
			if (fieldDown[x][y] == bomb) continue; else { fieldDown[x][y] = bomb; break; }
		} while (true);
	}

	//Добавляем на карту цифры
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++) {
			int countBombsAroud = 0;
			
			if(fieldDown[i][j]!=bomb){
				for(int k = i-1; k <= i+1; k++)
					for (int l = j - 1; l <= j + 1; l++)
						if (!(k < 0 || k >= FIELD_WIDTH || l < 0 || l >= FIELD_HEIGHT) && fieldDown[k][l] == bomb) countBombsAroud++;
				fieldDown[i][j] = countBombsAroud;
			}
			
		}
}

void openMap(int x, int y) {
	if (!(x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT)) { 
		if (fieldUp[x][y] == empty || fieldUp[x][y] == flag) return;
		fieldUp[x][y] = fieldDown[x][y]; 
		if (fieldUp[x][y] == empty) {
			for (int k = x - 1; k <= x + 1; k++)
				for (int l = y - 1; l <= y + 1; l++) openMap(k, l);
		}
	}
}

void saperPlay() {
	Texture texture;
	Sprite sprite;
	Font font;
	Text text;

	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\sapertiles.jpg");
	sprite.setTexture(texture);
	font.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\resources\\20653.otf");
	text.setFont(font);
	text.setPosition(0, FIELD_HEIGHT*SIZE_TILE / 2);
	text.setFillColor(Color::Red);
	text.setCharacterSize(30);

	srand(time(0));

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Saper Game");

	fillMap();
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) if (event.key.code == Keyboard::R) fillMap();
			if (!live) break;
			if (event.type == Event::MouseButtonPressed) {

				int x = Mouse::getPosition(window).x / SIZE_TILE,
					y= Mouse::getPosition(window).y / SIZE_TILE;

				if (event.key.code == Mouse::Right) 
					if(fieldUp[x][y] == block)
						fieldUp[x][y] = flag;
					else if (fieldUp[x][y] == flag)
						fieldUp[x][y] = block;
						
				if (event.key.code == Mouse::Left) 
					openMap(x,y);
			}
		}

		bool win = true;
		int t = 0;

		//Проверяем на победу или проигрыш
		for (int i = 0; i < FIELD_WIDTH; i++)
			for (int j = 0; j < FIELD_HEIGHT; j++) {
				if (fieldUp[i][j] == bomb) { live = false; text.setString(strLose); break; }
				else if (fieldUp[i][j] == flag && fieldDown[i][j] == bomb) t++;
			}
		if (t == bombCount) { live = false; win = true; } else win = false;

		window.clear(Color::White);
				
		//Отрисовываем поверхность
		for (int i = 0; i < FIELD_WIDTH; i++)
			for (int j = 0; j < FIELD_HEIGHT; j++) {
				sprite.setTextureRect(IntRect(fieldUp[i][j] * SIZE_TILE, 0, SIZE_TILE, SIZE_TILE));
				sprite.setPosition(i * SIZE_TILE, j * SIZE_TILE);
				if (!live) sprite.setColor(Color(255, 255, 255, 220));
				window.draw(sprite);
			}

		//Пишем, о смерти или победе
		if (!live) {
			text.setCharacterSize(30);
			text.setString((win) ? strWin : strLose);
			text.setPosition(100, WINDOW_HEIGHT / 2 - 70);
			window.draw(text);

			text.setCharacterSize(20);
			text.setString(strR);
			text.setPosition(0, WINDOW_HEIGHT / 2 + 30 -70);
			window.draw(text);
		}
		
		window.display();
	}
}