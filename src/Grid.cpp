#include "Game.hpp"
#include "Grid.hpp"

Grid::Grid()
    : grid(9, std::vector<int>(9, 0)),
      isEditable(9, std::vector<bool>(9, false)) // Khởi tạo isEditable
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
    // Tạo lưới Sudoku hoàn chỉnh
    fillGrid();

    // Xóa ngẫu nhiên các ô để tạo bài Sudoku chưa hoàn chỉnh
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 8);

    while (cellsToRemove > 0)
    {
        int row = distribution(generator);
        int col = distribution(generator);

        if (grid[row][col] != 0) // Chỉ xóa ô nếu nó chưa bị xóa
        {
            grid[row][col] = 0;
            isEditable[row][col] = true;
            cellsToRemove--;
        }
    }

    // Cập nhật lại vector isEditable cho các ô cố định
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (grid[i][j] != 0)
            {
                isEditable[i][j] = false; // Các ô cố định không thể chỉnh sửa
            }
        }
    }
}

bool Grid::isSafe(int row, int col, int num)
{
    // Kiểm tra hàng
    for (int i = 0; i < 9; ++i)
    {
        if (i != col && grid[row][i] == num) // Bỏ qua ô hiện tại
            return false;
    }

    // Kiểm tra cột
    for (int i = 0; i < 9; ++i)
    {
        if (i != row && grid[i][col] == num) // Bỏ qua ô hiện tại
            return false;
    }

    // Kiểm tra ô vuông 3x3
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
                        sf::Text number(std::to_string(grid[i][j]), font, 30);           // Đặt kích thước chữ lớn hơn
                        number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6); // Điều chỉnh vị trí
                        number.setFillColor(sf::Color::Blue);
                        window.draw(number);
                    }
                    else
                    {
                        sf::Text number(std::to_string(grid[i][j]), font, 30);           // Đặt kích thước chữ lớn hơn
                        number.setPosition(offsetX + j * 50 + 15, offsetY + i * 50 + 6); // Điều chỉnh vị trí
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

            lineRow.setPosition(offsetX, offsetY + i * 50); // Đặt vị trí của đoạn thẳng
            window.draw(lineRow);                           // Vẽ đoạn thẳng
        }
    }

    sf::RectangleShape lineCol(sf::Vector2f(3, 450));
    lineCol.setFillColor(sf::Color::Black);
    for (int i = 0; i <= 9; ++i)
    {
        if (i % 3 == 0)
        {

            lineCol.setPosition(offsetX + i * 50, offsetY); // Đặt vị trí của đoạn thẳng
            window.draw(lineCol);                           // Vẽ đoạn thẳng
        }
    }

    // Vẽ ô được chọn
    if (selectedRow != -1 && selectedCol != -1)
    {
        sf::RectangleShape highlight(sf::Vector2f(50, 50));
        highlight.setPosition(offsetX + selectedCol * 50, offsetY + selectedRow * 50);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineColor(sf::Color::Red);
        highlight.setOutlineThickness(3);
        window.draw(highlight);
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
            grid[selectedRow][selectedCol] = value;
        }
    }
}

bool Grid::checkWin()
{
    // Kiểm tra tất cả các hàng
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

    // Kiểm tra tất cả các cột
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

    // Kiểm tra tất cả các ô vuông 3x3
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

    // Nếu tất cả đều hợp lệ
    return true;
}
