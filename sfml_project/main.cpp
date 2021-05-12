#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "TetrisGame.h"
#include "SaperGame.h"
#include "PuzzleGame.h"
#include "Test_1.h"

using namespace sf;

int main() {
	/*std::map<std::string, int> mapping;
	
	mapping["Tetris"] = 1;
	mapping["Saper"]  = 2;
	mapping["Puzzle"] = 3;
	mapping["Test"]   = 4;
	mapping["Exit"]   = 5;
	for()
	*/
	int a = 0;
	while(a!=999){
		std::cout << "\tMenu" << std::endl;
		std::cout << "1 - Tetris" << std::endl;
		std::cout << "2 - Saper" << std::endl;
		std::cout << "3 - Puzzle" << std::endl;
		std::cout << "4 - Test 1" << std::endl;
		std::cout << "999 - exit" << std::endl;

		std::cin >> a;
		switch (a)
		{
		
		case 1: 
		tetrisPlay();
		break;
		
		case 2: 
		saperPlay();
		break;
		
		case 3: 
		puzzlePlay();
		break;
		
		case 4: 
		test_1::playTest_1();
		break;
		
		default:
			std::cout << "fucke tou man." << std::endl;
			break;
		}
	}
	
}