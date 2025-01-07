#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "Grid.hpp"
#include "Input.hpp"
#include <sstream>

class Game
{
public:
    Grid grid;
    Input input;
    sf::Clock gameClock;
    sf::Time elapsedTime;
    sf::Time totalPausedTime;
    sf::Time pauseStartTime;

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
    void drawTimer(sf::RenderWindow &window, sf::Time elapsedTime);
    void drawScore(sf::RenderWindow &window);
    void drawNumberError(sf::RenderWindow &window);
    Game();
    void run();
};

#endif
