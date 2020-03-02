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
    char board[BOARD_SIZE][BOARD_SIZE];
    // Flags
    int hit;
    int miss;
    int x_OOB;                                    // OUT OF BOUNDS : OOB
    int y_OOB;
    int hitMarkers[BOARD_SIZE][BOARD_SIZE];     // Keeps track of where a hit was registered
};


struct player2
{
    int bSize;
    char board[BOARD_SIZE][BOARD_SIZE];
    // Flags
    int hit;
    int miss;
    int OOB;                                    // OUT OF BOUNDS : OOB
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

    // Assign board sizes to structs
    p1.bSize = board_size;
    //p2.bSize = board_size;

    // Evaluate file name
    if (p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt") {
        __throw_bad_exception();
        cout << "\nIncorrect file name\n";
    }


    /* READ IN PLAYER 1 BOARD */
    ifstream p1_read;
    ifstream p2_read;
    string   p1_line;
    string   p2_line;
    p1_read.open("player_1.setup_board.txt");
    int row = 1;
    int col = 1;
    // Code Snippet Source: cplusplus.com/forum/beginner/27799/
    while(std::getline (p1_read,p1_line)) {
        //cout << "" << p1_line << endl;
        // Parse each character in the string
        // Code Snippet Source: https://stackoverflow.com/questions/9438209/for-every-character-in-string
        for(char& c : p1_line) {
            p1.board[row][col] = c;
            col++;
        }
        row++;      // Increment row
        col = 0;    // reset col for the next line
    }
    p1_read.close();
    p2_read.open("player_2.setup_board.txt");
    row = 1; col = 1;
    while(std::getline(p2_read, p2_line)) {
        //cout << "" << p2_line << endl;
        for(char& c : p2_line) {
            p2.board[row][col] = c;
            col++;
        }
        row++;
        col = 0;
    }
    p2_read.close();

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    // Check if two players are consistently playing
    if (player < 1 or player > 2) {
        __throw_bad_exception();
        cout << "\nToo many or too few players active.";
    }
    printf("x: %d\n y: %d\n", x, y);
    // Check if out of bounds
    if (x > BOARD_SIZE ) {
        shot_results = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    } else if (y >= BOARD_SIZE) {
        shot_results = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    if (player == 1) { // See if I hit something for player 2

        // Check if I hit something
        if (p2.board[y][x] != '_') {
            p1.hitMarkers[y][x] = HIT;
            return HIT;
        } else {
            p1.hitMarkers[y][x] = MISS;
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