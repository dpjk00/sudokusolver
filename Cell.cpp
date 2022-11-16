#include "Cell.h"

Cell::Cell() {}
Cell::~Cell() {}

Cell::Cell(int row, int col) {
	this->row = row;
	this->col = col;
}

int Cell::getRow() {
	return row;
}

int Cell::getCol() {
	return col;
}

int Cell::getNumber() {
	return number;
}

int Cell::getDistWidth() {
	return distWidth;
}

int Cell::getDistHeight() {
	return distHeight;
}

void Cell::setRow(int row) {
	this->row = row;
}

void Cell::setCol(int col) {
	this->col = col;
}

void Cell::setNumber(int number) {
	this->number = number;
}

void Cell::setDistWidth(int dist) {
	distWidth = dist;
}

void Cell::setDistHeight(int dist) {
	distHeight = dist;
}

void Cell::setFont(sf::Font& font) {
	text.setFont(font);
}