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

int bSize;
// Initialize structures
struct player1 p1;
struct player2 p2;
int shot_results;
void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    this -> board_size = board_size;
    bSize = BOARD_SIZE;
    // Evaluate if the board size is correct or not
    if (board_size != BOARD_SIZE) {
        throw ServerException("Incorrect board size");
    }

    // Evaluate file name
    if (p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt") {
        throw ServerException("Invalid board file paths");
    }

    // Read in boards from text files
    /* READ IN PLAYER 2 BOARD */
    ifstream read;
    string line;
    read.open(p2_setup_board);
    int row = 0;
    int col = 0;
    // Code Snippet Source: cplusplus.com/forum/beginner/27799/
    while(std::getline (read,line)) {
        // Parse each character in the string
        // Code Snippet Source: https://stackoverflow.com/questions/9438209/for-every-character-in-string
        for(char& c : line) {
            p2.board[row][col] = c;
            col++;
        }
        row++;      // Increment row
        col = 0;    // reset col for the next line
    }
    read.close();

    // Read in Player 1 Board
    ifstream read2;
    string line2;
    read.open(p1_setup_board);
    row = 0;
    col = 0;
    while(std::getline(read2, line2)) {
        for (char& c: line2) {
            p1.board[row][col] = c;
            col++;
        }
        row++;
        col = 0;
    }
    read2.close();

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    // Check if two players are consistently playing
    if (player < 1 or player > 2) {
        throw ServerException("Ensure there are two players");
    }

    // Set up board
    // Check if out of bounds
    
    if (x >= bSize || x < 0 ) {
        return OUT_OF_BOUNDS;
    } else if (y >=  bSize || x < 0) {
        return OUT_OF_BOUNDS;
    }

    if (player == 1) { // See if I hit something for player 2
        // Check if I hit something
        printf("p2 board hit check:\n%c\n", p2.board[y][x]);
        if (p2.board[y][x] == 'C' or p2.board[y][x] == 'B' or p2.board[y][x] == 'D' or p2.board[y][x] == 'R' or p2.board[y][x] == 'S') {
            return HIT;
        } else if (p2.board[y][x] == '_') {
            return MISS;
        } else {
            throw ServerException("Invalid shot");
        }
    } else {
        if (p1.board[y][x] != '_') {
            return HIT;
        } else {
            return MISS;
        }
    }


}


int Server::process_shot(unsigned int player) {
    // PSEUDO CODE FOR process_shot
    // check the player number is correct                   CHECK
    // Read in player shot file                             CHECK
    // grab shot coordinates                                CHECK
    // pass to eval shot                                    CHECK
    // write result file to ofstream/JsonOutputArchive      CHECK
    // remove the shot file                                 CHECK
    // return SHOT_FILE_PROCESSED                           CHECK

    // Variable Declarations
    int x;
    int y;
    // Check if two players are consistently playing
    if (player != 1 && player != 2) {
        throw ServerException("Invalid number of players");
    }
    string fileShot = "player_" + to_string(player) + ".shot.json";

    // Code Snippet From: https://stackoverflow.com/questions/32205981/reading-json-files-in-c
    std::ifstream shot_file_read(fileShot);
    cereal::JSONInputArchive archive_in(shot_file_read);
    archive_in(x, y);

    cout << "\nx: " << x  << "\ny: " << y << endl;
    // Pass to eval shot
    int result = evaluate_shot(player, x, y);
    cout << "result: " << result << endl;

    string fileResult = "player_" + to_string(player) + ".result.json";
    // Writing reversed engineered from above code snippet.
    std::ofstream shot_file_write(fileResult);
    cereal::JSONOutputArchive archive_out(shot_file_write);
    // Write to output file
    archive_out(CEREAL_NVP(result));

    // Remove player_1.shot.json
    if (player == 1) {
        remove("player_1.shot.json");
    } else {
        remove("player_2.shot.json");
    }
    return NO_SHOT_FILE;

}

