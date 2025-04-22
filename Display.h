#ifndef DISPLAY_H
#define DISPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>

class Display
{
	public:
		Display(sf::RenderWindow& realwindow);
		void refresh(std::array<int,2> grabedpos = {{0,0}});
		void setBoard(std::vector<std::array<int,4>> newboard);
	protected:
		sf::RenderWindow& window;
		sf::RectangleShape lineHori;
		sf::RectangleShape lineVert;
		sf::RectangleShape square;
		sf::CircleShape neutralPiece;
		std::vector<std::array<int,4>> board;
};

#endif
