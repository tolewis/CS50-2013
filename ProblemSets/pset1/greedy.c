#include <stdio.h>
#include <cs50.h>
#include <math.h> 

int main(void)
    {
	float x; //defince x as float
	do
	    {
	    printf("Ahoy, what do I owe you matey?\n");
	    x = GetFloat();
	    } while( x < 0);
	x = x * 100.0; //conversion from dollars to cents
	int y = (int) round(x); //round, cast from float to double to int
	int i = 0;
    while (y >= 25) //while loops starting at 25 cents to remove the largest change first
        {
        y = y - 25;
        i++;
        }
    while (y >= 10)
        {
        y = y - 10;
        i++;
        }
    while (y >= 5)
        {
        y = y - 5;
        i++;
        }
    while (y >= 1 && y != 0)
        {
        y = y - 1;
        i++;
        }
    printf("%i\n",i); //printing the total number of coins used
}
