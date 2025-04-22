#ifndef INPUTS_H
#define INPUTS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <tuple>

class Inputs
{
	public:
		Inputs(sf::RenderWindow& win,std::vector<std::array<int,4>> firstboard);
		std::tuple<std::vector<std::array<int,4>>,bool> draw();
		void setBoard(std::vector<std::array<int,4>> newboard);
		std::vector<std::array<int,4>> getBoard();
		std::tuple<std::vector<std::array<int,4>>,std::array<int,2>,bool> drag();

	protected:
		std::array<int,2> getPos();
		bool isLShape();
		sf::RenderWindow& window;
		bool tour = true;
		bool lmoved = false;
		bool drawing = false;
		bool mousepressed = false;
		bool grabing = false;
		std::vector<std::array<int,4>> initialboard;
		std::vector<std::array<int,4>> realboard;
		std::vector<std::array<int,4>> board;
		std::vector<std::array<int,2>> drawingpos;
		std::array<int,2> offset;
		std::array<int,2> grabedpos;
};

#endif
