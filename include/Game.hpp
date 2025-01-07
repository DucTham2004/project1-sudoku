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
public:
    Grid grid;
    Input input;
    sf::Clock gameClock;
    sf::Time elapsedTime;
    enum GameState
    {
        StartScreen,
        DifficultySelection,
        Playing,
        Pause,
        CongratulationScreen,
        LoseScreen
    };
    GameState state;
    void drawStartScreen(sf::RenderWindow &window);
    void drawDifficultySelection(sf::RenderWindow &window);
    void drawCongratulationScreen(sf::RenderWindow &window);
    void drawLoseScreen(sf::RenderWindow &window);
    void drawPauseScreen(sf::RenderWindow &window);
    Game();
    void run();
};

#endif
