//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"
#include "common.hpp"

BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {
    /*
     * I think I need to initialize the size of memory of p1_setup_board and p2_setup_board here, what do you think @Josh F?
     */
    // Check for invalid board size
    if (rows == 0 or columns== 0) {
        throw BitArray2DException("Invalid Board Size");
    }

    // Allocate memory
   // cout << "\nrows: " << rows << endl;
   // cout << "columns: " << columns << endl;
    this -> columns = columns;
    this -> rows = rows;
    array = new char[rows*columns];
    array = "0110000010000011";
   // cout << "array memory pointer: " << &array << endl;
}


BitArray2D::~BitArray2D() {

}


bool BitArray2D::get(unsigned int row, unsigned int column){
    // Check for invalid board size
    if (row >= BOARD_SIZE or column >= BOARD_SIZE or row < 0 or column < 0) {
        throw BitArray2DException("Invalid Board Size");
    }
    // set array bounds
    int memRowBitSize = 3;      // 2^memRowBitSize memory array allocation
    int memColBitSize = 3;      // 2^memColBitSize memory array allocation
    if (row >= 8) {
        memRowBitSize = 4;
    } else if (column >= 8) {
        memRowBitSize = 4;
    } else if (row >= 16 or column >= 16) {
        throw BitArray2DException("Board is too beeg");
    }
    // get the element
    bool val = get_bit_elem(array, columns, row, column);
    if (val == 1) {
        return 1;
    } else {
        return 0;
    }
}



void BitArray2D::set(unsigned int row, unsigned int column){
    // Check for invalid board size
    if (row >= BOARD_SIZE or column >= BOARD_SIZE or row < 0 or column < 0) {
        throw BitArray2DException("Invalid Board Size");
    }
    // set the element
    set_bit_elem(array, columns, row, column);
}
