/*
** movement.h
**
** Author: Geordie Pearson
**
*/

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

// Checks if the player has attempted to move a pawn foward 2 spaces on its 
// first turn. If the move is valid, updates the gameBoard array with the pawn
// arrving at its new position and its previous position becoming empty.
void checkFowardTwoPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int two_TilesInfront, int one_TileInfront, 
	int rowStart, int rowEnd);

// Checks if the player has attempted to move a pawn foward 1 space. If the 
// move is valid, updates the gameBoard array with the pawn arrving at its new
// position and its previous position becoming empty.
void checkFowardOnePawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int one_TileInfront);

// Checks if the player has attempted to move a pawn diagonally to capture 
// another piece.If the move is valid, updates the gameBoard array with the 
// pawn arrving at its new position and its previous position becoming empty.
void checkDiagonalsPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int rowLocation, int one_TileInDiagonal, 
	char opposingTeam);

// Checks for all the potential valid moves a player could have attempted with
// a pawn. Updates the board if a valid move is provided.
void movePawn(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove);

#endif /*MOVEMENT_H_*/