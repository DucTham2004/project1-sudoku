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

    // Tải font chữ một lần
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return; // Nếu không tải được font, thoát khỏi hàm
    }

    // Tính toán vị trí bắt đầu của lưới để căn giữa
    float offsetX = (800 - 450) / 2; // Tính toán khoảng cách để căn giữa theo chiều ngang
    float offsetY = (600 - 450) / 2; // Tính toán khoảng cách để căn giữa theo chiều dọc

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            // Đặt vị trí các ô trong lưới để căn giữa
            cell.setPosition(offsetX + j * 50, offsetY + i * 50);

            window.draw(cell);

            // Hiển thị số trong lưới
            if (grid[i][j] != 0)
            {
                sf::Text number(std::to_string(grid[i][j]), font, 30);           // Đặt kích thước chữ lớn hơn
                number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6); // Điều chỉnh vị trí
                number.setFillColor(sf::Color::Black);
                window.draw(number);
            }
        }
    }

    sf::RectangleShape lineRow(sf::Vector2f(450, 3));
    lineRow.setFillColor(sf::Color::Black);
    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            lineRow.setPosition(offsetX, offsetY + i * 50); // Đặt vị trí của đoạn thẳng
            window.draw(lineRow);                           // Vẽ đoạn thẳng
        }
    }

    sf::RectangleShape lineCol(sf::Vector2f(3, 450));
    lineCol.setFillColor(sf::Color::Black);
    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            lineCol.setPosition(offsetX + i * 50, offsetY); // Đặt vị trí của đoạn thẳng
            window.draw(lineCol);                           // Vẽ đoạn thẳng
        }
    }

    // Vẽ ô được chọn
    if (selectedRow != -1 && selectedCol != -1)
    {
        sf::RectangleShape highlight(sf::Vector2f(50, 50));
        highlight.setPosition(offsetX + selectedCol * 50, offsetY + selectedRow * 50);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineColor(sf::Color::Red);
        highlight.setOutlineThickness(3);
        window.draw(highlight);
    }
}

void Grid::selectCell(int row, int col)
{
    if (row >= 0 && row < 9 && col >= 0 && col < 9)
    {
        selectedRow = row;
        selectedCol = col;
    }
}

void Grid::setCellValue(int value)
{
    if (selectedRow >= 0 && selectedRow < 9 && selectedCol >= 0 && selectedCol < 9)
    {
        if (grid[selectedRow][selectedCol] == 0)
            grid[selectedRow][selectedCol] = value;
    }
}
