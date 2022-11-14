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

void Cell::setRow(int row) {
	this->row = row;
}

void Cell::setCol(int col) {
	this->col = col;
}