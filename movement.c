#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"

void checkFowardTwoPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int two_TilesInfront, int one_TileInfront, 
	int rowStart, int rowEnd){
	
	// Checks that all the following criteria are met:
	//   - The new tile is 2 spaces directly in front of the pawn
	//   - The new tile is empty
	//   - The tile directly in front of the pawn is empty
	//   - It is still the pawns first move (located in starting row)

	if(
		*arrayIndexPiece - *arrayIndexMove == two_TilesInfront 
		&& strcmp(gameBoard[*arrayIndexMove], "O ") == 0
		&& strcmp(gameBoard[*arrayIndexMove + one_TileInfront], "O ") == 0  
		&& rowStart < *arrayIndexPiece && *arrayIndexPiece < rowEnd){ 

		// Updates the gameBoard to show movement foward of 2 tiles.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
	}
}

void checkFowardOnePawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int one_TileInfront){
	
	// Checks that all the following criteria are met:
	//   - The new tile is 1 space directly in front of the pawn
	//   - The tile directly in front of the pawn is empty

	if(
		*arrayIndexPiece - *arrayIndexMove == one_TileInfront 
		&& strcmp(gameBoard[*arrayIndexMove], "O ") == 0){ 
		
		// Updates the gameBoard to show movement foward of 1 tile.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
	}
}

void checkDiagonalsPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int rowLocation, int one_TileInDiagonal, 
	char opposingTeam){

	// Checks that all the following criteria are met:
	//   - The piece is located in a specfied row (necessary to handle cases 
	//	   of diagonal movment from the edge columns)
	//   - The new tile is 1 space directly diagonal in front of the pawn
	//   - The new tile contains a piece of the opponents

	if(
		(*arrayIndexPiece + rowLocation) % 8  == 0 
		&& *arrayIndexPiece - *arrayIndexMove == one_TileInDiagonal
	 	&& gameBoard[*arrayIndexMove][0] == opposingTeam){
		
		// Updates the gameBoard to show movement diagonally foward of 1 tile.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
	}
}

void movePawn(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove){
	// If the selected pawn is white's.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		// Check if the pawn has been moved forward two spaces with the inputs:
		//   - 16, represents two tiles directly foward in the array
		//   - 8, represents one tile directly foward in the array
		//   - 47 and 56, represents row 2 on the board, starting position for 
		//	   white pawns
		checkFowardTwoPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
			16, 8, 47, 56);

		// Checks if the pawn has moved foward one space with 8 representing one 
		// tile directly foward in the array
		checkFowardOnePawn(gameBoard, arrayIndexPiece, arrayIndexMove, 8);
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 0, represent that the selected piece is in the left most column
		//   - 7, represents on tile diagonally right in the array
		//   - B, represents that the opposition team is black  
		checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 0, 7, 'B');
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 2-8, represents the selected piece is not on the edge of the board, 
		//     doesn't include 1 as that represents the right most column
		//   - Other inputs are same as above
		for (int rowLocation = 2; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
				rowLocation, 7, 'B');
		}

		// Checks if the selected piece has moved diagonally left with the inputs:
		//   - 1-8, represent that the selected piece isn't is the left most column
		//     doesn't include 0 as that represents the left most column
		//   - 9, represents on tile diagonally left in the array
		//   - B, represents that the opposition team is black  
		for (int rowLocation = 1; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, rowLocation, 9, 'B');
		}		
	}
	
	// If the selected pawn is black's.
	else{
		// Check if the pawn has been moved forward two spaces with the inputs:
		//   - -16, represents two tiles directly foward in the array
		//   - -8, represents one tile directly foward in the array
		//   - 7 and 16, represents row 2 on the board, starting position for 
		//	   white pawns
		checkFowardTwoPawn(gameBoard, arrayIndexPiece, arrayIndexMove, -16, -8, 7, 16);
		
		// Checks if the pawn has moved foward one space with -8 representing one 
		// tile directly foward in the array
		checkFowardOnePawn(gameBoard, arrayIndexPiece, arrayIndexMove, -8);

		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 0, represent that the selected piece is in the left most column
		//   - -9, represents on tile diagonally right in the array
		//   - W, represents that the opposition team is white  
		checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 0, -9, 'W');
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 2-8, represents the selected piece is not on the edge of the board, 
		//     doesn't include 1 as that represents the right most column
		//   - Other inputs are same as above
		for (int rowLocation = 2; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, rowLocation, -9, 'W');
		}

		// Checks if the selected piece has moved diagonally left with the inputs:
		//   - 1-8, represent that the selected piece isn't is the left most column
		//     doesn't include 0 as that represents the left most column
		//   - -7, represents on tile diagonally left in the array
		//   - W, represents that the opposition team is white
		for (int rowLocation = 1; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, rowLocation, -7, 'W');
		}		
	}
}