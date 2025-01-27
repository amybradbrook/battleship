#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct boat {
	int id;
	int x;
	int y;
	int direction;
	int length;
	int hits;
};

struct coordinatesToBoat{
	int id;
	int x;
	int y;
};

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

bool checkOverlapWithDirection(int gameboard[8][8], int x, int y, int direction, int length){
	
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
 * @brief to prevent computer based boats from being placed overlapping with the edge of the boat
 * @param x
 * @param y
 * @param direction
 * @param length
 */
bool checkOverflow(int x, int y, int direction, int length){
	if (direction==0 && x-length<0){
		return false;
	} else if (direction==1 && x+length>7){
		return false;
	} else if (direction==2 && y-length<0){
		return false;
	} else if (direction==3 && y+length>7){
		return false;
	}
	return true;
}

struct boat placeBoat(int gameboard[8][8], int x, int y, int direction, int length, int id){
	while (length!=0){
		gameboard[y][x]=id;
		if (direction==3){
			y++;
		} else if (direction==2){
			y--;
		} else if (direction == 0){
			x--;
		} else {
			x++;
		}
		length--;
	}
	struct boat toPlace={id, x, y,direction, length, 0};
	return toPlace;
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
struct boat determineCoordinates(int distance, int gameBoard[8][8], int id){
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
	
	struct boat toAdd = placeBoat(gameBoard, x, y, direction, length, id);
	return toAdd;
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
				printf("b");
			}
			printf(" ");
		}
		printf("\n");
	}
}

/**
 * @brief used to print a gameboard (when playing game)
 * @param board - gameboard
 */
void printGameBoardInPlay(int board[8][8]){
	printf("  0 1 2 3 4 5 6 7 \n");
	for (int i=0; i<8; i++){
		printf("%d ", i);
		for (int j=0; j<8; j++){
			if (board[i][j]==1){
				printf("X");
			} else if (board[i][j]==2){
				printf("S");
			} else if (board[i][j]>=13){
				printf("h");
			} else {
				printf("*");
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
struct boat *populatePlayerBoard(int gameboardPlayer[8][8]){
	printGameBoard(gameboardPlayer);
	struct boat *fleet=malloc(sizeof(struct boat)*5);
	
	printf("Lets start by placing your carrier ship (5 spaces)\n");
	struct boat carrier = determineCoordinates(5, gameboardPlayer, 3);
	fleet[0]=carrier;
	
	printGameBoard(gameboardPlayer);
	printf("Now lets place your battleship (4 spaces) \n");
	struct boat battleship = determineCoordinates(4, gameboardPlayer, 4);
	fleet[1]=battleship;
	
	printGameBoard(gameboardPlayer);
	printf("Smart choice! Where should we put the cruiser (3 spaces) \n");
	struct boat cruiser = determineCoordinates(3, gameboardPlayer, 5);
	fleet[2]=cruiser;
	
	printGameBoard(gameboardPlayer);
	printf("What about the submarine? (3 spaces) \n");
	struct boat submarine = determineCoordinates(3, gameboardPlayer, 6);
	fleet[3]=submarine;
	
	printGameBoard(gameboardPlayer);
	printf("Finally, what about the destroyer? (2 spaces) \n");
	struct boat destroyer = determineCoordinates(2, gameboardPlayer, 7);
	fleet[4]=destroyer;
}

/**
 * @brief use to place computer gamepieces
 * @param gameboard computer gameboard
 */
struct boat *populateComputerBoard(int gameboard[8][8]){
	//first choose carrier ship (5 spaces)
	int boatsPlaced=0;
	int length = 5;
	srand(time(NULL));
	struct boat *fleet= malloc(sizeof(struct boat)*5);
	int id=3;
	while (boatsPlaced<5){
		bool valid = false;
		while (!valid){
			int x = rand() %8;
			int y = rand() %8;
			int d = rand() %4;
			valid=checkOverlapWithDirection(gameboard, x, y, d, length) && checkOverflow(x, y, d, length);
			if (valid){
				struct boat comp = placeBoat(gameboard, x, y, d, length, id);
				fleet[boatsPlaced]=comp;
				boatsPlaced++;
				id++;
				if (boatsPlaced==1){
					length--;
				} else if (boatsPlaced==2){
					length--;
				} else if (boatsPlaced==4){
					length--;
				}
			}
		}
	}

}

/**
 * @brief creates a lookup table to find what coordinate matches a boat
 * @param fleet
 */
struct coordinatesToBoat *createCoordinateToBoatTable(struct boat *fleet){
	struct coordinatesToBoat *table=malloc(sizeof(struct coordinatesToBoat)*17);
	int pos=0;
	for (int i=0; i<5; i++){
		
		int x=fleet[i].x;
		int y=fleet[i].y;
		int direction=fleet[i].direction;
		int length=fleet[i].length;
		
		while (length!=0){
			struct coordinatesToBoat val = {i, x, y};
			table[pos]=val;
			pos++;
			if (direction==3){
				y++;
			} else if (direction==2){
				y--;
			} else if (direction == 0){
				x--;
			} else {
				x++;
			}
			length--;
		}
	}
}

/**
 * @brief function gets user input to determine coordinates of boat
 * @param pos used to indicate which coordinates will be grabbed, be it "first x", "first y", "last x", or "last y"
 */
void getHitCoordinate(int gameboard[8][8]){
	bool valid = false;
	while (!valid){
		int x =-1;
		while (x<0 || x>7){
			printf("Please enter the x coordinate of where you want to hit: ");
			scanf("%d", &x);
			if (x<0 || x>7){
				printf("Please enter a value between 0 and 7.");
			}
		}
		int y=-1;
		while (y<0 || y>7){
			printf("Please enter the y coordinate of where you want to hit: ");
			scanf("%d", &y);
			if (y<0 || y>7){
				printf("Please enter a value between 0 and 7.");
			}
		}
		if (gameboard[y][x]>=2 ){
			printf("you've already tried hitting this spot! Try a different coordinate \n");
		} else if (gameboard[y][x]==1){
			printf("HIT!");
			gameboard[y][x]=2;
			return;
			//logic to check if the boat is sunk
		} else {
			printf("Nothing is there...");
			gameboard[y][x]=4;
			return;
		}
	}
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
	
	struct boat *fleetPlayer = populatePlayerBoard(gameboardPlayer);
	struct boat *fleetComp = populateComputerBoard(gameboardComputer);
	
	struct coordinatesToBoat *lookupPlayer = createCoordinateToBoatTable(fleetPlayer);
	struct coordinatesToBoat *lookupComp = createCoordinateToBoatTable(fleetComp);
	
	bool win=false;
	while(!win){
		printf("**********************************************************\n\n\n\n");
		printf("Your turn!\n");
		printGameBoardInPlay(gameboardComputer);
		getHitCoordinate("x");
	}
	
	return 0;
}




