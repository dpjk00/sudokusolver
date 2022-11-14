#pragma once

#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell();
	~Cell();
	Cell(int row, int col);
	int getRow();
	int getCol();
	void setRow(int row);
	void setCol(int col);
public:
	sf::RectangleShape square;

private:
	int row;
	int col;
};

