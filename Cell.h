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
	int getNumber();
	int getDistWidth();
	int getDistHeight();
	void setRow(int row);
	void setCol(int col);
	void setNumber(int number);
	void setDistWidth(int dist);
	void setDistHeight(int dist);
	void setFont(sf::Font& font);
public:
	sf::RectangleShape square;
	sf::Text text;

private:
	int row;
	int col;
	int number;
	bool canModify;

	int distWidth;
	int distHeight;
};

