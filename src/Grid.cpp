#include "Grid.hpp"

Grid::Grid() : board(9, std::vector<int>(9, 0)) {}

void Grid::draw(sf::RenderWindow &window)
{
}

void Grid::fillCell(int row, int col, int value)
{
    board[row][col] = value;
}
