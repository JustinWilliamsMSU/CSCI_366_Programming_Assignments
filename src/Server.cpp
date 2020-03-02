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
    char board[BOARD_SIZE][BOARD_SIZE];
    // Flags
    int hitMarkers[BOARD_SIZE][BOARD_SIZE];     // Keeps track of where a hit was registered
};


struct player2
{
    char board[BOARD_SIZE][BOARD_SIZE];
    // Flags
    int hitMarkers[BOARD_SIZE][BOARD_SIZE];     // Keeps track of where a hit was registered
};


// Initialize structures
struct player1 p1;
struct player2 p2;
int shot_results;
void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    // Evaluate if the board size is correct or not
    if (board_size != BOARD_SIZE) {
        __throw_bad_exception();
        cout << "\nWrong board size\n";
    }

    // Evaluate file name
    if (p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt") {
        __throw_bad_exception();
        cout << "\nIncorrect file name\n";
    }

    // Read in boards from text files
    /* READ IN PLAYER 1 & 2 BOARDS */
    ifstream read;
    string line;
    read.open(p2_setup_board);
    int row = 1;
    int col = 1;
    // Code Snippet Source: cplusplus.com/forum/beginner/27799/
    while(std::getline (read,line)) {
        //cout << "" << p1_line << endl;
        // Parse each character in the string
        // Code Snippet Source: https://stackoverflow.com/questions/9438209/for-every-character-in-string
        for(char& c : line) {
            p2.board[row][col] = c;
            col++;
        }
        row++;      // Increment row
        col = 0;    // reset col for the next line
    }
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    // Check if two players are consistently playing
    if (player < 1 or player > 2) {
        __throw_bad_exception();
        cout << "\nToo many or too few players active.";
    }

    // Check if out of bounds
    if (x > BOARD_SIZE ) {
        return OUT_OF_BOUNDS;
    } else if (y >= BOARD_SIZE) {
        return OUT_OF_BOUNDS;
    }
    if (player == 1) { // See if I hit something for player 2

        cout << "board[" << y << "][" << x << "] = " << p2.board[y][x] << "\n";
        // Check if I hit something
        if (p2.board[y][x] != '_') {
            return HIT;
        } else {
            return MISS;
        }
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
/*
char Server::read_file(unsigned int player, string fileName, int board_size) {
    // Initialize vars
    int playerOne = 0;
    int playerTwo = 0;
    char board[board_size][board_size];

     READ IN PLAYER 1 & 2 BOARDS
    ifstream read;
    string line;
    read.open(fileName);
    int row = 1;
    int col = 1;
    // Code Snippet Source: cplusplus.com/forum/beginner/27799/
    while(std::getline (read,line)) {
        //cout << "" << p1_line << endl;
        // Parse each character in the string
        // Code Snippet Source: https://stackoverflow.com/questions/9438209/for-every-character-in-string
        for(char& c : line) {
            board[row][col] = c;
            //printf("%c", board[row][col]);
            col++;
        }
        row++;      // Increment row
        col = 0;    // reset col for the next line
        //printf("\n");
    }
    if (player == 1) {
        p2.board[BOARD_SIZE][BOARD_SIZE] = board[BOARD_SIZE][BOARD_SIZE];
    } else {
        p1.board[BOARD_SIZE][BOARD_SIZE] = board[BOARD_SIZE][BOARD_SIZE];
    }
    return 0;
}

int Server::shot_in_bounds(unsigned int player, int x, int y) {
    if (x >= BOARD_SIZE) {
        return OUT_OF_BOUNDS;
    } else if (y >= BOARD_SIZE) {
        return OUT_OF_BOUNDS;
    }
}

*/
