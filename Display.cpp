#include "Display.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>

Display::Display(sf::RenderWindow& realwindow)
:window(realwindow),
lineHori(sf::Vector2f(800, 2)),
lineVert(sf::Vector2f(2, 800)),
square(sf::Vector2f(200, 200)),
neutralPiece(100,40)
{
	lineHori.setFillColor(sf::Color(0,0,0));
	lineVert.setFillColor(sf::Color(0,0,0));
	neutralPiece.setFillColor(sf::Color(150,150,150));
};

void Display::setBoard(std::vector<std::array<int,4>> newboard){
	board = newboard;
};

void Display::refresh(std::array<int,2> grabedpos){
	window.clear(sf::Color(255,255,255));
	bool drawgrabed = false;
	for(int y = 0;y<4;y++){
		for(int x = 0;x<4;x++){
			square.setPosition(x*200,y*200);
			switch(board[y][x]){
				case 0:
					break;
				case 1:
					square.setFillColor(sf::Color(200,70,30));
					window.draw(square);
					break;
				case 2:
					square.setFillColor(sf::Color(30,70,200));
					window.draw(square);
					break;
				case 3:
					neutralPiece.setPosition(x*200,y*200);
					window.draw(neutralPiece);
					break;
				case 4:
					drawgrabed = true;
					break;
			};
		};
	};
	// horizontal
	lineHori.setPosition(0,199);
	window.draw(lineHori);
	lineHori.setPosition(0,399);
	window.draw(lineHori);
	lineHori.setPosition(0,599);
	window.draw(lineHori);
	// vertical
	lineVert.setPosition(199,0);
	window.draw(lineVert);
	lineVert.setPosition(399,0);
	window.draw(lineVert);
	lineVert.setPosition(599,0);
	window.draw(lineVert);
	if(drawgrabed){
		neutralPiece.setPosition(grabedpos[0],grabedpos[1]);
		window.draw(neutralPiece);
	};
	window.display();
};




