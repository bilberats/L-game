#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.h"
#include "Inputs.h"
#include <array>
#include <vector>
#include <tuple>


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML shapes", sf::Style::Default, settings);
	Display screen(window);
	
	std::vector<std::array<int,4>> board;
	std::vector<std::array<int,4>> displayboard;
	//board = model.getBoard();
	board = 
	{
		{3,2,2,0},
		{0,1,2,0},
		{0,1,2,0},
		{0,1,1,3}
	};
	Inputs player(window,board);
	
	displayboard = board;
	screen.setBoard(displayboard);
	player.setBoard(board);
	bool neutralmoved = false;
	bool lmoved = false;
	
	std::array<int,2> grabedpos = {{0,0}};
    sf::CircleShape shape(400, 100);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.setBoard(board);
		std::tie(displayboard,lmoved) = player.draw();
		if(lmoved){
			board = displayboard;
		};
		std::tie(displayboard,grabedpos,neutralmoved) = player.drag();
		if(neutralmoved){
			board = displayboard;
		};
		screen.setBoard(displayboard);
		
        window.clear();
        screen.refresh(grabedpos);
        window.display();
    }
	
    return 0;		
};
