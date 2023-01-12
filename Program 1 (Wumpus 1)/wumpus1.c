/*
        Program 1: Wumpus, version 1 (fixed size array)

        Course: CS 211, Fall 2022. Thurs 8pm lab
        System: Dell with Windows 10 on replit
        Author: Al Pakrosnis
*/
#include <ctype.h> // to convert lowercase to uppcase
#include <stdio.h>
#include <stdlib.h> // for srand
#include <time.h>   // allows for better randomization
int cave[20][3] = {{2, 5, 8},    {1, 3, 10},  {2, 4, 12},   {3, 5, 14},
                   {1, 4, 6},    {5, 7, 15},  {6, 8, 17},   {1, 7, 9},
                   {8, 10, 18},  {2, 9, 11},  {10, 12, 19}, {3, 11, 13},
                   {12, 14, 20}, {4, 13, 15}, {6, 14, 16},  {15, 17, 20},
                   {7, 16, 18},  {9, 17, 19}, {11, 18, 20}, {13, 16, 19}}; // global cave array so that the information can be used by any functin anywhere

//--------------------------------------------------------------------------------
void displayCave() {
  printf("       ______18______             \n"
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
} // a visual aide for understanding the cave

//--------------------------------------------------------------------------------
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you    "
         "fall and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' followed by a space and room number to guess which room "
         "Wumpus is in, to win or lose the game!         \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()
void assignRoom(int *phaz1, int *phaz2, int *pWumpus, int *pplayerRoom,
                int *haz1Num, int *haz2Num, int *wumpusNum,
                int *playerRoomNum) {
  int rand1, rand2, rand3, rand4;
  do {
    srand((unsigned int)time(0)); // different way to create a random value in the code; pretty much better than the one given to us :D
    int randomValue = rand() % 20 + 1;
    rand1 = randomValue;
    randomValue = rand() % 20 + 1;
    rand2 = randomValue; // each dynamically allocated rand is assigned a fresh random variable
    randomValue = rand() % 20 + 1;
    rand3 = randomValue;
    randomValue = rand() % 20 + 1;
    rand4 = randomValue;
  } while ((rand1 == rand2) || (rand1 == rand3) || (rand1 == rand4) ||
           (rand2 == rand3) || (rand2 == rand4) || (rand3 == rand4)); // continually randomizes rooms in the cave until four unique rooms are selected
  *haz1Num = rand1;
  *haz2Num = rand2;
  *wumpusNum = rand3;
  *playerRoomNum = rand4;
  for (int i = 0; i < 3; i++) {
    phaz1[i] = cave[rand1 - 1][i];
  }
  for (int i = 0; i < 3; i++) {
    phaz2[i] = cave[rand2 - 1][i];
  } // each of these for loops copies the adjecent rooms for each room from the cave data and copies it into the array variables from main
  for (int i = 0; i < 3; i++) {
    pWumpus[i] = cave[rand3 - 1][i];
  }
  for (int i = 0; i < 3; i++) {
    pplayerRoom[i] = cave[rand4 - 1][i];
  }
} // this function takes all the established variables from main and assigns them unqiue rooms

void roomCheck(int *playerRoom, int *phaz1Num, int *phaz2Num, int *pWumpusNum) {
  for (int i = 0; i < 3; i++){
    if (playerRoom[i] == *pWumpusNum){
      printf("You smell a stench. ");
    }
  }
  for (int i = 0; i < 3; i++) {
    if ((playerRoom[i] == *phaz1Num) || (playerRoom[i] == *phaz2Num)) {
      printf("You feel a draft. ");
    } 
  }
} // roomCheck prints the current warnings of the room the player would currently be in, it does so using two simple search algorithms

void movePlayer(int inptNum, int*playerRoom, int*playerRoomNum) {
  *playerRoomNum = inptNum;
  for (int i = 0; i < 3; i++) {
    playerRoom[i] = cave[inptNum - 1][i];
  }
} // this function updates the variables that are responsible for knowing the players variables when needbe

void moveWumpus(int *wumpus, int *pWumpusNum) {
  int lowest = 20;
  for (int i = 0; i < 3; i++) {
    if (wumpus[i] < lowest) {
      lowest = wumpus[i];
    }}
  for (int i = 0; i < 3; i++){
    wumpus[i] = cave[lowest - 1][i];
    }
  *pWumpusNum = lowest;
} // this function finds the lowest numbered adjecent room to the wumpus and moves it there by updating the variables that are responsible for knowing the wumpus' location

void withWumpus(int inptNum, int* pWumpusNum, int* wumpus, int* pstate){
  if (inptNum == *pWumpusNum) {
        if (*pWumpusNum % 2 == 0) {
          printf("You briefly feel a slimy tentacled arm as your neck is   "          "      snapped. \n" "It is over.\n");
          printf("\nExiting Program ...\n");
          *pstate = 0;
          } else if (*pWumpusNum % 2 == 1){
          printf("You hear a slithering sound, as the Wumpus slips away.                     "
                 "      \n"
                 "Whew, that was close! \n");
          moveWumpus(wumpus, pWumpusNum); // a void function being called within the original void function
          }
  }
} // this function is used to find out whether the player has moved into a room where the wumpus is, and subsequently starts the next steps if the player is

void resetItems(int* playerRoom, int* playerRoomNum, int rplayer, int*wumpus, int*pWumpusNum, int rWumpus, int* haz1, int* phaz1Num, int rhaz1, int*haz2, int*phaz2Num, int rhaz2){
  *playerRoomNum = rplayer;
  *pWumpusNum = rWumpus;
  *phaz1Num = rhaz1;
  *phaz2Num = rhaz2;
  for (int i = 0; i < 3; i++) {
    playerRoom[i] = cave[rplayer - 1][i];
  }
  for (int i = 0; i < 3; i++) {
    wumpus[i] = cave[rWumpus - 1][i];
  }
  for (int i = 0; i < 3; i++) {
    haz1[i] = cave[rhaz1 - 1][i];
  }
  for (int i = 0; i < 3; i++) {
    haz2[i] = cave[rhaz2 - 1][i];
  }
  printf("\n");
}// pretty self explanatory, this function takes the input from the user for where the stuff in the game should be located, and updates the variables that know the location of the stuff accordingly

//--------------------------------------------------------------------------------
int main(void) {

  int haz1[3], haz2[3], wumpus[3], playerRoom[3];
  int haz1Num, haz2Num, wumpusNum, playerRoomNum;
  int state = 1; // provides the ability to end the while loop, within a function or running segment of code, which will end the whole program
  int step = 1; // creates the step number for each proper move you make
  int* pstate = &state;
  int *phaz1Num = &haz1Num;
  int *phaz2Num = &haz2Num;
  int *pWumpusNum = &wumpusNum;
  int *pplayerRoomNum = &playerRoomNum;
  assignRoom(haz1, haz2, wumpus, playerRoom, phaz1Num, phaz2Num, pWumpusNum, pplayerRoomNum); // all the variables that will be used to identify rooms and objects and their surrounding rooms were just created and then assigned values
  char inpt;
  int inptNum; // both input values are used to get the input from the user
  
  while (state != 0) { // this while loops runs through the whole program so   that the user can be asked for input many times and actually play the game
    printf("You are in room %d. ", playerRoomNum); // prints current room of player
    roomCheck(playerRoom, phaz1Num, phaz2Num, pWumpusNum); // prints warnings
    printf("\n\n%d. Enter your move (or 'D' for directions): ", step); //prompt for user to enter their move
    
    scanf(" %c", &inpt); 
    inpt = toupper(inpt); // scans and turns all inputs into uppcase
    
      if (inpt == 'M') {
        scanf(" %d", &inptNum);
        } // allows for adding a number to the information inputted
    
      if (inpt == 'D') { // creates an extended else-if statement to deal with whatever character can be passed in with the same structure
        displayInstructions(); // displays instructions 
        } else if (inpt == 'C') {
          printf("Cheating! Game elements are in the following rooms: \n"
               "Player Wumpus Pit1 Pit2  \n"
               "%4d %7d %5d %5d \n\n",
               playerRoomNum, wumpusNum, haz1Num, haz2Num);
        } else if (inpt == 'P') {
          displayCave(); // displays cave
        } else if (inpt == 'R') {
          int rplayer, rWumpus, rhaz1, rhaz2; // creates dynamic variables to easily store input so that it may be used in a called function
          // Prompt for user when they choose to reset
          printf("Enter the room locations (1..20) for player, Wumpus, pit1,   and pit2: ""\n");
          scanf(" %d %d %d %d", &rplayer, &rWumpus, &rhaz1, &rhaz2);
          resetItems(playerRoom, &playerRoomNum, rplayer, wumpus, &wumpusNum, rWumpus, haz1, &haz1Num, rhaz1, haz2, &haz2Num, rhaz2); // sends the aforementioned variables to the function along with the identifying variables form the beginning of main
        } else if (inpt == 'G') { // the guessing code is quite simple; you guess it right you win, you guess it wrong and you lose, in both cases the program ends
          int temp;
          printf("Enter room (1..20) you think Wumpus is in: ");
          scanf(" %d", &temp);
          if (temp == wumpusNum) {
            printf("You won!\n");
            printf("\nExiting Program ...\n");
            state = 0;
            } else {
              printf("You lost.\n");
              printf("\nExiting Program ...\n");
              state = 0;
            }
        } else if (inpt == 'X') {
            // Message that prints at the end of the program
            printf("\nExiting Program ...\n");
            state = 0; // example of the state variable being used to end the while loop, which then ends the program
        } else if (inpt == 'M') {
          if ((inptNum!=playerRoom[0])&&(inptNum!=playerRoom[1])&&(inptNum!=playerRoom[2])){
            printf("Invalid move. Please retry. \n"); // message for invalid entry
          } else {
            step = step + 1;
            if (inptNum == haz1Num || inptNum == haz2Num){ // you can only die from a pit once, so this ISN'T a function
                // Message when the player dies by falling into a pit
                printf("Aaaaaaaaahhhhhh....   \n");
                printf("    You fall into a pit and die. \n");
                printf("\nExiting Program ...\n");
                state = 0;
              } else {
                  withWumpus(inptNum, pWumpusNum, wumpus, pstate); // you can meet the wumpus many times so this IS a function
                  movePlayer(inptNum, playerRoom, &playerRoomNum); // you will also move many times so this IS also a function
              }
          }
        } else {
          printf("Invalid command.  Please retry. \n"); // message for when the person enters something that isn't a known comamand
        }
      };
  return 0;
}