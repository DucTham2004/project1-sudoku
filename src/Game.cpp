#include <SFML/Graphics.hpp> // Nếu bạn sử dụng các đối tượng như sf::RenderWindow, sf::RectangleShape
#include <SFML/Window.hpp>   // Nếu bạn sử dụng các đối tượng về cửa sổ hoặc event
#include <SFML/System.hpp>   // Nếu bạn dùng các chức năng hệ thống như sf::Clock, sf::Time
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
