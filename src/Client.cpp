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
#include "Client.hpp"
#include <fstream>
#include <iostream>

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    // Variable Init
    string file;
    // Code Snippet From: https://stackoverflow.com/questions/9694838/how-to-implement-2d-vector-array
    int cols = board_size;
    int rows = board_size;
    int vals = 0;
    std::vector<std::vector<int>> board;
    board.resize(rows, std::vector<int>(cols, vals));

    // Code Snippet From: Mike's Github
    // serialize the array
    if (player == 1 || player == 2) {
        if (player == 1) {
            file = "player_1.action_board.json";
        } else {
            file = "player_2.action_board.json";
        }
        ofstream array_ofp(file); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", board)); // serialize the data giving it a name

        initialized = true;
    } else {
        initialized = false;
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    ofstream fire_write("player_1.shot.json");
    cereal::JSONOutputArchive fire_wr(fire_write);
    fire_wr(CEREAL_NVP(x), CEREAL_NVP(y));
}


bool Client::result_available() {
    // Declare file variables
    string fileName = "player_1.result.json";
    std::ifstream infile(fileName);
    remove("player_1.shot.json");
    // Check if the files are valid
    if (infile.good()) {
        return true;
    } else {
        return false;
    }


}


int Client::get_result() {
    int result;
    std::ifstream result_read("player_1.result.json");
    cereal::JSONInputArchive result_ready(result_read);
    result_ready(result);
    result_read.close();
    remove("player_1.result.json");
    if (result == HIT || result == MISS || result == OUT_OF_BOUNDS) {
        return result;
    } else {
        throw ClientException("Bad result");
    }

}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    // Declare Variables
    string file = "player_1.action_board.json";
    vector<vector<int> > board;

    // Read in file to update it
    std::ifstream action_file_read("player_1.action_board.json");
    cereal::JSONInputArchive archive_in(action_file_read);
    archive_in(board);
    // Rewrite the hit
    board[x][y] = result;

    // Write to file if it's a valid HIT or MISS
    if (result == HIT or result == MISS) {
        ofstream array_ofp(file); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", board));
    }

}
string Client::render_action_board(){

}