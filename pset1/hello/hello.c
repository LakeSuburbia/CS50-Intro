#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //Input naam
    string str = get_string("Hoe heet je? ");
    
    //output naam
    printf("hello,%s\n", str);
}