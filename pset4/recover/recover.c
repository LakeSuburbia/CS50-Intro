#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>


int main(int argc, char *argv[])
{
    FILE *fileptr = NULL;
    FILE *imgptr = NULL;
    
    int counter = 0;
    
    unsigned char buffer[512];
    char *filename = (char *) malloc(7 * sizeof(char));
    
    
    
    
    if (argc == 2 && fopen(argv[1], "r") != NULL)
    {
        fileptr = fopen(argv[1], "r");
    }
    else
    {
        printf("Geen geldige input\n");
        return 1;
    }
    
    
    while (fread(buffer, sizeof(char), 512, fileptr) != 0)
    {
        unsigned char test = (buffer[3] & 0xf0);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && test == 0xe0)
        {   
            //fclose(imgptr);
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            imgptr = fopen(filename, "a");
            //printf("%2d - Found a jpeg!\n", counter);
            fwrite(buffer, sizeof(char), 512, imgptr);
        }
    
        else 
        {   
            if (counter != 0)
            {
                fwrite(buffer, sizeof(char), 512, imgptr);
            }
        }
    }
    free(filename);
}

