#include "Game.hpp"
#include "Grid.hpp"

Grid::Grid()
    : grid(9, std::vector<int>(9, 0)),
      isEditable(9, std::vector<bool>(9, false))
{
    font.loadFromFile("E:/project1_sudoku/project1-sudoku/assets/fonts/Roboto-Medium.ttf");
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

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = 0;
        }
    }

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
    const float CELL_SIZE = 50.0f;
    const float GRID_SIZE = CELL_SIZE * 9;
    const float offsetX = (800 - GRID_SIZE) / 2;
    const float offsetY = (600 - GRID_SIZE) / 2;

    const sf::Color BORDER_COLOR(52, 72, 97, 255);
    const sf::Color SELECTED_COLOR(187, 222, 251, 255);
    const sf::Color HIGHLIGHT_COLOR(195, 215, 234, 255);
    const sf::Color LIGHT_HIGHLIGHT_COLOR(226, 235, 243, 255);
    const sf::Color ERROR_COLOR(255, 99, 71, 200);
    const sf::Color NUMBER_COLOR(52, 72, 97, 255);
    const sf::Color EDITABLE_NUMBER_COLOR(65, 105, 225);
    const sf::Color ERROR_NUMBER_COLOR(220, 20, 60);

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setOutlineColor(BORDER_COLOR);
    cell.setOutlineThickness(1);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cell.setPosition(offsetX + j * CELL_SIZE, offsetY + i * CELL_SIZE);

            if (i == selectedRow && j == selectedCol)
            {
                cell.setFillColor(SELECTED_COLOR);
            }
            else if (selectedRow != -1 && selectedCol != -1 &&
                     grid[i][j] == grid[selectedRow][selectedCol] &&
                     grid[selectedRow][selectedCol] != 0)
            {
                if (i == selectedRow || j == selectedCol ||
                    (i / 3 == selectedRow / 3 && j / 3 == selectedCol / 3))
                {
                    cell.setFillColor(!isSafe(selectedRow, selectedCol, grid[selectedRow][selectedCol]) ? ERROR_COLOR : HIGHLIGHT_COLOR);
                }
                else
                {
                    cell.setFillColor(HIGHLIGHT_COLOR);
                }
            }
            else if (i == selectedRow || j == selectedCol ||
                     (i / 3 == selectedRow / 3 && j / 3 == selectedCol / 3))
            {
                cell.setFillColor(LIGHT_HIGHLIGHT_COLOR);
            }
            else
            {
                cell.setFillColor(sf::Color::White);
            }

            window.draw(cell);

            if (grid[i][j] != 0)
            {
                sf::Text number(std::to_string(grid[i][j]), font, 36);
                number.setPosition(offsetX + j * CELL_SIZE + 15, offsetY + i * CELL_SIZE + 6);

                if (!isEditable[i][j])
                {
                    number.setFillColor(NUMBER_COLOR);
                }
                else
                {
                    number.setFillColor(isSafe(i, j, grid[i][j]) ? EDITABLE_NUMBER_COLOR : ERROR_NUMBER_COLOR);
                }
                window.draw(number);
            }
            else if (!notes[i][j].empty())
            {
                for (int note : notes[i][j])
                {
                    sf::Text noteText(std::to_string(note), font, 12);
                    noteText.setPosition(offsetX + j * CELL_SIZE + 5 + ((note - 1) % 3) * 15,
                                         offsetY + i * CELL_SIZE + 5 + ((note - 1) / 3) * 15);
                    noteText.setFillColor(sf::Color(100, 100, 100));
                    window.draw(noteText);
                }
            }
        }
    }

    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            sf::RectangleShape thickLine;
            thickLine.setFillColor(BORDER_COLOR);

            thickLine.setSize(sf::Vector2f(GRID_SIZE, 3));
            thickLine.setPosition(offsetX, offsetY + i * CELL_SIZE);
            window.draw(thickLine);

            thickLine.setSize(sf::Vector2f(3, GRID_SIZE));
            thickLine.setPosition(offsetX + i * CELL_SIZE, offsetY);
            window.draw(thickLine);
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
    if (!isNoteMode)
    {
        if (selectedRow >= 0 && selectedRow < 9 && selectedCol >= 0 && selectedCol < 9)
        {
            if (isEditable[selectedRow][selectedCol])
            {
                notes[selectedRow][selectedCol].clear();
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
    else
    {
        if (selectedRow >= 0 && selectedRow < 9 && selectedCol >= 0 && selectedCol < 9)
        {
            if (isEditable[selectedRow][selectedCol])
            {
                if (grid[selectedRow][selectedCol] != 0)
                    grid[selectedRow][selectedCol] = 0;
                notes[selectedRow][selectedCol].insert(value);
            }
        }
    }
}

bool Grid::checkWin()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (grid[i][j] == 0 || !isSafe(i, j, grid[i][j]))
                return false;
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
