#include "Game.hpp"
#include "Grid.hpp"

Grid::Grid()
    : grid(9, std::vector<int>(9, 0)),
      isEditable(9, std::vector<bool>(9, false))
{
}

bool Grid::fillGrid()
{
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (grid[row][col] == 0)
            {
                std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
                std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

                for (int num : numbers)
                {
                    if (isSafe(row, col, num))
                    {
                        grid[row][col] = num;

                        if (fillGrid())
                        {
                            return true;
                        }

                        grid[row][col] = 0;
                    }
                }

                return false;
            }
        }
    }

    return true;
}

void Grid::generate(int cellsToRemove)
{

    fillGrid();

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 8);

    while (cellsToRemove > 0)
    {
        int row = distribution(generator);
        int col = distribution(generator);

        if (grid[row][col] != 0)
        {
            grid[row][col] = 0;
            isEditable[row][col] = true;
            cellsToRemove--;
        }
    }

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (grid[i][j] != 0)
            {
                isEditable[i][j] = false;
            }
        }
    }
}

bool Grid::isSafe(int row, int col, int num)
{

    for (int i = 0; i < 9; ++i)
    {
        if (i != col && grid[row][i] == num)
            return false;
    }

    for (int i = 0; i < 9; ++i)
    {
        if (i != row && grid[i][col] == num)
            return false;
    }

    int startRow = row / 3 * 3;
    int startCol = col / 3 * 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((startRow + i != row || startCol + j != col) && grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

void Grid::draw(sf::RenderWindow &window)
{
    sf::RectangleShape cell(sf::Vector2f(50, 50));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1);

    sf::Font font;
    if (!font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/roboto-black.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    float offsetX = (800 - 450) / 2;
    float offsetY = (600 - 450) / 2;

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {

            cell.setPosition(offsetX + j * 50, offsetY + i * 50);

            if (i == selectedRow && j == selectedCol)
            {
                cell.setFillColor(sf::Color(187, 222, 251, 255));
            }
            else if (selectedRow != -1 && selectedCol != -1 && grid[i][j] == grid[selectedRow][selectedCol] && grid[selectedRow][selectedCol] != 0)
            {
                if (i == selectedRow || j == selectedCol || (i / 3 == selectedRow / 3 && j / 3 == selectedCol / 3))
                {
                    if (!isSafe(selectedRow, selectedCol, grid[selectedRow][selectedCol]))
                    {
                        cell.setFillColor(sf::Color(247, 207, 214, 255));
                    }
                    else
                    {
                        cell.setFillColor(sf::Color(195, 215, 234, 255));
                    }
                }
                else
                {
                    cell.setFillColor(sf::Color(195, 215, 234, 255));
                }
            }
            else if (i == selectedRow || j == selectedCol)
            {
                cell.setFillColor(sf::Color(226, 235, 243, 255));
            }
            else if (i / 3 == selectedRow / 3 && j / 3 == selectedCol / 3)
            {
                cell.setFillColor(sf::Color(226, 235, 243, 255));
            }
            else
            {
                cell.setFillColor(sf::Color::White);
            }

            window.draw(cell);

            if (grid[i][j] != 0)
            {
                if (!isEditable[i][j])
                {
                    sf::Text number(std::to_string(grid[i][j]), font, 30);
                    number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6);
                    number.setFillColor(sf::Color::Black);
                    window.draw(number);
                }
                else
                {
                    if (isSafe(i, j, grid[i][j]))
                    {
                        sf::Text number(std::to_string(grid[i][j]), font, 30);
                        number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6);
                        number.setFillColor(sf::Color::Blue);
                        window.draw(number);
                    }
                    else
                    {
                        sf::Text number(std::to_string(grid[i][j]), font, 30);
                        number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6);
                        number.setFillColor(sf::Color::Red);
                        window.draw(number);
                    }
                }
            }
        }
    }

    sf::RectangleShape lineRow(sf::Vector2f(450, 3));
    lineRow.setFillColor(sf::Color::Black);
    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            lineRow.setPosition(offsetX, offsetY + i * 50);
            window.draw(lineRow);
        }
    }

    sf::RectangleShape lineCol(sf::Vector2f(3, 450));
    lineCol.setFillColor(sf::Color::Black);
    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            lineCol.setPosition(offsetX + i * 50, offsetY);
            window.draw(lineCol);
        }
    }
}

void Grid::selectCell(int row, int col)
{
    if (row >= 0 && row < 9 && col >= 0 && col < 9)
    {
        selectedRow = row;
        selectedCol = col;
    }
}

void Grid::setCellValue(int value)
{
    if (selectedRow >= 0 && selectedRow < 9 && selectedCol >= 0 && selectedCol < 9)
    {
        if (isEditable[selectedRow][selectedCol])
        {
            if (!isSafe(selectedRow, selectedCol, value) && value != grid[selectedRow][selectedCol])
            {
                numberError++;
            }
            else if (isSafe(selectedRow, selectedCol, value) && value != grid[selectedRow][selectedCol])
            {
                currentScore += 50;
            }
            grid[selectedRow][selectedCol] = value;
        }
    }
}

bool Grid::checkWin()
{
    for (int i = 0; i < 9; ++i)
    {
        std::vector<bool> rowCheck(9, false);
        for (int j = 0; j < 9; ++j)
        {
            if (grid[i][j] == 0 || rowCheck[grid[i][j] - 1])
                return false;
            rowCheck[grid[i][j] - 1] = true;
        }
    }

    for (int j = 0; j < 9; ++j)
    {
        std::vector<bool> colCheck(9, false);
        for (int i = 0; i < 9; ++i)
        {
            if (grid[i][j] == 0 || colCheck[grid[i][j] - 1])
                return false;
            colCheck[grid[i][j] - 1] = true;
        }
    }

    for (int blockRow = 0; blockRow < 3; ++blockRow)
    {
        for (int blockCol = 0; blockCol < 3; ++blockCol)
        {
            std::vector<bool> boxCheck(9, false);
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    int val = grid[blockRow * 3 + i][blockCol * 3 + j];
                    if (val == 0 || boxCheck[val - 1])
                        return false;
                    boxCheck[val - 1] = true;
                }
            }
        }
    }
    return true;
}

bool Grid::checkLose()
{
    if (numberError >= 3)
        return true;
    else
        return false;
}
