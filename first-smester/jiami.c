#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char message[100];
    int key;
    printf("Enter message to be encrypted:");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n')
            message[len - 1] = '\0';   
    }
    printf("Enter shift amount (1-25): ");
    scanf("%d", &key);
    printf("Encrypted message:");
    for (int i = 0; message[i] != '\0'; i++)
    {
        char ch = message[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ((ch - 'a' + key) % 26) + 'a';
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ((ch - 'A' + key) % 26) + 'A';
        }
        printf("%c", ch);
    }
}
