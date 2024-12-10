#include "Game.hpp"

Game::Game() : state(StartScreen) {} // Trạng thái khởi tạo là StartScreen

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");
    state = StartScreen;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Xử lý logic theo trạng thái
            if (state == StartScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    state = DifficultySelection; // Chuyển sang trạng thái chọn mức độ khó
                }
            }
            else if (state == DifficultySelection && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1) // Easy
                {
                    grid.generate(1); // 20 ô trống cho dễ
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2) // Medium
                {
                    grid.generate(40); // 40 ô trống cho trung bình
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3) // Hard
                {
                    grid.generate(60); // 60 ô trống cho khó
                    state = Playing;
                }
            }
            else if (state == Playing && grid.checkWin())
            {
                state = CongratulationScreen;
            }
            else if (state == CongratulationScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1) // Easy
                {
                    grid.generate(20); // 20 ô trống cho dễ
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2) // Medium
                {
                    grid.generate(40); // 40 ô trống cho trung bình
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3) // Hard
                {
                    grid.generate(60); // 60 ô trống cho khó
                    state = Playing;
                }
            }
        }

        window.clear(sf::Color::White);

        // Vẽ giao diện dựa trên trạng thái
        if (state == StartScreen)
            drawStartScreen(window);
        else if (state == DifficultySelection)
            drawDifficultySelection(window);
        else if (state == Playing)
        {
            input.processMouse(window, grid);
            input.processKeyboard(grid);
            grid.draw(window);
        }
        else if (state == CongratulationScreen)
            drawCongratulationScreen(window);

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

void Game::drawDifficultySelection(sf::RenderWindow &window)
{
    // Tạo các thành phần giao diện
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Tiêu đề
    sf::Text title("Select Difficulty", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    // Mức độ dễ
    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 200);
    easy.setFillColor(sf::Color::Black);
    window.draw(easy);

    // Mức độ trung bình
    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 250);
    medium.setFillColor(sf::Color::Black);
    window.draw(medium);

    // Mức độ khó
    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 300);
    hard.setFillColor(sf::Color::Black);
    window.draw(hard);
}

void Game::drawCongratulationScreen(sf::RenderWindow &window)
{
    // Tạo các thành phần giao diện
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Tiêu đề
    sf::Text title("Congratulations, you have won!", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    // Mức độ dễ
    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 200);
    easy.setFillColor(sf::Color::Black);
    window.draw(easy);

    // Mức độ trung bình
    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 250);
    medium.setFillColor(sf::Color::Black);
    window.draw(medium);

    // Mức độ khó
    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 300);
    hard.setFillColor(sf::Color::Black);
    window.draw(hard);
}