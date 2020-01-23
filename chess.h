/*
** chess.h
**
** Author: Geordie Pearson
**
*/

#ifndef CHESS_H_
#define CHESS_H_

// Prints the player whose turn it currently is and prints the game board in 
// its current state.
void printBoard(int *turn);

// Get the users input and checks if it corresponds to a tile on a chess board.
// If the tile exists, it sets a flag to indicate it.
void getInputTile(char piece_location[], int* piece_input_flag);

// Converts the users inputted tile to an integer which corresponds to the index
// of that tile in the gameBoard array. 
void getArrayTile(char piece_location[], int* arrayIndex);

// Continuously prompts the user to input a tile and when presented with a valid
// tile, get the corresponding array position.
void selectTile(char piece_location[], int* arrayIndex, int* piece_input_flag);

// Checks whether, at the given position, there is a piece that belongs to the 
// player currently making their turn. If so, it sets a flag to indicate it.
void isTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn);

// Continuously prompts the user to input a tile that contains one of their 
//pieces. Then prints the piece and its location on the board.
void selectPiece(int* turn, int* arrayIndex, char piece_location[]);

// 
void movePiece(int* turn, int*arrayIndexPiece, int* arrayIndexMove, 
	char piece_location[]);

#endif /*CHESS_H_*/