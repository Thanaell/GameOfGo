#include "Game.h"
#include <iostream>

Game::Game():window(sf::VideoMode(880, 880), "Play Go") {}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	int i;
	int j;
	while (window.pollEvent(event))
	{
		// Request for closing the window
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			//clever cast :)
			i = sf::Mouse::getPosition(window).x / myBoard.getCaseSize();
			j = sf::Mouse::getPosition(window).y / myBoard.getCaseSize();
			std::cout << colorToPlay << " " << i << " " << j << std::endl;

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
}

void Game::render() {
	// Clear the whole window before rendering a new frame
	window.clear();
	// Draw some graphical entities
	myBoard.draw(window);
	// End the current frame and display its contents on screen
	window.display();
}