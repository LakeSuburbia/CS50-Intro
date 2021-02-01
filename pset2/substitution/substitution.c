#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argC, string argV[])
{
    //check of er meer dan 1 input is.
    if (argC == 2)
    {
        int n = strlen(argV[1]);
        string cipher = argV[1];
    
        //put cipher in all caps.
        for (int i = 0; i < n; i++)
        {
            cipher[i] = toupper(cipher[i]);
        }
    
        
    
        //check of het cipher 26 lang is.
        if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
    
        }
    
        //check of het cipher enkel uit letters bestaat.
        for (int i = 0; i < n; i++)
        {
            if (cipher[i] >= 'A' && cipher[i] <= 'Z')
            {
                for (int j = 0; j < i; j++)
                {
                    
                    //check of het cipher geen dubbels bevat;
                    if (cipher[i] == cipher[j])
                    {
                        printf("Key must not contain the same character twice.\n");
                        return 1;
                    }
                }
            }
            else
            {
                printf("Key must only contain letters\n");
                return 1;
    
            }
    
    
        }
    
        string source = get_string("plaintext: ");
        string destination = source;
        string source_upper = source;
        int m = strlen(source);
        int cipher_index[m];
        
        
        for (int i = 0; i < m; i++)
        {
            cipher_index[i] = (int)toupper(source[i]) - (int)'A';
            //printf("%i\n",cipher_index[i]);
        }
    
        for (int i = 0; i < m; i++)
        {
            
            int extra = (int)cipher[cipher_index[i]] - 'A';
            
            if (source[i] >= 'a' && source[i] <= 'z')
            {
                
                destination[i] = cipher[cipher_index[i]] + 32;
                
            }
            else if (source[i] >= 'A' && source[i] <= 'Z')
            {
                
                destination[i] = cipher[cipher_index[i]];
                
            }
            else
            {
                destination[i] = source[i];
            }
            
            //printf("%s\n",source);
        }
    
        printf("ciphertext: %s\n", destination);
    }
    else
    {
        printf("You must add one argument 'Cipher Text'\n");
        return 1;
    }
}
