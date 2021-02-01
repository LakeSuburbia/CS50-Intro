#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int height;
    
    //Vraag input
    do
    {
        height = get_int("height: ");
    }
    while (height < 1 || height > 8);
    
    //height-1-i spaties, gevolgd door i "#", gevolgd door 1 spatie, gevolgd door 1 spatie, gevolgd door height-1-i spaties
    
    //i = aantal rijen
    for (int i = 0; i < height; i++)
    {
        
        //Print height-i spaties
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        //print i maal #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        //print 1 spatie 
        printf("  ");
        
        //print i maal #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        
        //end line
        printf("\n");
    }
}