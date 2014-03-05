#include <stdio.h>
#include <cs50.h>

int main(void)
{
	int y;
	do //do while loop to ask and check pyramid value for validity
	{
		printf("How tall would you like your pyramid?\n");
		y = GetInt();
	} while( y < 0 || y >23 ); //check y against conditions
	
	for(int i = 0; i < y; i++)
	{
		for(int j = y-i-1; j > 0; j--) //printing spaces before #'s
		{
			printf(" ");
		}
		for(int k = 0; k < i; k++) //printing #/s
		{
			printf("#");
		}
		printf("##\n");	 //printing final #'s
	}
}
