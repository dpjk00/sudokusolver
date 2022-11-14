#include <SFML/Graphics.hpp>
#include "Cell.h"

#include <iostream>

const int windowWidth = 1000;
const int windowHeight = 1100;

const int bottomDivHeight = 100;
sf::RectangleShape bottomDiv;

const int cellWidth = windowWidth / 9;
const int cellHeight = (windowHeight - bottomDivHeight) / 9;

sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sudoku Solver Visualization");

// create sudoku grid 9x9
std::vector<std::vector<Cell>> grid;

void init() {
    int width = 0, height = 0;
    // initialize grid
    for (int i = 0; i < 9; i++) {
        std::vector<Cell> temp;
        for (int j = 0; j < 9; j++) {
            Cell cell;
            cell.square.setSize(sf::Vector2f(cellWidth, cellHeight));
            cell.square.setPosition(sf::Vector2f(width, height));
            cell.square.setFillColor(sf::Color(30, 30, 30));
            cell.square.setOutlineColor(sf::Color(80, 80, 80));
            cell.square.setOutlineThickness(-1);
            temp.emplace_back(cell);
            width += cellWidth;
        }
        grid.emplace_back(temp);
        height += cellHeight;
        width = 0;
    }
    bottomDiv.setPosition(sf::Vector2f(0, height));
    bottomDiv.setSize(sf::Vector2f(windowWidth, bottomDivHeight));
    bottomDiv.setFillColor(sf::Color(43, 111, 43));
}

// renders grid
void draw() {
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            window.draw(grid[i][j].square);
}

int main() {
    init();
	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        draw();
        window.display();
	}

    return 0;
}