#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Grid
{
public:
    Grid();                                      // Khởi tạo lưới rỗng
    void generate();                             // Tạo một lưới Sudoku mới
    bool isValidMove(int row, int col, int num); // Kiểm tra xem bước đi hợp lệ không
    void setValue(int row, int col, int value);  // Đặt giá trị cho một ô
    int getValue(int row, int col) const;        // Lấy giá trị của một ô
    void print() const;                          // In lưới ra console (debug)
    void draw(sf::RenderWindow &window);

private:
    std::vector<std::vector<int>> grid;
    bool isSafe(int row, int col, int num); // Kiểm tra an toàn khi điền số
};

#endif
