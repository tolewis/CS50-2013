/**
*Timothy Lewis tim@tolewis.com
*vigenere.c program using the Vigenere's cipher to encrypt some  text
*input: ./vigenere alphabetical-key-cipher (no special characters or numbers)
*input: Encrypted text phrase, all special characters will be passed through unaffected
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)                                  //only 2 arguments may be passed or program returns 1
    {
        string key = argv[1];
        int keyLength = strlen(key);                //define the key character length
        int keyValue[keyLength];                    //define the array to hold the key cipher values
        for (int k = 0, n = keyLength; k < n; k++)  //convert key char values to int values base 26
        {
            int m = (int)key[k];
            if (m >= 'A' && m <= 'Z')
            {
                keyValue[k] = m - 65;
            }
            else if (m >= 'a' && m <= 'z')
            {
                keyValue[k] = m - 97;
            }
            else
            {
                printf("Error, key phrase may only be alphabetical a->z and/or A->Z\n");
                return 1;
            }
        }

    //get plain text value for encryption 
        printf("");
        string s = GetString();

    //pass key values at base 26 through plain test according to scenario
        if (s != NULL)
        {
            for (int i = 0, k = 0, n = strlen(s); i < n; i++, k++)
            {
                k = k % keyLength;                  //revolving key index value
                int p = (int)s[i] + keyValue[k];    //formula to calculate encrypted plain text value 
                if (s[i] >= 'a' && s[i] <= 'z' && p > 'z')  //loop to encrypt plain text data
                {
                    printf("%c", (char)((p % 'z') + 'a' - 1));
                }
                else if (s[i] >='A' && s[i] <= 'Z' && p > 'Z')
                {
                    printf("%c", (char)((p % 'Z') + 'A' - 1));
                }
                else if (s[i] >= 'a' && s[i] <= 'z')
                {
                    printf("%c", p);
                }
                else if (s[i] >= 'A' && s[i] <= 'Z')
                {
                    printf("%c", p);
                }
                else
                {
                    printf("%c", (char)s[i]);
                    k--;
                }
            }
// end of loop
        }
        printf("\n");
    }
    else
    {
        printf("Error, incorrect # of arguments\n");
        return 1;
    }
    return 0;
}
