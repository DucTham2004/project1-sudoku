#include "Game.hpp"
#include "Grid.hpp"

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

        window.clear();
        grid.draw(window);
        window.display();
    }
}
