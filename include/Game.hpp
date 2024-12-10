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
    enum GameState
    {
        StartScreen,
        DifficultySelection, // Trạng thái chọn mức độ khó
        Playing
    };
    GameState state;
    void drawStartScreen(sf::RenderWindow &window);
    void drawDifficultySelection(sf::RenderWindow &window);

public:
    Game();
    void run();
};

#endif
