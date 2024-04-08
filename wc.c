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

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        char *flag = argv[1];
        char *filePath = argv[2];
        FILE *fptr;
        char c;

        if (strcmp(flag, "-c") == 0)
        {
            fptr = fopen(filePath, "r");
            if (fptr == NULL)
                return 1;
                
            int bytes = getByteCount(fptr);
            printf("\t%d %s", bytes, filePath);
        }
    }

    return 0;
}