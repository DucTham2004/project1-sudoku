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
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(240, 248, 255));
    window.draw(background);

    sf::RectangleShape headerBar(sf::Vector2f(800, 120));
    headerBar.setFillColor(sf::Color(70, 130, 180));
    headerBar.setPosition(0, 40);
    window.draw(headerBar);

    sf::Text title("Welcome to Sudoku!", font, 72);
    title.setFillColor(sf::Color::White);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 60);

    sf::Text subtitle("Challenge Your Mind", font, 36);
    subtitle.setFillColor(sf::Color(52, 73, 94));
    subtitle.setPosition(800 / 2 - subtitle.getGlobalBounds().width / 2, 250);

    sf::Text instructions("Press Enter to Start", font, 48);
    instructions.setFillColor(sf::Color(46, 204, 113));
    instructions.setPosition(800 / 2 - instructions.getGlobalBounds().width / 2, 400);

    window.draw(title);
    window.draw(subtitle);
    window.draw(instructions);
}

void Game::drawDifficultySelection(sf::RenderWindow &window)
{

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(240, 248, 255));
    window.draw(background);

    sf::RectangleShape headerBar(sf::Vector2f(800, 80));
    headerBar.setFillColor(sf::Color(70, 130, 180));
    headerBar.setPosition(0, 60);
    window.draw(headerBar);

    sf::Text title("Select Difficulty", font, 60);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 70);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    sf::Text easy("1. Easy", font, 36);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 220);
    easy.setFillColor(sf::Color(46, 139, 87));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 36);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 300);
    medium.setFillColor(sf::Color(70, 130, 180));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 36);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 380);
    hard.setFillColor(sf::Color(178, 34, 34));
    window.draw(hard);
}

void Game::drawCongratulationScreen(sf::RenderWindow &window)
{

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(240, 248, 255));
    window.draw(background);

    sf::Text title("Congratulations!", font, 72);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 80);
    title.setFillColor(sf::Color(46, 139, 87));
    window.draw(title);

    sf::Text subtitle("You have completed the puzzle!", font, 36);
    subtitle.setPosition(800 / 2 - subtitle.getGlobalBounds().width / 2, 180);
    subtitle.setFillColor(sf::Color(70, 130, 180));
    window.draw(subtitle);

    sf::Text playAgain("Play Again?", font, 48);
    playAgain.setPosition(800 / 2 - playAgain.getGlobalBounds().width / 2, 280);
    playAgain.setFillColor(sf::Color(52, 72, 97));
    window.draw(playAgain);

    sf::Text easy("1. Easy", font, 36);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 380);
    easy.setFillColor(sf::Color(46, 139, 87));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 36);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 440);
    medium.setFillColor(sf::Color(70, 130, 180));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 36);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 500);
    hard.setFillColor(sf::Color(178, 34, 34));
    window.draw(hard);
}

void Game::drawLoseScreen(sf::RenderWindow &window)
{
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(240, 248, 255));
    window.draw(background);

    sf::Text gameOver("Game Over!", font, 72);
    gameOver.setPosition(800 / 2 - gameOver.getGlobalBounds().width / 2, 80);
    gameOver.setFillColor(sf::Color(178, 34, 34));
    window.draw(gameOver);

    sf::Text message("Better luck next time!", font, 36);
    message.setPosition(800 / 2 - message.getGlobalBounds().width / 2, 180);
    message.setFillColor(sf::Color(70, 130, 180));
    window.draw(message);

    sf::Text playAgain("Try Again?", font, 48);
    playAgain.setPosition(800 / 2 - playAgain.getGlobalBounds().width / 2, 280);
    playAgain.setFillColor(sf::Color(52, 72, 97));
    window.draw(playAgain);

    sf::Text easy("1. Easy", font, 36);
    easy.setPosition(800 / 2 - easy.getGlobalBounds().width / 2, 380);
    easy.setFillColor(sf::Color(46, 139, 87));
    window.draw(easy);

    sf::Text medium("2. Medium", font, 36);
    medium.setPosition(800 / 2 - medium.getGlobalBounds().width / 2, 440);
    medium.setFillColor(sf::Color(70, 130, 180));
    window.draw(medium);

    sf::Text hard("3. Hard", font, 36);
    hard.setPosition(800 / 2 - hard.getGlobalBounds().width / 2, 500);
    hard.setFillColor(sf::Color(178, 34, 34));
    window.draw(hard);
}

void Game::drawPauseScreen(sf::RenderWindow &window)
{

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(240, 248, 255));
    window.draw(background);

    sf::Text title("Paused", font, 72);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 80);
    title.setFillColor(sf::Color(52, 72, 97));
    window.draw(title);

    sf::Text resume("Press P to Resume", font, 36);
    resume.setPosition(800 / 2 - resume.getGlobalBounds().width / 2, 180);
    resume.setFillColor(sf::Color(70, 130, 180));
    window.draw(resume);
}

void Game::drawTimer(sf::RenderWindow &window, sf::Time elapsedTime)
{
    int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;

    sf::RectangleShape timerBox(sf::Vector2f(150, 35));
    timerBox.setFillColor(sf::Color(70, 130, 180, 200));
    timerBox.setPosition(20, 20);
    timerBox.setOutlineThickness(2);
    timerBox.setOutlineColor(sf::Color(52, 72, 97));

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setString("Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(30, 25);

    window.draw(timerBox);
    window.draw(timerText);
}

void Game::drawScore(sf::RenderWindow &window)
{

    sf::RectangleShape scoreBox(sf::Vector2f(150, 35));
    scoreBox.setFillColor(sf::Color(46, 139, 87, 200));
    scoreBox.setPosition(190, 20);
    scoreBox.setOutlineThickness(2);
    scoreBox.setOutlineColor(sf::Color(52, 72, 97));

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(grid.currentScore));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(200, 25);

    window.draw(scoreBox);
    window.draw(scoreText);
}

void Game::drawNumberError(sf::RenderWindow &window)
{

    sf::RectangleShape errorBox(sf::Vector2f(150, 35));
    errorBox.setFillColor(sf::Color(178, 34, 34, 200));
    errorBox.setPosition(360, 20);
    errorBox.setOutlineThickness(2);
    errorBox.setOutlineColor(sf::Color(52, 72, 97));

    sf::Text errorText;
    errorText.setFont(font);
    errorText.setString("Errors: " + std::to_string(grid.numberError) + "/3");
    errorText.setCharacterSize(24);
    errorText.setFillColor(sf::Color::White);
    errorText.setPosition(370, 25);

    window.draw(errorBox);
    window.draw(errorText);
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
    // Create background box
    sf::RectangleShape background(sf::Vector2f(600, 40));
    background.setFillColor(sf::Color(70, 130, 180, 200));
    background.setPosition(100, 545);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color(52, 72, 97));

    // Create individual shortcut texts
    sf::Text noteText("N: Note", font, 24);
    sf::Text pauseText("P: Pause", font, 24);
    sf::Text deleteText("Backspace: Delete", font, 24);

    // Set text colors
    noteText.setFillColor(sf::Color::White);
    pauseText.setFillColor(sf::Color::White);
    deleteText.setFillColor(sf::Color::White);

    // Position texts evenly
    noteText.setPosition(150, 550);
    pauseText.setPosition(350, 550);
    deleteText.setPosition(500, 550);

    // Draw everything
    window.draw(background);
    window.draw(noteText);
    window.draw(pauseText);
    window.draw(deleteText);
}
