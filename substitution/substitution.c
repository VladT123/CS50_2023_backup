#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

string hacker(string txt, string key);
int Error(string key);
int main(int argc, string argv[])
{
    string plain, cipher;
    string key = argv[1];
    if (argc != 2) //Check for arguments.
    {
        printf("ERROR\n");
        return 1;
    }
    else if (Error(key) == 1) //Error function used to check for invalid key.
    {
        printf("ERROR\n");
        return 1;
    }
    plain = get_string("plaintext: ");
    cipher = hacker(plain, key);
    printf("ciphertext:%s\n", cipher);
}

string hacker(string txt, string key)
{
    for (int i = 0; txt[i] != 0; i++)
    {
        if (txt[i] >= 'A' && txt[i] <= 'Z') //If input in uppercase.
        {
            txt[i] = key[tolower(txt[i]) - 97];
            txt[i] = toupper(txt[i]);
        }
        else if (txt[i] >= 'a' && txt[i] <= 'z') //If input in lowercase.
        {
            txt[i] = tolower(key[txt[i] - 97]);
        }
    }
    return txt;
}

int Error(string key)
{
    int length = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        if ((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z')) //Check for invalid characters.
        {
            length++; //Used to count key length.
        }
        else
        {
            return 1;
        }
    }
    if (length != 26) //Check length.
    {
        return 1;
    }

    for (int i = 0; key[i] != '\0'; i++) //Check for duplicate characters.
    {
        for (int j = 0; key[j] != '\0'; j++)
        {
            if (key[i] == key[i + 1])
            {
                printf("Key %c", key[i]);
                return 1;
            }
        }
    }
    return 0;
}