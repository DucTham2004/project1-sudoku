#include "Game.hpp"

Game::Game() : state(StartScreen), totalPausedTime(sf::Time::Zero) {}

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

            if (state == StartScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    state = DifficultySelection;
                }
            }
            else if (state == DifficultySelection && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    grid.generate(20);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(40);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(60);
                    gameClock.restart();
                    state = Playing;
                }
            }
            else if (state == Playing && grid.checkWin())
            {
                state = CongratulationScreen;
                grid.numberError = 0;
                grid.selectedCol = -1;
                grid.selectedRow = -1;
                grid.currentScore = 0;
            }
            else if (state == Playing && grid.checkLose())
            {
                state = LoseScreen;
                grid.numberError = 0;
                grid.selectedCol = -1;
                grid.selectedRow = -1;
                grid.currentScore = 0;
            }
            else if (state == Playing && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                pauseStartTime = gameClock.getElapsedTime();
                state = Pause;
            }
            else if (state == Pause && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                totalPausedTime += gameClock.getElapsedTime() - pauseStartTime;
                state = Playing;
            }
            else if (state == CongratulationScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    grid.generate(20);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(40);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(60);
                    gameClock.restart();
                    state = Playing;
                }
            }
            else if (state == LoseScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    grid.generate(20);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(40);
                    gameClock.restart();
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(60);
                    gameClock.restart();
                    state = Playing;
                }
            }
        }
        if (state == Playing)
            elapsedTime = gameClock.getElapsedTime() - totalPausedTime;

        window.clear(sf::Color::White);

        if (state == StartScreen)
            drawStartScreen(window);
        else if (state == DifficultySelection)
            drawDifficultySelection(window);
        else if (state == Playing)
        {
            input.processMouse(window, grid);
            input.processKeyboard(grid);
            grid.draw(window);
            drawTimer(window, elapsedTime);
            drawScore(window);
            drawNumberError(window);
        }
        else if (state == Pause)
        {
            drawPauseScreen(window);
            drawTimer(window, elapsedTime);
        }
        else if (state == CongratulationScreen)
            drawCongratulationScreen(window);
        else if (state == LoseScreen)
            drawLoseScreen(window);

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

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Select Difficulty", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 200);
    easy.setFillColor(sf::Color::Black);
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 250);
    medium.setFillColor(sf::Color::Black);
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 300);
    hard.setFillColor(sf::Color::Black);
    window.draw(hard);
}

void Game::drawCongratulationScreen(sf::RenderWindow &window)
{

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Congratulations, you have won!", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 200);
    easy.setFillColor(sf::Color::Black);
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 250);
    medium.setFillColor(sf::Color::Black);
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 300);
    hard.setFillColor(sf::Color::Black);
    window.draw(hard);
}

void Game::drawLoseScreen(sf::RenderWindow &window)
{

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("You lost!", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 200);
    easy.setFillColor(sf::Color::Black);
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 250);
    medium.setFillColor(sf::Color::Black);
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 300);
    hard.setFillColor(sf::Color::Black);
    window.draw(hard);
}

void Game::drawPauseScreen(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Game Paused", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    sf::Text resume("Press 'p' to Resume", font, 30);
    resume.setPosition(800 / 2 - resume.getGlobalBounds().width / 2, 200);
    resume.setFillColor(sf::Color::Black);
    window.draw(resume);
}

void Game::drawTimer(sf::RenderWindow &window, sf::Time elapsedTime)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;

    std::ostringstream timerText;
    timerText << "Time: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;

    sf::Text timer(timerText.str(), font, 30);
    timer.setFillColor(sf::Color::Black);
    timer.setPosition(10, 10);

    window.draw(timer);
}

void Game::drawScore(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(grid.currentScore));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(200, 10);

    window.draw(scoreText);
}

void Game::drawNumberError(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text numberErrorText;
    numberErrorText.setFont(font);
    numberErrorText.setString("Eror: " + std::to_string(grid.numberError) + "/3");
    numberErrorText.setCharacterSize(30);
    numberErrorText.setFillColor(sf::Color::Black);
    numberErrorText.setPosition(400, 10);

    window.draw(numberErrorText);
}
