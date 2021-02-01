#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long creditcard = get_long("kaarnummer: ");
    long mem = creditcard;
    int digit, checksum = 0;
    int length = (int)log10((double)creditcard) + 1;
    int firstdigits = 0;

    
    for (int i = 0; i < length; i++)
    {
        digit = mem % 10;
        mem = mem / 10;
        if (i % 2 == 1)
        {
            digit = 2 * digit;
            if (digit > 9)
            {
                checksum = checksum + digit % 10;
                checksum = checksum + digit / 10;
            }
            else
            {
                checksum = checksum + digit;                
            }
            digit = digit / 2;
        }
        else
        {
            checksum = checksum + digit;
        }
        
        
        if (i == length - 2)
        {
            firstdigits = firstdigits + digit;
        }
        else if (i == length - 1)
        {
            firstdigits = firstdigits + digit * 10;
        }
        
    }
    
    
    
    
    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (length == 15 && (firstdigits == 34 || firstdigits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 13 && digit == 4)
    {
        printf("VISA\n");
    }
    else if (length == 16)
    {
        if (firstdigits == 51 || firstdigits == 52 || firstdigits == 53 || firstdigits == 54 || firstdigits == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
    
    
    
}