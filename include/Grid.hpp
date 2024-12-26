#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

class Grid
{
public:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> isEditable;
    Grid();
    void generate(int cellsToRemove);
    void draw(sf::RenderWindow &window);
    void selectCell(int row, int col);
    void setCellValue(int value);
    bool fillGrid();
    bool isSafe(int row, int col, int num);
    bool checkWin();
    bool checkLose();
    int selectedRow = -1;
    int selectedCol = -1;
    int numberError = 0;
};

#endif
