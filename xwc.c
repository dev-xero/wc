#include <stdio.h>
#include <string.h>

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
            if (fptr == NULL) return 1;
            
            int count = 0;
            while (fgetc(fptr) != EOF)
            {
                ++count;
            }
            printf("\t%d %s", count, filePath);
        }
    }

    return 0;
}