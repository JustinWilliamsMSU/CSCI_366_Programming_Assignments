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
    int row = 0;
    int col = 0;
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
    read.close();

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    // Check if two players are consistently playing
    if (player < 1 or player > 2) {
        __throw_bad_exception();
        cout << "\nToo many or too few players active.";
    }

    // Check if out of bounds
    if (x >= BOARD_SIZE ) {
        cout << "OUT OF BOUNDS" << endl;
        return OUT_OF_BOUNDS;
    } else if (y >= BOARD_SIZE) {
        cout << "OUT OF BOUNDS" << endl;
        return OUT_OF_BOUNDS;
    }
    if (player == 1) { // See if I hit something for player 2
        cout << "board[" << y << "][" << x << "] = " << (int)p2.board[(int)y][(int)x] << "\n";
        // Check if I hit something
        if (p2.board[y][x] != '_') {
            cout << "HIT" << endl;
            return HIT;
        } else {
            cout << "MISS" << endl;
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
        __throw_bad_exception();
    }

    // Code Snippet From: https://stackoverflow.com/questions/32205981/reading-json-files-in-c
    std::ifstream shot_file_read("player_1.shot.json");
    cereal::JSONInputArchive archive_in(shot_file_read);
    archive_in(x, y);

    cout << "\nx: " << x  << "\ny: " << y << endl;
    // Pass to eval shot
    int result = evaluate_shot(player, x, y);
    cout << "result: " << result << endl;

    // Writing reversed engineered from above code snippet.
    std::ofstream shot_file_write("player_1.result.json");
    cereal::JSONOutputArchive archive_out(shot_file_write);
    // Write to output file
    if (result == 1) { // HIT
        archive_out(CEREAL_NVP(result));
    } else if (result == 0) { // OUT OF BOUNDS
        archive_out(CEREAL_NVP(result));
    } else if (result == -1) { // MISS
        archive_out(CEREAL_NVP(result));
    }

    // Remove player_1.shot.json
    remove("player_1.shot.json");
    return NO_SHOT_FILE;

}

