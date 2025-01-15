#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Function checks if boat will overlap with other ships
 * @param gameboard player gameboard used to place down ships
 * @param coordinateOne start of boat
 * @param coordinateTwo end of boat
 * @param length length of boat
 */
bool checkOverlap(int gameboard[8][8], int coordinateOne[2], int coordinateTwo[2], int length){
	int direction;
	//determine whether the boat will be placed horizontally or vertically
	if (coordinateOne[1]==coordinateTwo[1]){
		//horizontal movement
		if (coordinateOne[0]>coordinateTwo[0]){
			direction=0; //boat will be placed to the left of coord 1
		} else {
			direction=1; //boat will be placed to the right of coord 1
		}
	} else {
		//vertical movement
		if (coordinateOne[1]>coordinateTwo[1]){
			direction=2; //boat will be placed vertically up from coord 1
		} else {
			direction=3; //boat will be placed vertically down from coord 1
		}
	}
	//placing the boat down
	int x=coordinateOne[0];
	int y=coordinateOne[1];
	
	while (length!=0){
		if (gameboard[y][x]==0){
			if (direction==3){
				y++;
			} else if (direction==2){
				y--;
			} else if (direction==0){
				x--;
			} else {
				x++;
			}
			length--;
		} else {
			return false;
		}
	}
	return true;
}

/**
 * @brief function gets user input to determine coordinates of boat
 * @param pos used to indicate which coordinates will be grabbed, be it "first x", "first y", "last x", or "last y"
 */
int getCoordinate(char pos[]){
	int val =-1;
	while (val<0 || val>7){
		printf("Please enter the %s coordinate of your ship: ", pos);
		scanf("%d", &val);
		if (val<0 || val>7){
			printf("Please enter a value between 0 and 7.");
		}
	}
	return val;
	
}

/**
 * @brief Collects coordinates from user, verifies them, and places them on the players gameboard
 * @param distance the number of holes the boat can occupy
 * @param gameBoard the players gameboard
 */
void determineCoordinates(int distance, int gameBoard[8][8]){
	int coordinateOne[2] = {-1, -1};
	int coordinateTwo[2] = {-1, -1};
	int length= 0;
	bool overlapping = false;
	while(length!=distance && !overlapping){
		coordinateOne[0]=getCoordinate("first x");
		coordinateOne[1]=getCoordinate("first y");
		coordinateTwo[0]=getCoordinate("last x");
		coordinateTwo[1]=getCoordinate("last y");

		if (coordinateOne[0]==coordinateTwo[0]){
			length=abs(coordinateOne[1]-coordinateTwo[1]-1);
			if (length!=distance){
				printf("You entered a boat with a length of %d, please enter one with a length of %d.\n", length, distance);
				length=0;
			}
		} else if (coordinateOne[1]==coordinateTwo[1]){
			length=abs(coordinateOne[0]-coordinateTwo[0]-1);
			if (length!=distance){
				printf("You entered a boat with a length of %d, please enter one with a length of %d.\n", length, distance);
				length=0;
			}
		} else {
			printf("Please make sure coordinates are on the same column or row as each other. \n");
		}
		overlapping = checkOverlap(gameBoard, coordinateOne, coordinateTwo, distance);
		if (!overlapping){
			printf("Your boat is overlapping with another. Please correct this. \n");
			length=0;
		}
	}
	int direction;
	if (coordinateOne[1]==coordinateTwo[1]){
		if (coordinateOne[0]>coordinateTwo[0]){
			direction=0; //left
		} else {
			direction=1; //right
		}
	} else {
		if (coordinateOne[1]>coordinateTwo[1]){
			direction=2; //up
		} else {
			direction=3; //down
		}
	}
	int x=coordinateOne[0];
	int y=coordinateOne[1];
	
	while (length!=0){
		gameBoard[y][x]=1;
		if (direction==3){
			y++;
		} else if (direction==2){
			y--;
		} else if (direction==0){
			x--;
		} else {
			x++;
		}
		length--;
	}
}

/**
 * @brief used to print a gameboard (prior to playing the game)
 * @param board - gameboard
 */
void printGameBoard(int board[8][8]){
	printf("  0 1 2 3 4 5 6 7 \n");
	for (int i=0; i<8; i++){
		printf("%d ", i);
		for (int j=0; j<8; j++){
			if (board[i][j]==0){
				printf("*");
			} else {
				printf("d");
			}
			printf(" ");
		}
		printf("\n");
	}
}

/**
 * @brief Initial function used to populate the players gameboard with numerous ships
 * @param gameboardPlayer
 */
void populatePlayerBoard(int gameboardPlayer[8][8]){
	printGameBoard(gameboardPlayer);
	
	printf("Lets start by placing your carrier ship (5 spaces)\n");
	determineCoordinates(5, gameboardPlayer);
	
	printGameBoard(gameboardPlayer);
	printf("Now lets place your battleship (4 spaces) \n");
	determineCoordinates(4, gameboardPlayer);
	
	printGameBoard(gameboardPlayer);
	printf("Smart choice! Where should we put the cruiser (3 spaces) \n");
	determineCoordinates(3, gameboardPlayer);
	
	printGameBoard(gameboardPlayer);
	printf("What about the submarine? (3 spaces) \n");
	determineCoordinates(3, gameboardPlayer);
	
	printGameBoard(gameboardPlayer);
	printf("Finally, what about the destroyer? (2 spaces) \n");
	determineCoordinates(2, gameboardPlayer);
}

int main(int argc, char **argv){
	
	int gameboardPlayer[8][8];
	int gameboardComputer[8][8];
	
	
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			gameboardPlayer[i][j]=0;
			gameboardComputer[i][j]=0;
		}
	}
	
	populatePlayerBoard(gameboardPlayer);
	return 0;
}




