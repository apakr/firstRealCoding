/*  
  Program 3: Wordle
  Course: CS 211, UIC, Fall 2022
  System(s): Replit, VS Code
  Authors: Philip Keith, Al Pakrosnis

  Links to wordle dictionary words at:
  https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/
*/

#include <stdio.h>
#include <stdlib.h> // for exit( -1)
#include <string.h>

typedef struct //defines a structure that contains the string array of the word itself and its score
{
    char *word;
    int score;
} wordStruct;

int compareFunction( const void * a, const void * b) {
    // Before using parameters we have cast them into the actual type they are in our program
    // and then extract the numerical value used in comparison
    int firstScore = ((wordStruct *)a)->score;
    int secondScore = ((wordStruct *)b)->score;
    char *firstWord = ((wordStruct *)a)->word;
    char *secondWord = ((wordStruct *)b)->word;

    if (firstScore != secondScore) {
        // We reverse the values, so the result is in descending vs. the otherwise ascending order
        // return firstScore - secondScore;   // ascending order
        return secondScore - firstScore;      // descending order
    }
    else {
        return strcmp(firstWord , secondWord);
    }
} //end compareFunction(..)

int getFileSize(const char *fileName) // Returns an int that denotes the size of the file given to it
{
    FILE *inFilePtr = fopen(fileName, "r"); // Connect logical name to filename
    char inputString[ 81];
    int fileWordCount = 0;

    if (inFilePtr == NULL) // Sanity check: ensure file open worked correctly
    {
        printf("Error: could not open %s for reading\n", fileName);
        exit(-1);
    }

    // Reads each word from file and prints it.  
    while (fscanf(inFilePtr, "%s", inputString) != EOF)
    {
        fileWordCount++;
    }

    // Closes the file
    fclose(inFilePtr);

    return fileWordCount;
}

void copyFileContents(wordStruct *output, const char *fileName, int startingIndex) //Copies file contents
{
    FILE *inFilePtr = fopen(fileName, "r"); // Connect logical name to filename
    char inputString[81];

    // Sanity check: ensure file open worked correctly
    if (inFilePtr == NULL)
    {
        printf("Error: could not open %s for reading\n", fileName);
        exit(-1);
    }

    while (fscanf(inFilePtr, "%s", inputString) != EOF)
    {
        output[startingIndex].word = (char *)malloc(sizeof(char *)); // Assigns space for word within each wordStruct
        strcpy(output[startingIndex].word, inputString);
        output[startingIndex].score = 0; // Initializes each score to 0
        startingIndex++;
    }

    // Closes the file
    fclose(inFilePtr);
}

int calculateWordScore(const char *inputWord, const char *answerWord) // Is a helper function to calculateScores, does the actual score calculation
{
    int score = 0;
    char tempGuess[6];
    char tempAns[6];

    strcpy(tempGuess, inputWord);
    strcpy(tempAns, answerWord);

    for (int i = 0; i < 5; i++) // Check matching letter in the right place
    {
        if (tempGuess[i] == tempAns[i])
        {
            tempGuess[i] = ' '; // For ease of use
            tempAns[i] = ' ';
            score += 3;
        }
    }

    for (int i = 0; i < 5; i++) // Check i letter in answerword against every letter in guessword
    {
        if (tempGuess[i] != ' ')
        {                               // If this letter was found to be an exact match we don't score it again
            for (int j = 0; j < 5; j++) // Go through letters in inputWord and check against i letter in answerWord
            {
                if (tempAns[j] != ' ' && tempGuess[i] == tempAns[j])
                { // Check if we are checking against a letter that hasn't been found yet
                    score += 1;
                    tempAns[j] = ' '; // Once a letter in answerword is found it won't count again
                    j = 5;            // Once we find that the letter exists we stop adding points for if it exists again
                }
            }
        }
    }
    // Check matching letter out of place
    return score;
}

void calculateScores(wordStruct *bestWords, wordStruct *answerList, int bestWordsSize, int answerListSize) // Calculates the scores for each word and assigns it to its struct score values
{
    for (int i = 0; i < bestWordsSize; i++)
    { // Indexes through answers after words is done
        int score = 0;
        for (int j = 0; j < answerListSize; j++)
        { // Indexes through bestWords first
            score += calculateWordScore(bestWords[i].word, answerList[j].word);
        }
        bestWords[i].score = score;
    }
}

void helperSwap(wordStruct *listToSort, int place){ // Is a helper function for the sort funciton which swaps the values
  int tempValue = listToSort[place].score;
  char *tempWord = listToSort[place].word;

  listToSort[place].score = listToSort[place+1].score;
  listToSort[place].word = listToSort[place+1].word;
  listToSort[place+1].score = tempValue;
  listToSort[place+1].word = tempWord;
}

void organizeScores(wordStruct *listToSort, int listSize){ //Sorts the words in descending order based on their score
  for(int i = 0; i < listSize-1; i++){
    for(int j = 0; j < listSize-i-1; j++){
      if(listToSort[j].score<listToSort[j+1].score){
        helperSwap(listToSort, j);
      }
    }
  }
}

void printTopScores(wordStruct *listToPrint, int listSize){ // Prints top scores
  for(int i = 0; i < listSize; i++){
    printf("%s %d\n", listToPrint[i].word, listToPrint[i].score);
    
    if(listToPrint[i].score>listToPrint[i+1].score)
      break;
  }
}

int getNumOfTop(wordStruct *listToPrint, int listSize){ //Returns the number of top words, essentially tells us if there is more than one top words as well as exactly how many
  int output = 0;
  for(int i = 0; i < listSize; i++){
    output++;
    if(listToPrint[i].score>listToPrint[i+1].score)
      break;
  }
  return output;
}
void fillTopWords(wordStruct *listToCopy, wordStruct *listToCopyOn, int size){ //Takes a wordStruct as input and fills it with the top words, we coded this to be scalable
  for(int i = 0; i<size; i++){
    listToCopyOn[i].score = listToCopy[i].score;
    listToCopyOn[i].word = listToCopy[i].word;
    }
}

wordStruct calculateSecondBestWord(const char *topWord, wordStruct *bestWords, wordStruct *answerWords, const int bestWordsSize,const int answerWordsSize) // Calculates second best word and returns a wordStruct with those words
{
    wordStruct *answerWordsCopy = (wordStruct*)malloc(sizeof(wordStruct) * answerWordsSize); // answerWords with letters blanked out
    for (int i = 0; i < answerWordsSize; i++) // Loop through every answerWord and replace matching letters with space
    {
        char tempAns[6];
        char tempTopWord[6];

        strcpy(tempTopWord, topWord);
        strcpy(tempAns, answerWords[i].word);

        for (int i = 0; i < 5; i++) // Check matching letter in the right place
        {
            if (tempTopWord[i] == tempAns[i])
            {
                tempTopWord[i] = ' '; // For ease of use
                tempAns[i] = ' ';
            }
        }

        for (int i = 0; i < 5; i++) // Check i letter in answerword against every letter in guessword
        {
            if (tempTopWord[i] != ' ')
            {                               // If this letter was found to be an exact match we don't score it again
                for (int j = 0; j < 5; j++) // Go through letters in inputWord and check against i letter in answerWord
                {
                    if (tempAns[j] != ' ' && tempTopWord[i] == tempAns[j])
                    { // Check if we are checking against a letter that hasn't been found yet
                        tempAns[j] = ' '; // Once a letter in answerword is found it won't count again
                        j = 5;            // Once we find that the letter exists we stop adding points for if it exists again
                    }
                }
            }
        }
        answerWordsCopy[i].word = (char *)malloc(sizeof(char *));

        strcpy(answerWordsCopy[i].word, tempAns);
        answerWordsCopy[i].score = 0;
    }
    
    calculateScores(bestWords, answerWordsCopy, bestWordsSize, answerWordsSize);
    qsort( bestWords, bestWordsSize, sizeof(wordStruct), compareFunction);
    free(answerWordsCopy);

    for(int i = 0; i < bestWordsSize; i++){
        printf("    %s %d", bestWords[i].word, bestWords[i].score);
        
        if(bestWords[i].score>bestWords[i+1].score) break;
    }
    printf("\n");
    return bestWords[0];
}

// -----------------------------------------------------------------------------------------
int main()
{
    char *answersFileName; // Stores the answers file name
    char *guessesFileName; // Stores the guesses file name
    // Sets default file names
    answersFileName = "answersLarge.txt";
    guessesFileName = "wordsLarge.txt";

    printf("Default file names are %s and %s\n", answersFileName, guessesFileName);
    int menuOption = 0;
    do
    {
        printf("\n"); // Display menu
        printf("Menu Options:\n");
        printf("  1. Display best first words only\n");
        printf("  2. Display best first and best second words\n");
        printf("  3. Change answers and guesses filenames\n");
        printf("  4. Exit\n");
        printf("Your choice: ");
        scanf("%d", &menuOption);

        if (menuOption == 4) // Exits the program
        {
            exit(1); 
        }
        else if (menuOption == 3) // Changes file names. 
        {
            printf("Enter new answers and guesses filenames: ");
            char temp[81];
            char burner;
            scanf("%c", &burner);
            fgets(temp, 81, stdin);
            answersFileName = strtok(temp, " ");
            guessesFileName = strtok(NULL, "\n");
        }
    } while (menuOption == 3);

    int answerListSize = getFileSize(answersFileName); // Amount of words in just input answer file
    int guessListSize = getFileSize(guessesFileName);  // DOESN'T INCLUDE ANSWERS IN ANSWER LIST SIZE
    printf("%s has %d words\n", answersFileName, answerListSize);
    printf("%s has %d words\n\n", guessesFileName, guessListSize);
    // Create our word lists
    wordStruct *bestWords = (wordStruct *)malloc(sizeof(wordStruct) * (answerListSize + guessListSize));
    wordStruct *answerList = (wordStruct *)malloc(sizeof(wordStruct) * answerListSize);

    copyFileContents(answerList, answersFileName, 0);            //Copy answerfile into answerList

    copyFileContents(bestWords, answersFileName, 0);              // Copy answerfile into BestWords
    copyFileContents(bestWords, guessesFileName, answerListSize); // Copy and append guessesfile into Bestwords

    calculateScores(bestWords, answerList, (guessListSize+answerListSize), answerListSize); // Calculates and Assigns scores
    organizeScores(bestWords, guessListSize+answerListSize); // Sorts by highest score
  
    int sizeOfTopWords = getNumOfTop(bestWords, guessListSize + answerListSize);
    wordStruct *topWords = (wordStruct *)malloc(sizeof(wordStruct)*sizeOfTopWords);
    fillTopWords(bestWords, topWords, sizeOfTopWords); // Creates a new wordStruct which stores all of the top scoring words

    if(menuOption == 1){ //Shows first top scoring words
        printf("Words and scores for top first words: \n");
        printTopScores(bestWords, (guessListSize + answerListSize));
    }
    if(menuOption == 2){ //Shows first and second top scoring words
      printf("Words and scores for top first words and second words:\n");
      for(int i = 0; i<sizeOfTopWords; i++){
        printf("%s %d\n", topWords[i].word, topWords[i].score);
        wordStruct tempSecondWord = calculateSecondBestWord(topWords[i].word, bestWords, answerList, (answerListSize + guessListSize), answerListSize);
      }
    }
    printf("Done\n");
    return 0;
} // end main()