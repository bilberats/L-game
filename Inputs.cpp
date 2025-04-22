#include "Inputs.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <tuple>

Inputs::Inputs(sf::RenderWindow& win,std::vector<std::array<int,4>> firstboard)
:window(win),
board(firstboard),
initialboard(firstboard)
{
};

void Inputs::setBoard(std::vector<std::array<int,4>> newboard){
	realboard = newboard;
};

std::vector<std::array<int,4>> Inputs::getBoard(){
	return board;
};

std::array<int,2> Inputs::getPos(){
	std::array<int,2> pos;
	sf::Vector2<int> mousepos = sf::Mouse::getPosition(window);
	if((mousepos.x>0 && mousepos.x<800) && (mousepos.y>0 &&mousepos.y<800)){
        pos[0] = mousepos.y/200;
        pos[1] = mousepos.x/200;
	}
	else{
        return {{-1,-1}};
	};
	return pos;
};

std::tuple<std::vector<std::array<int,4>>,bool> Inputs::draw(){
	bool correct = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
        board = initialboard;
        tour = true;
		lmoved = false;
		return std::make_tuple(board,true);
    };
	if(!lmoved){
		int color;
		if(tour){
			color = 1;
		}
		else{
			color = 2;
		};
		std::array<int,2> pos;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			if(!mousepressed){
				for(int y = 0;y<4;y++){
					for(int x = 0;x<4;x++){
						if(board[y][x] == color){
							board[y][x] = 0;
						};
					};
				};
				drawingpos.clear();
				mousepressed = true;
				drawing = true;
			};
			pos = getPos();
            std::array<int,2> posnot = {{-1,-1}};
			if((pos != posnot) && (board[pos[0]][pos[1]] == 0)){
				board[pos[0]][pos[1]] = color;
				drawingpos.push_back(pos);
			};
		}
		else{
			if(mousepressed){
				if(board != realboard){
					if(isLShape()){
						correct = true;
						lmoved = true;
					}
					else{
						board = realboard;
					};
				};
			};
			mousepressed = false;
			drawing = false;
		};
	};
	return std::make_tuple(board,correct);
};

std::tuple<std::vector<std::array<int,4>>,std::array<int,2>,bool> Inputs::drag(){
	bool moved = false;
	if(lmoved){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
			for(int y = 0;y<4;y++){
				for(int x = 0;x<4;x++){
					if(board[y][x] == 4){
						board[y][x] = 3;
					};
				};
			};
			moved = true;
			lmoved = false;
			tour = !tour;
			mousepressed = false;
			grabing = false;
			return std::make_tuple(board,grabedpos,moved);
		};
		std::array<int,2> pos = getPos();
		std::array<int,2> posnot = {{-1,-1}};
		sf::Vector2<int> mousepos = sf::Mouse::getPosition(window);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			if(!mousepressed){
				if((pos != posnot) &&(board[pos[0]][pos[1]] == 3)){
					board[pos[0]][pos[1]] = 4;
					grabing = true;
					offset = {{mousepos.y-(pos[0]*200),mousepos.x-(pos[1]*200)}};
					mousepressed = true;
				};
			};
			if(grabing){
				grabedpos = {{mousepos.x-offset[1],mousepos.y-offset[0]}};
			};
		}
		else{
			if(mousepressed){
				if((pos != posnot) && (board[pos[0]][pos[1]] == 0)){
					board[pos[0]][pos[1]] = 3;
					for(int y = 0;y<4;y++){
						for(int x = 0;x<4;x++){
							if(board[y][x] == 4){
								board[y][x] = 0;
							};
						};
					};
					moved = true;
					lmoved = false;
					tour = !tour;
				}
				else{
					board = realboard;
				};
			};
			mousepressed = false;
			grabing = false;
		};
	};
	return std::make_tuple(board,grabedpos,moved);
};

bool Inputs::isLShape(){
	if(drawingpos.size() == 4){
		std::vector<std::array<int,2>> relpostest;
		std::array<int,2> firstpos = drawingpos[0];
		for(int i = 1;i<4;i++){
			std::array<int,2> relpos = {drawingpos[i][0]-firstpos[0],drawingpos[i][1]-firstpos[1]};
			relpostest.push_back(relpos);
		};

		std::vector<std::array<int,2>> gauchehautinverted =
		{
			{0,1},
			{1,1},
			{2,1}
		};
		std::vector<std::array<int,2>> gauchebasinverted =
		{
			{0,-1},
			{1,-1},
			{2,-1}
		};
		std::vector<std::array<int,2>> droitehautinverted =
		{
			{0,1},
			{-1,1},
			{-2,1}
		};
		std::vector<std::array<int,2>> droitebasinverted =
		{
			{0,-1},
			{-1,-1},
			{-2,-1}
		};
		std::vector<std::array<int,2>> hautgaucheinverted =
		{
			{1,0},
			{1,1},
			{1,2}
		};
		std::vector<std::array<int,2>> hautdroiteinverted =
		{
			{-1,0},
			{-1,1},
			{-1,2}
		};
		std::vector<std::array<int,2>> basgaucheinverted =
		{
			{1,0},
			{1,-1},
			{1,-2}
		};
		std::vector<std::array<int,2>> basdroiteinverted =
		{
			{-1,0},
			{-1,-1},
			{-1,-2}
		};

		/* not inverted */
		std::vector<std::array<int,2>> gauchehaut =
		{
			{-1,0},
			{-2,0},
			{-2,-1}
		};
		std::vector<std::array<int,2>> gauchebas =
		{
			{-1,0},
			{-2,0},
			{-2,1}
		};
		std::vector<std::array<int,2>> droitehaut =
		{
			{1,0},
			{2,0},
			{2,-1}
		};
		std::vector<std::array<int,2>> droitebas =
		{
			{1,0},
			{2,0},
			{2,1}
		};
		std::vector<std::array<int,2>> hautgauche =
		{
			{0,-1},
			{0,-2},
			{-1,-2}
		};
		std::vector<std::array<int,2>> hautdroite =
		{
			{0,-1},
			{0,-2},
			{1,-2}
		};
		std::vector<std::array<int,2>> basgauche =
		{
			{0,1},
			{0,2},
			{-1,2}
		};
		std::vector<std::array<int,2>> basdroite =
		{
			{0,1},
			{0,2},
			{1,2}
		};
		if(relpostest == gauchehautinverted){
			return true;
		}
		else if(relpostest == gauchebasinverted){
			return true;
		}
		else if(relpostest == droitehautinverted){
			return true;
		}
		else if(relpostest == droitebasinverted){
			return true;
		}
		else if(relpostest == hautgaucheinverted){
			return true;
		}
		else if(relpostest == hautdroiteinverted){
			return true;
		}
		else if(relpostest == basgaucheinverted){
			return true;
		}
		else if(relpostest == basdroiteinverted){
			return true;
		}
		/* not inverted */
		else if(relpostest == gauchehaut){
			return true;
		}
		else if(relpostest == gauchebas){
			return true;
		}
		else if(relpostest == droitehaut){
			return true;
		}
		else if(relpostest == droitebas){
			return true;
		}
		else if(relpostest == hautgauche){
			return true;
		}
		else if(relpostest == hautdroite){
			return true;
		}
		else if(relpostest == basgauche){
			return true;
		}
		else if(relpostest == basdroite){
			return true;
		}
		else{
			return false;
		};
	};
	return false;
};







