#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Grid
{
private:
    std::vector<std::vector<int>> board;

public:
    Grid();
    void draw(sf::RenderWindow &window);        // Vẽ lưới
    void fillCell(int row, int col, int value); // Điền giá trị vào ô
};

#endif
