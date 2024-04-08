#include <stdio.h>
#include <string.h>

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

        if (strcmp(flag, "-c") == 0)
        {
            int bytes = getByteCount(fptr);
            printf("\t%d %s", bytes, filePath);
        }

        if (strcmp(flag, "-l") == 0)
        {
            int lines = getLineCount(fptr);
            printf("\t%d %s", lines, filePath);
        }
    }

    return 0;
}