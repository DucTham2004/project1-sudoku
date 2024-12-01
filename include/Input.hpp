#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Input
{
public:
    void processMouse(sf::RenderWindow &window, Grid &grid);
    void processKeyboard(Grid &grid);
};

#endif
