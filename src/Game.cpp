#include "Game.hpp"

Game::Game() : state(StartScreen), totalPausedTime(sf::Time::Zero)
{
    loadHighScoresFromFile();
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
}

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
            {
                saveHighScoresToFile();
                window.close();
            }

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
                    grid.generate(3);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(4);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(6);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
            }
            else if (state == Playing && grid.checkWin())
            {
                state = CongratulationScreen;
                grid.numberError = 0;
                grid.selectedCol = -1;
                grid.selectedRow = -1;
                addHighScore(grid.currentScore, elapsedTime);
                grid.currentScore = 0;
            }
            else if (state == Playing && grid.checkLose())
            {
                state = LoseScreen;
                grid.numberError = 0;
                grid.selectedCol = -1;
                grid.selectedRow = -1;
                addHighScore(grid.currentScore, elapsedTime);
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
                    grid.generate(3);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(4);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(6);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
            }
            else if (state == LoseScreen && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    grid.generate(3);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    grid.generate(4);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    grid.generate(6);
                    gameClock.restart();
                    totalPausedTime = sf::Time::Zero;
                    state = Playing;
                }
            }
        }

        window.clear(sf::Color::White);

        if (state == StartScreen)
        {
            drawStartScreen(window);
            drawHighScores(window);
        }
        else if (state == DifficultySelection)
            drawDifficultySelection(window);
        else if (state == Playing)
        {
            elapsedTime = gameClock.getElapsedTime() - totalPausedTime;
            input.processMouse(window, grid);
            input.processKeyboard(grid);
            grid.draw(window);
            drawTimer(window, elapsedTime);
            drawScore(window);
            drawNumberError(window);
            drawShortcutKey(window);
        }
        else if (state == Pause)
        {
            drawPauseScreen(window);
            drawTimer(window, elapsedTime);
            drawScore(window);
            drawNumberError(window);
        }
        else if (state == CongratulationScreen)
        {
            drawCongratulationScreen(window);
            drawHighScores(window);
        }
        else if (state == LoseScreen)
        {
            drawLoseScreen(window);
            drawHighScores(window);
        }

        window.display();
    }
}

void Game::drawStartScreen(sf::RenderWindow &window)
{
    sf::Font font;
    sf::Font font2;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
    font2.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf");

    sf::Text title("Welcome to Sudoku!", font, 50);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 10);

    sf::Text instructions("Press Enter to Start", font2, 30);
    instructions.setFillColor(sf::Color(52, 72, 97, 255));
    instructions.setPosition(800 / 2 - instructions.getGlobalBounds().width / 2, 500);

    window.draw(title);
    window.draw(instructions);
}

void Game::drawDifficultySelection(sf::RenderWindow &window)
{
    sf::Text title("Select Difficulty", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 400);
    easy.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 450);
    medium.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 500);
    hard.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(hard);
}

void Game::drawCongratulationScreen(sf::RenderWindow &window)
{

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Congratulations, you have won!", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 30);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 400);
    easy.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 450);
    medium.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 500);
    hard.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(hard);
}

void Game::drawLoseScreen(sf::RenderWindow &window)
{

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("You lost!", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 30);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);

    sf::Text easy("1. Easy", font, 30);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 400);
    easy.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 30);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 450);
    medium.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 30);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 500);
    hard.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(hard);
}

void Game::drawPauseScreen(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Game Paused", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);

    sf::Text resume("Press 'p' to Resume", font, 30);
    resume.setPosition(800 / 2 - resume.getGlobalBounds().width / 2, 200);
    resume.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(resume);
}

void Game::drawTimer(sf::RenderWindow &window, sf::Time elapsedTime)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;

    std::ostringstream timerText;
    timerText << "Time: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;

    sf::Text timer(timerText.str(), font, 24);
    timer.setFillColor(sf::Color(52, 72, 97, 255));
    timer.setPosition(10, 10);

    window.draw(timer);
}

void Game::drawScore(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(grid.currentScore));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(52, 72, 97, 255));
    scoreText.setPosition(200, 10);

    window.draw(scoreText);
}

void Game::drawNumberError(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text numberErrorText;
    numberErrorText.setFont(font);
    numberErrorText.setString("Eror: " + std::to_string(grid.numberError) + "/3");
    numberErrorText.setCharacterSize(24);
    numberErrorText.setFillColor(sf::Color(52, 72, 97, 255));
    numberErrorText.setPosition(400, 10);

    window.draw(numberErrorText);
}

void Game::addHighScore(int score, sf::Time playTime)
{

    highScores.push_back({score, playTime});

    std::sort(highScores.begin(), highScores.end(), [](const Record &a, const Record &b)
              { return a.score > b.score; });

    if (highScores.size() > 3)
        highScores.pop_back();
}

void Game::drawHighScores(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("High Scores", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);

    for (int i = 0; i < highScores.size(); ++i)
    {
        std::ostringstream highScoreText;
        highScoreText << "Top " << i + 1 << ": " << highScores[i].score << " - " << round(highScores[i].playTime.asSeconds()) << "s";

        sf::Text highScore(highScoreText.str(), font, 30);
        highScore.setFillColor(sf::Color(52, 72, 97, 255));
        highScore.setPosition(800 / 2 - highScore.getGlobalBounds().width / 2, 200 + i * 50);
        window.draw(highScore);
    }
}

void Game::saveHighScoresToFile()
{
    std::ofstream file("E:/project1_sudoku/project1-sudoku/assets/scores/highscores.txt");

    if (!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    for (const auto &record : highScores)
    {
        file << record.score << " " << record.playTime.asSeconds() << std::endl;
    }

    file.close();
}

void Game::loadHighScoresFromFile()
{
    std::ifstream file("E:/project1_sudoku/project1-sudoku/assets/scores/highscores.txt");

    if (!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    highScores.clear();

    int score;
    float playTime;
    while (file >> score >> playTime)
    {
        highScores.push_back({score, sf::seconds(playTime)});
    }

    file.close();
}

void Game::drawShortcutKey(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Shortcut Key:        N: Note      P: Pause      Backspace: Delete", font, 24);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 550);
    title.setFillColor(sf::Color(52, 72, 97, 255));
    window.draw(title);
}
