// Raulph Peltrop
// Dr. Steinberg
// COP3223C Section 1
// Large Program 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STRIKES 6
#define MAX 20

// Function Prototypes
void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no

int main()
{
    // Introduction
    printf("Welcome to the Hangman Game!\n");
    rules();

    // Opening and reading the file
    FILE* fptr;
    fptr = fopen("words.txt", "r");
    // Failsafe
    if (fptr == NULL)
    {
        printf("File was not successfully opened.");
        return -1;
    }
    else
    {
        // Arrays needed
        char answer[MAX];
        char words[MAX];
        // Looping through the file for the contents
        while (fscanf(fptr, "%s", words) != EOF)
        {
            // Copying original string from file to the answer array
            strncpy(answer, words, sizeof(answer));
            int wordsLength = strlen(words);
            maskWord(words, wordsLength);
            // Begins round
            int play = playRound(words, answer);
            // Winner or loser
            if (play == 10)
            {
                printf("Congratulations! You won! The word was %s.\n", answer);
                printf("************************************************************************\n");
                
            }
            else
            {
                printf("Sorry you did not win the round. The word was %s.\n", answer);
                printf("************************************************************************\n");
            }
            // Prompts user if they would like to continue playing
            playAgain(&play);
            if (play == 1)
            {
                continue;
            }
            else
            {  
                printf("************************************************************************\n"
                        "Thank you for playing today!\n");
                break;
            }
        }
        // EOF condition met
        if (fscanf(fptr, "%s", words) == EOF)
        {
            printf("Sorry. It seems you have reached the end of the game. :(\n"
            "Please place more words in the text file to continue playing Hangman! :)");
        }
        // Closes file
        fclose(fptr);
    }
    
    return 0;
}

void rules(void)
{
    // Rules
    printf("************************************************************************\n");
    printf("Here are the rules.\n"
        "I will provide you a set of * characters for each round.\n"
        "Each * represents a letter in the English Alphabet.\n"
        "You must figure out each letter of the missing word.\n"
        "For every correct letter guessed, I will reveal its place in the word.\n"
        "Each mistake will result in a strike.\n"
        "6 strikes will result in a loss that round.\n"
        "Are you ready? Here we go!\n");
    printf("************************************************************************\n");
}
void maskWord(char starword[], int size)
{
    // Looping through string and replacing with * value
    for(int i = 0; i < size; i++)
    {
        starword[i] = '*';
    }
}
int playRound(char starword[], char answer[])
{

    int count = 0, index = 0, length = strlen(starword);
    char guess = ' ';
    char guessesTotal[MAX] = {' '};
    // Introduction
    printf("Welcome to the Round!\n");
    printf("The size of the word has %d letters.\n", length);
    while(count != STRIKES)
    {
        // What has been guessed, the amount of strikes, and collecting user input for guess
        printf("Letter(s) you have guessed: %s\n", guessesTotal);
        printf("You currently have %d strike(s).\n", count);
        printf("Enter your guess: ");
        scanf(" %c", &guess);
        // Fail safe
        while (!(isalpha(guess)))
        {
            printf("You did not enter a letter from the alphabet.\n");
            printf("You currently have %d strike(s).\n", count);
            printf("Letter(s) you have guessed: %s\n", guessesTotal);
            printf("Enter your guess: ");
            scanf(" %c", &guess);
        }
        // Placing guess in character array
        guess = tolower(guess);
        guessesTotal[index] = guess;
        index++;

        int result = occurancesInWord(guess, answer);
        // If guess exists enter updateStarWord
        if (result > 0)
        {
            updateStarWord(starword, answer, guess);
            // Displays current starword
            printf("%s\n", starword);
        }
        // Increases counter for loop if guess does not exist
        else
        { 
            printf("The letter %c is NOT in the word.\n", guess);
            count++;
            // Displays current starword
            printf("%s\n", starword);
        }
        // Compares starword string to answer and breaks out of loop if they match
        if (strcmp(starword, answer) == 0)
        {
            return 10;
        }
    }
    // Loss of round
    return 9;
}
int occurancesInWord(char userguess, char answer[])
{
    int occurences = 0;
    // Loops through answer string
    for(int i = 0; answer[i] != '\0'; i++)
    {
        // If user input exists, increase variable
        if(answer[i] == userguess)
        {
            occurences++;
        }
    }
    // Return's the existence of character or not
    if (occurences > 0)
    {
        return occurences;
    }
    else
    {
        return 0;
    }
}
void updateStarWord(char starword[], char answer[], char userguess)
{
    // Loops through answer string
    for (int i = 0; answer[i] != '\0'; i++)
    {
        // Replaces user input in starword index of answer's index
        if (userguess == answer[i])
        {
            starword[i] = userguess;
        }
    }
    
}
void playAgain(int *play)
{
    // Checks if user wants to play again
    printf("Would you like to play another round?\n"
            "1: Yes\n"
            "2: No\n"
            "Choice: ");
    scanf("%d", play);
    // Fail safe
    while((*play != 1 && *play != 2))
    {
        printf("Invalid input.\n");
        printf("Would you like to play another round?\n"
            "1: Yes\n"
            "2: No\n"
            "Choice: ");
        scanf("%d", play);
    }
}
