#include <SFML/Graphics.hpp>
#include "Cell.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

const int windowWidth = 1000;
const int windowHeight = 1100;

const int bottomDivHeight = 100;
sf::RectangleShape bottomDiv;

const int cellWidth = windowWidth / 9;
const int cellHeight = (windowHeight - bottomDivHeight) / 9;

sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sudoku Solver Visualization");

sf::Text text;
sf::Font font;

// these two are used to select cell
std::pair<int, int> selectedCellCoords;
std::pair<int, int> prevSelectedCellCoords;

// create sudoku grid 9x9
std::vector<std::vector<Cell>> grid;

void init() {
    int width = 0, height = 0;
    if (!font.loadFromFile("arial.ttf"))
        std::cout << "Failed to load a font." << std::endl;

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
            cell.setFont(font);
            cell.text.setFillColor(sf::Color::White);
            cell.text.setCharacterSize(60);
            cell.text.setPosition(sf::Vector2f(width + (cellWidth / 2 - 15), height + 15));
            temp.emplace_back(cell);
            width += cellWidth;
        }
        grid.emplace_back(temp);
        height += cellHeight;
        width = 0;
    }
    bottomDiv.setSize(sf::Vector2f(windowWidth, bottomDivHeight));
    bottomDiv.setPosition(sf::Vector2f(0, height));
    bottomDiv.setFillColor(sf::Color(30, 30, 30));

    // use two variables to position number in every cell, make it string if needed
}

// renders grid
void draw() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            window.draw(grid[i][j].square);
            window.draw(grid[i][j].text);
        }
    }
    window.draw(bottomDiv);
}

bool canPlace(int row, int col, int num);
bool backtrack(int row, int col);

void updateInput() {
    sf::Event event;
    sf::Mouse mouse;
    sf::Vector2f mousecoords(window.mapPixelToCoords(sf::Vector2i(mouse.getPosition(window).x, mouse.getPosition(window).y)));
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    if (grid[i][j].square.getGlobalBounds().contains(mousecoords)) {
                        prevSelectedCellCoords.first = selectedCellCoords.first;
                        prevSelectedCellCoords.second = selectedCellCoords.second;
                        selectedCellCoords.first = i;
                        selectedCellCoords.second = j;
                        grid[prevSelectedCellCoords.first][prevSelectedCellCoords.second].square.setFillColor(sf::Color(30, 30, 30));
                        grid[i][j].square.setFillColor(sf::Color(60, 60, 60));
                    }
                }
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code >= 27 && event.key.code <= 35) {
                std::string temp = std::to_string(event.key.code - 26);
                grid[selectedCellCoords.first][selectedCellCoords.second].text.setString(temp);
                grid[selectedCellCoords.first][selectedCellCoords.second].setNumber(stoi(temp));
            }
            if (event.key.code == sf::Keyboard::D) {
                grid[selectedCellCoords.first][selectedCellCoords.second].text.setString("");
                grid[selectedCellCoords.first][selectedCellCoords.second].setNumber(0);
            }
            if (event.key.code == sf::Keyboard::S)
                backtrack(0, 0);
        }
    }
}

void visualize() {
    window.clear();
    draw();
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
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
        updateInput();
        window.display();
	}

    return 0;
}

bool canPlace(int row, int col, int num) {
    // check every row
    for (int i = 0; i < 9; i++)
        if (grid[row][i].getNumber() == num)
            return false;

    // check every col
    for (int i = 0; i < 9; i++)
        if (grid[i][col].getNumber() == num)
            return false;

    // check every box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol].getNumber() == num)
                return false;
    return true;
}

bool backtrack(int row, int col) {
    if (row == grid.size() - 1 && col == grid[row].size())
        return true;

    if (col == 9) {
        row++;
        col = 0;
    }

    if (grid[row][col].getNumber() > 0)
        return backtrack(row, col + 1);

    for (int i = 1; i <= 9; i++) {
        if (canPlace(row, col, i)) {
            grid[row][col].setNumber(i);
            grid[row][col].text.setString(std::to_string(i));
            visualize();
            if (backtrack(row, col + 1))
                return true;
        }
        grid[row][col].setNumber(0);
        grid[row][col].text.setString("");
    }

    return false;
}