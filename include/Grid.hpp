#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

class Grid
{
public:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> isEditable;
    Grid();                                      // Khởi tạo lưới rỗng
    void generate(int cellsToRemove);            // Tạo một lưới Sudoku mới
    bool isValidMove(int row, int col, int num); // Kiểm tra xem bước đi hợp lệ không
    void setValue(int row, int col, int value);  // Đặt giá trị cho một ô
    int getValue(int row, int col) const;        // Lấy giá trị của một ô
    void print() const;                          // In lưới ra console (debug)
    void draw(sf::RenderWindow &window);
    void selectCell(int row, int col);
    void setCellValue(int value);
    bool fillGrid();
    bool isSafe(int row, int col, int num); // Kiểm tra an toàn khi điền số
    int selectedRow = -1;                   // Hàng được chọn
    int selectedCol = -1;                   // Cột được chọn
};

#endif
