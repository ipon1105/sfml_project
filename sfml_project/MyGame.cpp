#include <SFML/Graphics.hpp>

namespace myGame {
	using namespace sf;
	
	class Tile {
	private:
		FloatRect	position;//x,y,width,heitgh
		Sprite		sprite;
	public:
		Tile(FloatRect rect) {
			position = rect;
		}

		void initSprite(Texture &text, IntRect rect) {
			sprite.setTexture(text);
			sprite.setTextureRect(rect);
		}

		void render(RenderWindow window) {
			sprite.setPosition(position.left, position.top);
			window.draw(sprite);
		}
	};

	void play() {
		RenderWindow window(VideoMode(500, 500), "Game");

		while (window.isOpen()) {

			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) window.close();
			}

			window.clear(Color::White);

			window.display();
		}
	}
}