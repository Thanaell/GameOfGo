// GameOfGo.cpp : Defines the entry point for the console application.
//

#include "GameOfGo.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Stone.h"
#include <iostream>

int main()
{
	int i = 0;
	int j = 0;
	Board myBoard;
	sf::RenderWindow window(sf::VideoMode(880, 880), "SFML window");
	StoneColor colorToPlay = BLACK;
	while (window.isOpen())
	{
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				//clever cast :)
				i = sf::Mouse::getPosition(window).x/myBoard.getCaseSize();
				j = sf::Mouse::getPosition(window).y / myBoard.getCaseSize();
				std::cout<<colorToPlay<< " " << i << " " << j << std::endl;

				if (Stone::createStone(i, j, colorToPlay, myBoard)) {
					if (colorToPlay == BLACK) {
						colorToPlay = WHITE;
					}
					else {
						colorToPlay = BLACK;
					}
					i++;
					j++;
				}
			}
		}
		// Clear the whole window before rendering a new frame
		window.clear();
		// Draw some graphical entities
		myBoard.draw(window);
		// End the current frame and display its contents on screen
		window.display();
	}
    return 0;
}

