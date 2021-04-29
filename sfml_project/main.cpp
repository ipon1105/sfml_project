#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrisGame.h"

using namespace sf;

const int HEIGHT = 600;
const int WIDTH = 800;

int main1()
{
	ContextSettings setting;
	setting.antialiasingLevel = 8;

	Vertex line_without_thickness[] = {
		Vertex(Vector2f(390.f, 240.f)), // координата первой вершины
		Vertex(Vector2f(470.f, 150.f))
	};

	CircleShape circle(50.f, 30);
	circle.setFillColor(Color(255, 0, 0));
	circle.setOutlineThickness(15.f);
	circle.setOutlineColor(Color(0, 255, 0));
	circle.move(15, 15);

	ConvexShape convex;
	convex.setPointCount(5);
	convex.setPoint(0, Vector2f(0.f, 0.f));
	convex.setPoint(1, Vector2f(150.f, 10.f));
	convex.setPoint(2, Vector2f(120.f, 90.f));
	convex.setPoint(3, Vector2f(30.f, 100.f));
	convex.setPoint(4, Vector2f(5.f, 50.f));
	convex.setFillColor(Color::Black);

	RectangleShape rectangle(Vector2f(100, 100));
	rectangle.move(165, 150);
	rectangle.setFillColor(Color::Blue);
	
	
	RectangleShape line(Vector2f(50, 5));
	line.setFillColor(Color::Green);
	line.move(WIDTH/2, HEIGHT/2);


	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML Works!",Style::Default,setting);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
			if (event.KeyPressed) {
				switch (event.key.code)
				{
				case Keyboard::W: circle.move(0, -1); break;
				case Keyboard::S: circle.move(0, 1); break;
				case Keyboard::A: circle.move(-1, 0); break;
				case Keyboard::D: circle.move(1, 0); break;
				default:
					break;
				}
			}
			
			if (event.MouseMoved) {
				int8_t i8;
				int16_t i16;
				int32_t i32;
				int64_t i64;

				int x = event.mouseMove.x;
				int y = event.mouseMove.y;
				line.setRotation(atan2(y-line.getPosition().y, x-line.getPosition().x) * 180 / 3.1415);
			}
		}
		window.clear(Color(255,255,255));
		
		window.draw(convex);
		window.draw(circle);
		window.draw(rectangle);
		window.draw(line);

		window.display();
	}

	return 0;
}

int main() {
	tetrisPlay();
	#pragma region Шаблон

	/*
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Texture lesson");

	Texture texture;
	texture.loadFromFile("C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\images\\tiles.png", IntRect(0,0,18,18));
	texture.setSmooth(true);//сглажевание
	//Чтобы загрузить лишь часть изображения, можно нужно к функции подгрузки добавить
	//второй параметр - texture.loadFromFile("image.png", IntRect(10, 10, 32, 32));

	// Включаем режим повторения для текстуры
	//texture.setRepeated(true);
	//setOrigin(float, float) - установка точки относительно трансформации
	Sprite sprite(texture);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return 0;
			}
		}


		window.clear(Color::White);
		window.draw(sprite);
		window.display();
	}

	return 0;
	*/
#pragma endregion
}