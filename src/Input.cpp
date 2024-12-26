#include "Input.hpp"

const int cellSize = 50;
const int offsetX = 175;
const int offsetY = 75;

void Input::processMouse(sf::RenderWindow &window, Grid &grid)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int row = (mousePos.y - offsetY) / cellSize;
        int col = (mousePos.x - offsetX) / cellSize;

        if (row >= 0 && row < 9 && col >= 0 && col < 9)
        {
            grid.selectCell(row, col);
        }
    }
}

void Input::processKeyboard(Grid &grid)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        grid.setCellValue(1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        grid.setCellValue(2);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        grid.setCellValue(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        grid.setCellValue(4);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        grid.setCellValue(5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        grid.setCellValue(6);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
    {
        grid.setCellValue(7);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
    {
        grid.setCellValue(8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
    {
        grid.setCellValue(9);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
    {
        grid.setCellValue(0);
    }
}
