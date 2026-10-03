#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 50
#define MAX_LENGTH 20
#define MAX_WRONG 6

void displayHangman(int wrong);
void displayWord(char word[], char guessed[], int guessedCount);
int alreadyGuessed(char guessed[], int count, char letter);
int isLetter(char ch);
char toLowerCase(char ch);

int main()
{
    FILE *fp;

    char words[MAX_WORDS][MAX_LENGTH];
    int wordCount = 0;

    fp = fopen("words.txt", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open words.txt\n");
        return 1;
    }

    while (wordCount < MAX_WORDS &&
           fscanf(fp, "%19s", words[wordCount]) == 1)
    {
        wordCount++;
    }

    fclose(fp);

    if (wordCount == 0)
    {
        printf("No words found in words.txt\n");
        return 1;
    }

    int randomIndex = rand() % wordCount;

    char *secretWord = words[randomIndex];

    int wordLength = strlen(secretWord);

    char guessedLetters[26];
    int guessedCount = 0;

    int wrongGuesses = 0;
    int correctLetters = 0;

    printf("\n");
    printf("===================================\n");
    printf("        HANGMAN GAME\nGuess the word and save from death.\n");
    printf("===================================\n");

    while (wrongGuesses < MAX_WRONG &&
           correctLetters < wordLength)
    {
        printf("\n");

        displayHangman(wrongGuesses);

        printf("\nWord: ");
        displayWord(secretWord, guessedLetters, guessedCount);

        printf("\nWrong guesses: %d/%d\n",
               wrongGuesses, MAX_WRONG);

        printf("Guessed letters: ");

        for (int i = 0; i < guessedCount; i++)
        {
            printf("%c ", guessedLetters[i]);
        }

        printf("\n");

        char guess;

        printf("Enter a letter: ");
        scanf(" %c", &guess);

        guess = toLowerCase(guess);

        if (!isLetter(guess))
        {
            printf("Please enter a letter only.\n");
            continue;
        }

        if (alreadyGuessed(guessedLetters, guessedCount, guess))
        {
            printf("You already guessed '%c'. Try another letter.\n",
                   guess);
            continue;
        }

        guessedLetters[guessedCount] = guess;
        guessedCount++;

        int found = 0;

        for (int i = 0; i < wordLength; i++)
        {
            if (secretWord[i] == guess)
            {
                found = 1;
                correctLetters++;
            }
        }

        if (found)
        {
            printf("Correct! '%c' is in the word.\n", guess);
        }
        else
        {
            printf("Wrong guess!\n");
            wrongGuesses++;
        }
    }

    printf("\n");

    if (correctLetters == wordLength)
    {
        printf("==============================\n");
        printf("          YOU WIN!\n");
        printf("==============================\n");

        printf("The word was: %s\n", secretWord);
    }
    else
    {
        displayHangman(wrongGuesses);

        printf("\n");
        printf("==============================\n");
        printf("        GAME OVER!\n");
        printf("==============================\n");

        printf("The word was: %s\n", secretWord);
    }

    return 0;
}


void displayWord(char word[], char guessed[], int guessedCount)
{
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int found = 0;

        for (int j = 0; j < guessedCount; j++)
        {
            if (guessed[j] == word[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
}


int alreadyGuessed(char guessed[], int count, char letter)
{
    for (int i = 0; i < count; i++)
    {
        if (guessed[i] == letter)
        {
            return 1;
        }
    }

    return 0;
}


int isLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z'))
    {
        return 1;
    }

    return 0;
}


char toLowerCase(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch + ('a' - 'A');
    }

    return ch;
}


void displayHangman(int wrong)
{
    printf(" +---+\n");
    printf(" |   |\n");

    if (wrong >= 1)
        printf(" O   |\n");
    else
        printf("     |\n");

    if (wrong == 2)
        printf(" |   |\n");
    else if (wrong == 3)
        printf("/|   |\n");
    else if (wrong >= 4)
        printf("/|\\  |\n");
    else
        printf("     |\n");

    if (wrong == 5)
        printf("/    |\n");
    else if (wrong >= 6)
        printf("/ \\  |\n");
    else
        printf("     |\n");

    printf("     |\n");
    printf("=========\n");
}

