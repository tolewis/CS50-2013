/**
*Timothy Lewis tim@tolewis.com
*caesar.c program using the Caesar's cipher to encrypt some  text
*input: ./caesar integer-cipher
*input: Encrypted text phrase, all special characters will be passed through
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)                                      //only 2 arguments may be passed or program returns 1
    {
        int k = atoi(argv[1]) % 26;
        printf("");
        string s = GetString();
        if (s != NULL)
        {
            for (int i = 0, n = strlen(s); i < n; i++)  //loop to encrypt plain text datas
            {
                int p = (int)s[i] + k;
                if (s[i] >= 'a' && s[i] <= 'z' && p > 'z')
                {
                    printf("%c", (char)((p % 'z') + 'a' - 1));
                }
                else if (s[i] >='A' && s[i] <= 'Z' && p > 'Z')
                {
                    printf("%c", (char)((p % 'Z') + 'A' - 1));
                }
                else if (s[i] >= 'a' && s[i] <= 'z')
                {
                    printf("%c", (char)(s[i] + k));
                }
                else if (s[i] >= 'A' && s[i] <= 'Z')
                {
                    printf("%c", (char)(s[i] + k));
                }
                else
                {
                    printf("%c", (char)s[i]);
                }
            }
            printf("\n");
        }
    }
    else
    {
    printf("Error, incorrect # of arguments\n");        //Error for incorrect number of arguments
    return 1;
    }
    return 0;
}
