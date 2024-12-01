#include "Input.hpp"
#include "Grid.hpp"

void Input::processMouse(sf::RenderWindow &window, Grid &grid)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int row = mousePos.y / cellSize; // cellSize: kích thước 1 ô
        int col = mousePos.x / cellSize;

        // Kiểm tra nếu click trong lưới
        if (row >= 0 && row < 9 && col >= 0 && col < 9)
        {
            grid.selectCell(row, col); // Chọn ô (giả sử có hàm selectCell trong Grid)
        }
    }
}

void Input::processKeyboard(Grid &grid)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        grid.setCellValue(1); // Đặt giá trị 1 vào ô được chọn
    }
    // Tương tự cho các phím từ Num2 đến Num9
}
