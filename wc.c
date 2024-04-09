/* HEADER FILES */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* HEADER FILES END */

/* DEFINE DIRECTIVES */

#define IN 1  // Inside a word
#define OUT 0 // Outside a word

/* DEFINE DIRECTIVES END*/

/**
 *  Returns the number of bytes present in a file
 *  @param *fptr: A pointer to the file stream
 */
int getByteCount(FILE *fptr)
{
    int count = 0;

    while (fgetc(fptr) != EOF)
        ++count;

    rewind(fptr); // Resets the cursor to the file stream beginning
    return count;
}

/**
 *  Returns the number of new lines (line count)
 *  @param *fptr: A pointer to the file stream
 */
int getLineCount(FILE *fptr)
{
    int count = 0;
    char c;

    while ((c = fgetc(fptr)) != EOF)
    {
        if (c == '\n')
            ++count;
    }

    rewind(fptr); // Resets the cursor to the file stream beginning
    return count;
}

/**
 *   Returns number of words in a file
 *   @param *fptr: A pointer to the file stream
 */
int getWordCount(FILE *fptr)
{
    int STATE = OUT; // Monitors whether the cursor is in a word or not
    int count = 0;
    char c;

    while ((c = fgetc(fptr)) != EOF)
    {
        // If we encounter whitespace, we've exited a word
        if (isspace(c))
            STATE = OUT;

        // If we're not in a word currently, increase word count
        else if (STATE == OUT)
        {
            ++count;
            STATE = IN;
        }
    }

    rewind(fptr); // Resets the cursor to the file stream beginning
    return count;
}

/**
 *   Returns number of UTF-8 characters in a file stream
 *   @param *fptr: A pointer to the file stream
 */
int getCharCount(FILE *fptr)
{
    int count = 0;
    int c;

    while ((c = fgetc(fptr)) != EOF)
        // Bit-wise AND to check the most significant bits
        // of c isn't a leading byte sequence '1100..'
        if ((c & 0xC0) != 0x80)
            ++count;

    rewind(fptr);
    return count;
}

void printStats(char *flag, int lines, int words, int chars, int bytes, char *filePath)
{
    switch (flag[1])
    {
    case 'l':
        printf("%d", lines);
        break;

    case 'w':
        printf("%d", words);
        break;

    case 'm':
        printf("%d", chars);
        break;

    case 'c':
        printf("%d", bytes);
        break;

    default:
        printf("\t%d %d %d %s", lines, words, bytes, filePath);
        break;
    }
}

/**
 *  Program entry point
 *  Accepts an option flag and optionally a file name to print useful statistics
 *
 * Flags:
 *  - `-c`: Prints the number of bytes present in the file
 *  - `-l`: Prints the number of lines in the file
 *  - `-w`: Prints the number of words present in the file
 */
int main(int argc, char **argv)
{
    int ch;
    int lines = 0, words = 0, chars = 0, bytes = 0;
    int state = 0;

    if (argc == 2)
    {
        char *arg = argv[1];
        if (arg[0] == '-')
        {
            while ((ch = getchar()) != EOF)
            {
                ++bytes;

                if (ch == '\n')
                    ++lines;

                if ((ch & 0xC0) != 0x80)
                    ++chars;

                if (isspace(ch))
                    state = 0;

                else if (state == 0)
                {
                    ++words;
                    state = 1;
                }
            }

            printStats(arg, lines, words, chars, bytes, "");
        }
        else
        {
            char *filePath = argv[1];
            FILE *fptr;

            fptr = fopen(filePath, "r");
            if (fptr == NULL)
            {
                perror("Failed to read file");
                exit(EXIT_FAILURE);
            }

            lines = getLineCount(fptr);
            words = getWordCount(fptr);
            chars = getCharCount(fptr);
            bytes = getByteCount(fptr);

            printStats("", lines, words, chars, bytes, filePath);
        }
    }
    else if (argc == 3)
    {
        char *flag = argv[2];
        char *filePath = argv[1];
        FILE *fptr;

        fptr = fopen(filePath, "r");
        if (fptr == NULL)
        {
            perror("Failed to read file");
            exit(EXIT_FAILURE);
        }

        lines = getLineCount(fptr);
        words = getWordCount(fptr);
        chars = getCharCount(fptr);
        bytes = getByteCount(fptr);

        printStats(flag, lines, words, chars, bytes, filePath);
    }

    return 0;
}