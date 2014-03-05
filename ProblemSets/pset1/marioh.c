#include <stdio.h>
#include <cs50.h>

int main(void)
    {
	int y;
	do
	    {
		printf("How tall would you like your pyramid?\n");
		y = GetInt();
	    } while( y < 0 || y >23 ); //check y against conditions

	for(int i = 0; i < y; i++)
	    {

		for(int j = y-i-1; j > 0; j--)
		    {
			printf(" ");
		    }

		for(int k = 0; k < i; k++)
		    {
			printf("#");
		    }

		printf("#  #");

		for(int l = 0; l<i; l++)
		    {
		    printf("#");
		    }
	    printf("\n");
	    }
    }
