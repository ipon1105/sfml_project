#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>


namespace test_1 {

	using namespace sf;

	const int WINDOW_WIDTH  = 600;
	const int WINDOW_HEIGHT = 600;

	void load(SoundBuffer* buf, int num) {
		std::string path = "C:\\Users\\ipon1105\\source\\repos\\sfml_project\\sfml_project\\audioRes\\";
		std::string name = std::to_string(num);

		buf->loadFromFile(path + name + ".mp3");
	}

	void playTest_1() {	
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "test_1");

		bool playMusic = false;

		SoundBuffer buffer;
		Sound		sound;

		//8 (927) 841 46-56
		while (window.isOpen())
		{
			
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) window.close();
				if (event.type == Event::KeyPressed) {
					std::cout << "Code = " << event.key.code<<"\t"<<"simbol = "<<(char) event.key.code << std::endl;
				}
			}
			window.clear(Color::White);

			window.display();
		}
	}
}