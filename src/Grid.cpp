#include "Grid.hpp"
#include <iostream>

Grid::Grid() : grid(9, std::vector<int>(9, 0)) {}

void Grid::generate()
{
    // Tạo lưới Sudoku cơ bản (tạm thời có thể tạo lưới tĩnh)
    grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};
}

bool Grid::isValidMove(int row, int col, int num)
{
    return grid[row][col] == 0 && isSafe(row, col, num);
}

void Grid::setValue(int row, int col, int value)
{
    grid[row][col] = value;
}

int Grid::getValue(int row, int col) const
{
    return grid[row][col];
}

void Grid::print() const
{
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << " ";
        }
        std::cout << "\n";
    }
}

bool Grid::isSafe(int row, int col, int num)
{
    // Kiểm tra hàng
    for (int i = 0; i < 9; i++)
        if (grid[row][i] == num)
            return false;

    // Kiểm tra cột
    for (int i = 0; i < 9; i++)
        if (grid[i][col] == num)
            return false;

    // Kiểm tra ô vuông 3x3
    int startRow = row / 3 * 3;
    int startCol = col / 3 * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

void Grid::draw(sf::RenderWindow &window)
{

    sf::RectangleShape cell(sf::Vector2f(50, 50));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cell.setPosition(i * 50, j * 50);
            window.draw(cell);
        }
    }
}
