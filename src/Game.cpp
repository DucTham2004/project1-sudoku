#include "Game.hpp"

Game::Game() : state(StartScreen) {} // Trạng thái khởi tạo là StartScreen

void Game::run()
{
    grid.generate();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Xử lý chuyển trạng thái
            if (state == StartScreen && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                state = Playing; // Bắt đầu chơi khi nhấn Enter
            }
        }

        window.clear(sf::Color::White);

        if (state == StartScreen)
        {
            drawStartScreen(window);
        }
        else if (state == Playing)
        {
            input.processMouse(window, grid);
            input.processKeyboard(grid);
            grid.draw(window);
        }

        window.display();
    }
}

void Game::drawStartScreen(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Welcome to Sudoku!", font, 50);
    title.setFillColor(sf::Color::Black);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 150);

    sf::Text instructions("Press Enter to Start", font, 30);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(800 / 2 - instructions.getGlobalBounds().width / 2, 300);

    window.draw(title);
    window.draw(instructions);
}
