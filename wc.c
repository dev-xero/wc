/* HEADER FILES */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

    while ((c = fgetc(fptr) != EOF))
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
    if (argc > 2)
    {
        char *flag = argv[1];
        char *filePath = argv[2];
        FILE *fptr;

        fptr = fopen(filePath, "r"); // Pointer to the file stream
        if (fptr == NULL)
        {
            perror("Failed to read file");
            exit(EXIT_FAILURE);
        }

        // -c counts bytes
        if (strcmp(flag, "-c") == 0)
        {
            int bytes = getByteCount(fptr);
            printf("\t%d %s", bytes, filePath);
        }

        // -l counts lines
        if (strcmp(flag, "-l") == 0)
        {
            int lines = getLineCount(fptr);
            printf("\t%d %s", lines, filePath);
        }

        // -w counts words
        if (strcmp(flag, "-w") == 0)
        {
            int words = getWordCount(fptr);
            printf("\t%d %s", words, filePath);
        }

        // -m counts characters
        if (strcmp(flag, "-m") == 0)
        {
            int chars = getCharCount(fptr);
            printf("\t%d %s", chars, filePath);
        }
    }

    return 0;
}