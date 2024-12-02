#include "Game.hpp"

Game::Game() {}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        input.processMouse(window, grid);
        input.processKeyboard(grid);
        grid.generate();
        window.clear(sf::Color::White);
        grid.draw(window);

        window.display();
    }
}
