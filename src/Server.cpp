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


#include "common.hpp"
#include "Server.hpp"
#include <fstream>
#include <iostream>


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
}

struct player1
{
    int bSize;
    //char board[BOARD_SIZE][BOARD_SIZE];
    char board[];
};

struct player2
{
    int bSize;
    //char board[BOARD_SIZE][BOARD_SIZE];
    char board[];
};

// Initialize structures
struct player1 p1;
struct player2 p2;

void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    // Evaluate if the board size is correct or not
    if (board_size != BOARD_SIZE) {
        __throw_bad_exception();
        cout << "\nWrong board size\n";
    }

    // Assign board sizes to structs
    p1.bSize = board_size;
    p2.bSize = board_size;

    // Evaluate file name
    if (p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt") {
        __throw_bad_exception();
        cout << "\nIncorrect file name\n";
    }


    // Read in boards into p1 & p2 structures
    ifstream p1_board_read;
    ifstream p2_board_read;

    // Read player 1 board
    p1_board_read.open(p1_setup_board);
    cout << "Reading from p1 board" << endl;
    p1_board_read >> p1.board;
    p1_board_read.close();

    // Read player 2 board
    p2_board_read.open(p2_setup_board);
    cout << "Reading from p2 board" << endl;
    p2_board_read >> p2.board;
    p2_board_read.close();

    cout << p1.board;
    cout << p2.board;


}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    // Check if I hit something
    /* if (p1.board[x+y] == '_') {
        __throw_bad_exception();
        cout << "\nMissed";
    } */
    // Check if two players are consistently playing
    if (player != 1 && player != 2) {
        __throw_bad_exception();
        cout << "\nToo many or too few players active.";
    }

}


int Server::process_shot(unsigned int player) {

    // Check if two players are consistently playing
    if (player != 1 && player != 2) {
        __throw_bad_exception();
        cout << "\nToo many or too few players active.";
    }
   return NO_SHOT_FILE;
}