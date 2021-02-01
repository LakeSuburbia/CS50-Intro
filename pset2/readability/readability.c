#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string input = get_string("Text: ");
    float totaalAantalLetters = 0, totaalAantalWoorden = 1, totaalAantalZinnen = 0;
    int n = strlen(input);


    //gather gegevens
    for (int i = 0; i < n; i++)
    {
        //Tel het aantal letters
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            totaalAantalLetters++;
        }

        //Tel het aantal woorden
        if (input[i] == ' ')
        {
            totaalAantalWoorden++;
        }

        //Tel het aantal zinnen
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            totaalAantalZinnen++;
        }
    }

    //Bereken de readability index;
    float multiplier = totaalAantalWoorden / 100;
    float L = totaalAantalLetters / multiplier;
    float S = totaalAantalZinnen / multiplier;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", index);
    }
}