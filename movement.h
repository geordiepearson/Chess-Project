/*
** movement.h
**
** Author: Geordie Pearson
**
*/

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

// Checks if the player has attempted to move a pawn foward 2 spaces on its 
// first turn. If the move is valid, updates the gameBoard array.
void checkFowardTwoPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int twoTilesInfront, int oneTileInfront, 
	int rowStart, int rowEnd);

// Checks if the player has attempted to move a pawn foward 1 space. If the 
// move is valid, updates the gameBoard array.
void checkFowardOnePawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int oneTileInfront);

// Checks if the player has attempted to move a pawn diagonally to capture 
// another piece.If the move is valid, updates the gameBoard array.
void checkDiagonalsPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int rowLocation, int oneTileInDiagonal, 
	char opposingTeam);

// Checks for all the potential valid moves a player could have attempted with
// a pawn. Updates the board if a valid move is provided.
void movePawn(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove);

// Checks if the player has attempted to move the rook fowards or backwards any
// number of spaces. If the move is valid, updates the gameBoard array.
void checkVerticalRook(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int oneTile);

// Checks if the player has attempted to move the rook left or right any
// number of spaces. If the move is valid, updates the gameBoard array.
void checkHorizontalRook(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int oneTile);

// Checks if the player has attempted to move the bishop diagonally left or 
// right any number of spaces. If the move is valid, updates the gameBoard array.
void checkBishopMove(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int verticalDirection);

// Checks for all the potential valid moves a player could have attempted with
// a rook. Updates the board if a valid move is provided.
void moveRook(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove);

// Checks for all the potential valid moves a player could have attempted with
// a knight. Updates the board if a valid move is provided.
void moveKnight(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove);

// Checks for all the potential valid moves a player could have attempted with
// a bishop. Updates the board if a valid move is provided.
void moveBishop(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove);

#endif /*MOVEMENT_H_*/