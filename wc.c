#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0

int getByteCount(FILE *fptr)
{
    int count = 0;
    while (fgetc(fptr) != EOF)
    {
        ++count;
    }
    return count;
}

int getLineCount(FILE *fptr)
{
    int count = 0;
    char c;

    while (c != EOF)
    {
        c = fgetc(fptr);
        if (c == '\n')
        {
            ++count;
        }
    }

    return count;
}

int getWordCount(FILE *fptr)
{
    int count = 0;
    char c;

    int STATE = OUT;

    while ((c = fgetc(fptr)) != EOF)
    {
        if (isspace(c))
            STATE = OUT;

        else if (STATE == OUT)
        {
            ++count;
            STATE = IN;
        }
    }

    rewind(fptr);

    return count;
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        char *flag = argv[1];
        char *filePath = argv[2];
        FILE *fptr;

        // Open file for reading
        fptr = fopen(filePath, "r");
        if (fptr == NULL)
            return 1;

        // -c flag counts bytes
        if (strcmp(flag, "-c") == 0)
        {
            int bytes = getByteCount(fptr);
            printf("\t%d %s", bytes, filePath);
        }

        // -l flag counts lines
        if (strcmp(flag, "-l") == 0)
        {
            int lines = getLineCount(fptr);
            printf("\t%d %s", lines, filePath);
        }

        // -w flag counts words
        if (strcmp(flag, "-w") == 0)
        {
            int words = getWordCount(fptr);
            printf("\t%d %s", words, filePath);
        }
    }

    return 0;
}