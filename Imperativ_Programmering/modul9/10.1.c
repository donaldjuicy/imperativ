#include <stdio.h>

void strrev(char *str)
{
    char *start = str;
    char *end = str;
    char temp;

    /* Find slutningen af strengen */
    while (*end != '\0')
        end++;
    end--;  // Peg på sidste tegn (ikke '\0')

    /* Byt tegnene */
    while (start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}
