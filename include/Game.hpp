#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "Grid.hpp"
#include "Input.hpp"

class Game
{
private:
    Grid grid;
    Input input;

public:
    Game();
    void run();
};

#endif
