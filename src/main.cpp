#include "Grid.hpp"
#include <iostream>

int main()
{
    Grid sudokuGrid;
    sudokuGrid.generate();
    sudokuGrid.print();

    if (sudokuGrid.isValidMove(0, 2, 4))
    {
        sudokuGrid.setValue(0, 2, 4);
        std::cout << "\nAfter placing 4 in (0, 2):\n";
        sudokuGrid.print();
    }
    else
    {
        std::cout << "\nMove not valid!\n";
    }

    return 0;
}
