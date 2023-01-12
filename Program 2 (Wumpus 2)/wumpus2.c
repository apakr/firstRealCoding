/*
			Program 2: Wumpus 2 (Dynamically Allocated Arrays)
			Course: CS 211, UIC, Fall 2022, Thurs 8pm Lab
			System: VS Code
			Author: Al Pakrosnis
*/

#include <stdio.h>
#include <stdlib.h>		// for srand
#include <ctype.h>      // for toupper
#include <time.h>       // for time in srand(time(0))
#include <stdbool.h>	// for the bool type in C

#define NUMBER_OF_ROOMS 20 // Used because I had trouble getting my random numbers to match on the test cases so I used this; it did end up making a difference so I have to keep it, even though I only use it once
//--------------------------------------------------------------------------------
struct GameInfo{
	int moveNumber;  // Counts up from 1, incrementing for each move
	int personRoom;  // Room 1..20 the person currently is in
	int wumpusRoom;  // Room 1..20 the Wumpus is in
	int pitRoom1;    // Room 1..20 the first pit is in
	int pitRoom2;    // Room 1..20 the second pit is in
	int arrowRoom;	 // Room 1..20 the arrow is in
	int batRoom1;	 // Room 1..20 the first bat is in
	int batRoom2;	 // Room 1..20 the second bat is in
	bool hasArrow; // Determines whether the player has collected the arrow
	bool running; // Used to keep the main "do-while" function while the game should be running - allows for the game to end
};

//--------------------------------------------------------------------------------
int areRoomsUnique(int randomValue, int*values, int limit){ // used to figure out if the random values in an array are unique. Is a helper functoin for setUniqueValues
	int returnValue = 0;
    
    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == (*(values+i))) {
            returnValue = 1;   // Returns 1 if the value is already present is already there
            break;
        }
    }
    
    return returnValue;
}

//--------------------------------------------------------------------------------
void setUniqueValues(int*values, int num){ // takes a dynamically allocated array and a number of values to randomize as parameters, then creates "num" number of unique numbers in the array from 1 to 20
	int randomValue = -1;
	for( int i = 0; i<num; i++) {
        do {
            randomValue = rand() % NUMBER_OF_ROOMS + 1;   // random number 1..20
        } while (areRoomsUnique(randomValue, values, i)==1);
        *(values+i) = randomValue;
    }
}

//--------------------------------------------------------------------------------
void assignRooms(struct GameInfo *gameInfo){ //creates random rooms and assigns them to each of the objects rooms in the game
	int* values;
	values = (int*)malloc(7*sizeof(int));
	setUniqueValues(values, 7);
	gameInfo->personRoom = *values;   
	gameInfo->wumpusRoom = *(values+1);
	gameInfo->pitRoom1 = *(values+2);
	gameInfo->pitRoom2 = *(values+3);
	gameInfo->batRoom1 = *(values+4);
	gameInfo->batRoom2 = *(values+5);
	gameInfo->arrowRoom = *(values+6);
	gameInfo->hasArrow = false; 
	gameInfo->running = true;
	free(values);
}

//--------------------------------------------------------------------------------
int **createCave(){ // creates the dynamically allocated 2D array that will be used to store all the rooms and their adjacent rooms
// I could have included this as an object in my gameInfo structure but chose not to
	int **cave = (int**)malloc(21*sizeof(int*));
	if (cave == NULL){
		return NULL;
	} //makes sure to return null if there isnt enough space for malloc
	for(int j=1; j<=21; j++){ //this for loop goes through each room
		cave[j] = (int*)malloc(3*sizeof(int));
		for(int k = 0; k<3; k++){ // this for loop goes through each room's adjacent rooms and assigns them
			switch(j){
				case 1: switch(k){ //room 1
					case 0: *(*(cave+j)+k) = 2;	break;
					case 1: *(*(cave+j)+k) = 5;	break;
					case 2: *(*(cave+j)+k) = 8;	break;
				} break;
				case 2: switch(k){ //room 2
					case 0: *(*(cave+j)+k) = 1;	break;
					case 1: *(*(cave+j)+k) = 3; break;
					case 2: *(*(cave+j)+k) = 10; break;
				} break;
				case 3: switch(k){ //room 3
					case 0: *(*(cave+j)+k) = 2; break;
					case 1: *(*(cave+j)+k) = 4; break;
					case 2: *(*(cave+j)+k) = 12; break;
				} break;
				case 4: switch(k){ //room 4
					case 0: *(*(cave+j)+k) = 3;	break;
					case 1: *(*(cave+j)+k) = 5; break;
					case 2: *(*(cave+j)+k) = 14; break;
				} break;
				case 5: switch(k){ //room 5
					case 0: *(*(cave+j)+k) = 1;	break;
					case 1: *(*(cave+j)+k) = 4; break;
					case 2: *(*(cave+j)+k) = 6; break;
				} break;
				case 6: switch(k){ //room 6
					case 0: *(*(cave+j)+k) = 5;	break;
					case 1: *(*(cave+j)+k) = 7; break;
					case 2: *(*(cave+j)+k) = 15; break;
				} break;
				case 7: switch(k){ //room 7
					case 0: *(*(cave+j)+k) = 6;	break;
					case 1: *(*(cave+j)+k) = 8; break;
					case 2: *(*(cave+j)+k) = 17; break;
				} break;
				case 8: switch(k){ //room 8
					case 0: *(*(cave+j)+k) = 1;	break;
					case 1: *(*(cave+j)+k) = 7; break;
					case 2: *(*(cave+j)+k) = 9; break;
				} break;
				case 9: switch(k){ //room 9
					case 0: *(*(cave+j)+k) = 8;	break;
					case 1: *(*(cave+j)+k) = 10; break;
					case 2: *(*(cave+j)+k) = 18; break;
				} break;
				case 10: switch(k){ //room 10
					case 0: *(*(cave+j)+k) = 2;	break;
					case 1: *(*(cave+j)+k) = 9; break;
					case 2: *(*(cave+j)+k) = 11; break;
				} break;
				case 11: switch(k){ //room 11
					case 0: *(*(cave+j)+k) = 10; break;
					case 1: *(*(cave+j)+k) = 12; break;
					case 2: *(*(cave+j)+k) = 19; break;
				} break;
				case 12: switch(k){ //room 12
					case 0: *(*(cave+j)+k) = 3;	break;
					case 1: *(*(cave+j)+k) = 11; break;
					case 2: *(*(cave+j)+k) = 13; break;
				} break;
				case 13: switch(k){ //room 13
					case 0: *(*(cave+j)+k) = 12; break;
					case 1: *(*(cave+j)+k) = 14; break;
					case 2: *(*(cave+j)+k) = 20; break;
				} break;
				case 14: switch(k){ //room 14
					case 0: *(*(cave+j)+k) = 4;	break;
					case 1: *(*(cave+j)+k) = 13; break;
					case 2: *(*(cave+j)+k) = 15; break;
				} break;
				case 15: switch(k){ //room 15
					case 0: *(*(cave+j)+k) = 6;	break;
					case 1: *(*(cave+j)+k) = 14; break;
					case 2: *(*(cave+j)+k) = 16; break;
				} break;
				case 16: switch(k){ //room 16
					case 0: *(*(cave+j)+k) = 15; break;
					case 1: *(*(cave+j)+k) = 17; break;
					case 2: *(*(cave+j)+k) = 20; break;
				} break;
				case 17: switch(k){ //room 17
					case 0: *(*(cave+j)+k) = 7;	break;
					case 1: *(*(cave+j)+k) = 16; break;
					case 2: *(*(cave+j)+k) = 18; break;
				} break;
				case 18: switch(k){ //room 18
					case 0: *(*(cave+j)+k) = 9;	break;
					case 1: *(*(cave+j)+k) = 17; break;
					case 2: *(*(cave+j)+k) = 19; break;
				} break;
				case 19: switch(k){ //room 19
					case 0: *(*(cave+j)+k) = 11; break;
					case 1: *(*(cave+j)+k) = 18; break;
					case 2: *(*(cave+j)+k) = 20; break;
				} break;
				case 20: switch(k){ //room 20
					case 0: *(*(cave+j)+k) = 13; break;
					case 1: *(*(cave+j)+k) = 16; break;
					case 2: *(*(cave+j)+k) = 19; break;
				} break; //after looking at other people's code and after finishing up my code, I realize I could created my cave in a less cluttered way than nested cases and for loops, but this was one of the first things that I did in this project and I was really proud of it so I decided to keep it in; from what I understand it doesn't make the code slower, it just is long in the source code
			}

		};
	};
	return cave;
}

//--------------------------------------------------------------------------------
void displayCave() //displays cave when user prompts it to
{
    printf( "\n"
			"       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}

//--------------------------------------------------------------------------------
void displayInstructions() //displays instructions and cave when user prompts it to
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()

//--------------------------------------------------------------------------------
void displayRoomInfo(struct GameInfo gameInfo, int** cave){ //this function is used to inform the player of their position and the hazards around them

	 // Retrieve player's current room number and display it
    int currentRoom = gameInfo.personRoom;
    printf("You are in room %d. ", currentRoom);
    
    // Retrieve index values of all 3 adjacent rooms
    int room1 = *(*(cave+currentRoom)+0);
    int room2 = *(*(cave+currentRoom)+1);
    int room3 = *(*(cave+currentRoom)+2);
    
    // Display hazard detection message if Wumpus is in an adjacent room
    int wumpusRoom = gameInfo.wumpusRoom;
    if( room1 == wumpusRoom || room2 == wumpusRoom || room3 == wumpusRoom) {
        printf("You smell a stench. ");
    }
    
    // Display hazard detection message if a pit is in an adjacent room
    int pit1Room = gameInfo.pitRoom1;
    int pit2Room = gameInfo.pitRoom2;
    if( room1 == pit1Room || room1 == pit2Room ||
        room2 == pit1Room || room2 == pit2Room ||
        room3 == pit1Room || room3 == pit2Room
      ) {
        printf("You feel a draft. ");
    }

	//Display hazard detection message if bats are in an adjacent room
	int bat1Room = gameInfo.batRoom1;
	int bat2Room = gameInfo.batRoom2;
	if( room1 == bat1Room || room1 == bat2Room|| room2 == bat1Room || room2 == bat2Room || room3 == bat1Room|| room3 == bat2Room){
		printf("You hear rustling of bat wings. ");
	}
    printf("\n\n");
}

//--------------------------------------------------------------------------------
void resetLocations(struct GameInfo *gameInfo){ // this functions allows the user to choose what rooms they want all the objects to be in
	int pR, wR, ptR1, ptR2, bR1, bR2, aR = 1;
	// Prompt for user when they choose to reset
	printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
	scanf(" %d %d %d %d %d %d %d",&gameInfo->personRoom,&gameInfo->wumpusRoom,&gameInfo->pitRoom1,&gameInfo->pitRoom2,&gameInfo->batRoom1,&gameInfo->batRoom2,&gameInfo->arrowRoom);
	if(gameInfo->arrowRoom == -1){
		gameInfo->hasArrow = true; // this must be updated because the player might choose for the arrow's room to change to -1, which would mean that the player has the arrow, but this if statement is needed to make sure that the game knows the player then has the arrow
	}
	printf("\n");
}

//--------------------------------------------------------------------------------
void moveToRoom(struct GameInfo *gameInfo, int inptNum, int** cave){ // this is one of the most important functions; it is used to move the player from room to room as well as update the game if the player happens to move into a room where a hazard or arrow is
	gameInfo->personRoom = inptNum; //moves the player
	if(gameInfo->personRoom == gameInfo->wumpusRoom){ //checks if player moved into wumpus room and does the according action depending on the value of the room
		if(gameInfo->personRoom % 2 == 1){
			printf( "You hear a slithering sound, as the Wumpus slips away. \n"
			"Whew, that was close! \n");
			gameInfo->wumpusRoom = *(*(cave+gameInfo->personRoom)+0);
		} else {
			printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
			"It is over.\n");
			gameInfo->running = false;
			return;
		}
	}
	if(gameInfo->personRoom == gameInfo->pitRoom1 || gameInfo->personRoom == gameInfo->pitRoom2){ //checks if player moved into a room with a pit and kills the player ending the game
		// Message when the player dies by falling into a pit
		printf("Aaaaaaaaahhhhhh....   \n");
		printf("    You fall into a pit and die. \n");
		gameInfo->running = false;
		return;
	}
	if(gameInfo->personRoom == gameInfo->arrowRoom){ //checks if player moved into a room with the arrow and picks it up
		gameInfo->hasArrow = true;
		gameInfo->arrowRoom = -1;
		// Player picks up arrow
		printf("Congratulations, you found the arrow and can once again shoot.\n");
	}
	bool bR1Hit = false; // these two variables are created on the stack and are used within the function to differentiate between what bats the player met
	bool bR2Hit = false;
	if(gameInfo->personRoom == gameInfo->batRoom1){
		bR1Hit = true;
	}
	if(gameInfo->personRoom == gameInfo->batRoom2){
		bR2Hit = true;
	}
	if(bR1Hit||bR2Hit){
		int batRoomOneOld = gameInfo->batRoom1;
		int* singleBats = (int*)malloc(2*sizeof(int)); //creates a dynamically allocated array to store random values in for the player and the bats to be transported into
		setUniqueValues(singleBats,2);
		if(batRoomOneOld == *(singleBats+1)){ // this along with int batRoomOneOld is used to pass test case 7
			int* randomRoom = (int*)malloc(1*sizeof(int));
			setUniqueValues(randomRoom,1);
			*(singleBats+1) = *randomRoom;
			free(randomRoom);
		}
		if(bR1Hit&&bR2Hit){ // this isnt necesarry but when I was coding it I created it and it doesn't interfere with the test cases so I decided to keep it; this is the code for if a player enters a room where both bats are, something that would only happen randomly a few moves into the game
			int* bothBats = (int*)malloc(3*sizeof(int)); // I would use the same dynamic array as above except for the fact that it messes up the test cases when I do that so thats why I have two different dynamic arrays
			setUniqueValues(bothBats, 3);
			gameInfo->batRoom1 = *(bothBats+1);
			gameInfo->batRoom2 = *(bothBats+2);
			printf("Woah... you're flying! \n");
			moveToRoom(gameInfo, *bothBats, cave);
			free(bothBats);
		} else if (bR1Hit) { // does the according action if the player entered a room with bats
			gameInfo->batRoom1 = *(singleBats+1);
			// Message when bats transport player
			printf("Woah... you're flying! \n");
   			printf("You've just been transported by bats to room %d.\n", *singleBats); 
			moveToRoom(gameInfo, *singleBats, cave); //the functions recurses in case the player is randomly sent into a room where there was already a hazard or arrow present
		} else if (bR2Hit) { // copy of the first second part of the if statement except for bat2 instead of bat1
			gameInfo->batRoom2 = *(singleBats+1);
			// Message when bats transport player
			printf("Woah... you're flying! \n");
    		printf("You've just been transported by bats to room %d.\n", *singleBats); 
			moveToRoom(gameInfo, *singleBats, cave);
		}
		free(singleBats);
	}
}

//--------------------------------------------------------------------------------
void doesArrowKillPlayer(struct GameInfo *gameInfo, bool intentional){ //checks if the arrow is shot into the same room as the player; is a helper function to a helper function
	if(gameInfo->arrowRoom == gameInfo->personRoom && (intentional == false)){
		// Arrow ricochets, and kills person
		printf( "You just shot yourself, and are dying.\n" //gets printed if the arrow ricoshets unintentionally into the room where the player is in
        		"It didn't take long, you're dead.\n");
		gameInfo->running = false;
		return; // is used to end the execution of this function if the player or wumpus dies and the game ends
	} else if (gameInfo->arrowRoom == gameInfo->personRoom && (intentional == true)){
		// Arrow killed player
		printf( "You just shot yourself.  \n"
      			"Maybe Darwin was right.  You're dead.\n"); //gets printed if the player indicated their room when they were entering the rooms to shoot into
		gameInfo->running = false;
		return; // is used to end the execution of this function if the player or wumpus dies and the game ends
	}
}

//--------------------------------------------------------------------------------
void doesArrowKillWumpus(struct GameInfo *gameInfo, bool intentional){ //checks if the arrow is shot into the same room as the wumpus; is a helper function to a helper function
	if(gameInfo->arrowRoom == gameInfo->wumpusRoom && (intentional == true)){
		// Arrow killed Wumpus
		printf( "Wumpus has just been pierced by your deadly arrow! \n" //gets printed if the player indicated the wumpus room when they were entering the rooms to shoot into
        	    "Congratulations on your victory, you awesome hunter you.\n");
		gameInfo->running = false;
		return; // is used to end the execution of this function if the player or wumpus dies and the game ends
	} else if (gameInfo->arrowRoom == gameInfo->wumpusRoom && (intentional == false)){
		// Arrow ricochets, and kills Wumpus
		printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n" //gets printed if the arrow ricoshets unintentionally into the room where the wumpus is in
            	"Accidental victory, but still you win!\n");
		gameInfo->running = false;
		return; // is used to end the execution of this function if the player or wumpus dies and the game ends
	}
}

//--------------------------------------------------------------------------------
void roomIsAdjacent(struct GameInfo *gameInfo, int room){ // is a helper function for when the arrow doesn't ricoshet, moves the arrow and then checks if that arrow kills the wumpus or the player
	gameInfo->arrowRoom = room;
	doesArrowKillPlayer(gameInfo, true);
	doesArrowKillWumpus(gameInfo, true);
}

//--------------------------------------------------------------------------------
void roomIsNotAdjacent(struct GameInfo *gameInfo, int **cave, int room){ // is a helper function for when the arrow ricoshets, moves the arrow and then checks if that arrow kills the wumpus or the player
	// Attempt to shoot arrow through room that is not adjacent
	printf("Room %d is not adjacent.  Arrow ricochets...\n", room);
	gameInfo->arrowRoom = *(*(cave+gameInfo->arrowRoom)+0);
	doesArrowKillPlayer(gameInfo, false);
	doesArrowKillWumpus(gameInfo, false);
}

//--------------------------------------------------------------------------------
bool isRoomAdjacentToArrow(struct GameInfo *gameInfo, int **cave, int room){ // is a helper function that checks if the room entered by the player to shoot into is adjacent to the room the arrow is currently in
	if(room == *(*(cave+gameInfo->arrowRoom)+0) || room == *(*(cave+gameInfo->arrowRoom)+1) || room == *(*(cave+gameInfo->arrowRoom)+2)){
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
void shootArrow(struct GameInfo *gameInfo, int numMoves, int* rooms, int **cave){ // is the main function that shoots the arrow
	if(gameInfo->arrowRoom != gameInfo->personRoom) gameInfo->hasArrow = false; //makes sure that the arrow and the player share the same room when the arrow is intially shot; this was added retroactively to make test cases work
	gameInfo->arrowRoom = gameInfo->personRoom;
	switch (numMoves){ // this switch runs each inputted room through a series of if statements depending on the number of rooms the arrow should go through
		case 1:
			if(isRoomAdjacentToArrow(gameInfo, cave, *rooms)){
				roomIsAdjacent(gameInfo, *rooms);
			} else {
				roomIsNotAdjacent(gameInfo, cave, *rooms);
			}
		break;
		case 2:
			if(isRoomAdjacentToArrow(gameInfo, cave, *rooms)){
				roomIsAdjacent(gameInfo, *rooms);
				if(gameInfo->running == false) return; // is used to end the execution of this function if the player or wumpus dies and the game ends, used in multiple places throughout this function because it is needed in multiple places throughout the function
				if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+1))){
					roomIsAdjacent(gameInfo, *(rooms+1));
				} else {
					roomIsNotAdjacent(gameInfo, cave, *(rooms+1));
				}
			} else {
				roomIsNotAdjacent(gameInfo, cave, *rooms);
				if(gameInfo->running == false) return;
				if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+1))){
					roomIsAdjacent(gameInfo, *(rooms+1));
				} else {
					roomIsNotAdjacent(gameInfo, cave, *(rooms+1));
				}
			}
		break;
		case 3:
			if(isRoomAdjacentToArrow(gameInfo, cave, *rooms)){
				roomIsAdjacent(gameInfo, *rooms);
				if(gameInfo->running == false) return;
				if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+1))){
					roomIsAdjacent(gameInfo, *(rooms+1));
					if(gameInfo->running == false) return;
					if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+2))){
						roomIsAdjacent(gameInfo, *(rooms+2));
					} else {
						roomIsNotAdjacent(gameInfo, cave, *(rooms+2));
					}
				} else {
					roomIsNotAdjacent(gameInfo, cave, *(rooms+1));
					if(gameInfo->running == false) return;
					if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+2))){
						roomIsAdjacent(gameInfo, *(rooms+2));
					} else {
						roomIsNotAdjacent(gameInfo, cave, *(rooms+2));
					}
				}
			} else {
				roomIsNotAdjacent(gameInfo, cave, *rooms);
				if(gameInfo->running == false) return;
				if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+1))){
					roomIsAdjacent(gameInfo, *(rooms+1));
					if(gameInfo->running == false) return;
					if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+2))){
						roomIsAdjacent(gameInfo, *(rooms+2));
					} else {
						roomIsNotAdjacent(gameInfo, cave, *(rooms+2));
					}
				} else {
					roomIsNotAdjacent(gameInfo, cave, *(rooms+1));
					if(gameInfo->running == false) return;
					if(isRoomAdjacentToArrow(gameInfo, cave, *(rooms+2))){
						roomIsAdjacent(gameInfo, *(rooms+2));
					} else {
						roomIsNotAdjacent(gameInfo, cave, *(rooms+2));
					}
				}
			}
		break;
	}
	gameInfo->wumpusRoom = *(*(cave+gameInfo->wumpusRoom)+0); // moves the wumpus to the lowest adjacent room after the arrow is shot
	// The code below was created to check whether the player and the wumpus were in the same room when the arrow was shot, and then to do the adequate moves if that happens. However, after asking if I should do this on Piazza I was told by an instructor that it isn't necessary and the wumpus and person will be allowed to exist in the same room at the same time for ths once case.
	// if(gameInfo->wumpusRoom == gameInfo->personRoom && (gameInfo->personRoom % 2 == 0)){
	// 	//kill player
	// } else if (gameInfo->wumpusRoom == gameInfo->personRoom && gameInfo->personRoom % 2 == 1){
	// 	gameInfo->wumpusRoom = *(*(cave+gameInfo->wumpusRoom)+0);
	// }
}

//--------------------------------------------------------------------------------
int main(void) {
    srand(1); // allows for random numbers
	int inptNum; // used to know what the user inputs
	struct GameInfo gameInfo; // holds all the current information of the game including rooms and whether the game should end or if the player has the arrow
	int** cave = createCave(); // creates the cave with all of its connections
	gameInfo.moveNumber = 1; // starts the moveNumber counter
	assignRooms(&gameInfo); // assigns random rooms each time as well as sets hasArrow and running
	do{ //do while loop to keep the game running, ends when the player or wumpus are killed
		displayRoomInfo(gameInfo, cave); //displays the room information each time a new step is required of the palyer
		printf("%d. Enter your move (or 'D' for directions): ", gameInfo.moveNumber);	// prompt for user to enter their move
		char inpt; // holds the user's move
		scanf(" %c", &inpt); // receives the user's move
		inpt = toupper(inpt); //turns all input into capital letters
		if (inpt == 'D'){ //directions
			displayCave(); 
			displayInstructions();
		} else if (inpt == 'P'){ //map
			displayCave();
		} else if (inpt == 'M'){ //move
			scanf(" %d", &inptNum); // receives what room the user wants to enter
			if(inptNum == *(*(cave+gameInfo.personRoom)+0) || inptNum == *(*(cave+gameInfo.personRoom)+1) || inptNum == *(*(cave+gameInfo.personRoom)+2)){ //checks whether the room the user entered is adjacent or not and does the according action
				gameInfo.moveNumber = gameInfo.moveNumber + 1; //increments the move number
				moveToRoom(&gameInfo, inptNum, cave); //calls the function that moves the player
			} else {
				printf("Invalid move.  Please retry. \n");
			}
		} else if (inpt == 'S'){ //shoot
			gameInfo.moveNumber = gameInfo.moveNumber + 1; //increments the move number
			if(gameInfo.hasArrow){ //checks if the player has the arrow to shoot and stops you from shooting if you don't have an arrow
				// Prompt user to enter input
				printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
				scanf("%d",&inptNum);
				int* rooms = (int*)malloc(3*sizeof(int)); //allocates memory for a dynamically allocated array that holds the rooms that the player wants to shoot their arrows through
				switch (inptNum){
					case 1: //goes through this case if the player wants to shoot through one room
						scanf(" %d", &(*rooms));
						shootArrow(&gameInfo, 1, rooms, cave);
						break;
					case 2: //goes through this case if the player wants to shoot through two rooms
						scanf(" %d %d", &(*rooms),&(*(rooms+1)));
						shootArrow(&gameInfo, 2, rooms, cave);
						break;
					case 3: //goes through this case if the player wants to shoot through three rooms
						scanf(" %d %d %d", &(*rooms), &(*(rooms+1)), &(*(rooms+2)));
						shootArrow(&gameInfo, 3, rooms, cave);
						break;
					default: // User enters more than 3 rooms to shoot arrow through
						printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
						scanf(" %d %d %d", &(*rooms), &(*(rooms+1)), &(*(rooms+2)));
						shootArrow(&gameInfo, 3, rooms, cave);
				}
				free(rooms);
			} else {
				// Attempt to shoot arrow you don't have
				printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
			}
		} else if (inpt == 'C'){ // Message for menu option C (cheating).
			printf( "Cheating! Game elements are in the following rooms: \n"
    				"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    				"%4d %5d %6d %5d %5d %5d %5d \n\n",gameInfo.personRoom,gameInfo.wumpusRoom,gameInfo.pitRoom1,gameInfo.pitRoom2,gameInfo.batRoom1,gameInfo.batRoom2,gameInfo.arrowRoom);
		} else if (inpt == 'R'){ //reset
			resetLocations(&gameInfo);
		} else if (inpt == 'X'){ //exit
			gameInfo.running = false;
		} else {
			printf("Invalid move.  Please retry. \n");	// message for invalid move
		}
	} while ((gameInfo.running) == true);
	printf("\nExiting Program ...\n"); // Message that prints at the end of the program when the game ends
	return 0;
}