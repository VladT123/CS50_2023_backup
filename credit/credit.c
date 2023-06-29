#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{

    long id, digit, x = 0, y = 0, z = 0, summ, lastdigit, seconddigit;
    int length, i;
    const long ID = get_long("Enter your  credit card number\n");
    id = ID;
    printf("ID %ld\n", id);
    for (id = ID, length = 0; id != 0;) //Count every second digit starting from the end of the card number.
    {
        id = id / 10;
        digit = id % 10;
        id = id / 10;
        digit = digit * 2; //Multiply every second digit by two.
        for (z = 0; digit != 0;) //Second loop used to count digits in numbers after multiplication by two.
        {
            z = digit % 10;
            x = x + z;  //x stores sum of every digit after multiplication.
            digit = digit / 10;
        }
    }
    for (id = ID; id != 0;) //Count every first digit starting at the end of the card number.
    {
        digit = id % 10;
        id = id / 10;
        id = id / 10;
        y = y + digit; //y stores sum of every first digit.
    }
    for (id = ID, length = 0; id != 0;) //Count every digit again and stores the last digit starting from the end of the card number.
    {
        digit = id % 10;
        id = id / 10;
        length++;                              //Use length variable to store total length of the card number.
        lastdigit = digit;
    }
    for (id = ID, i = 0; i < length - 1; i++) //Use length variable to find second-to-last digit starting at the end of the card number.
    {
        digit = id % 10;
        id = id / 10;
        seconddigit = digit;
    }
    summ = x + y;
    summ = summ % 10;
    if (lastdigit == 4 && length > 12 && length < 17 && summ == 0)
    {
        printf("VISA\n");

    }
    else if (lastdigit == 5 && length == 16 && summ == 0 && (seconddigit == 1 || seconddigit == 2 || seconddigit == 3
             || seconddigit == 4 || seconddigit == 5))
    {
        printf("MASTERCARD\n");

    }
    else if (lastdigit == 3 && length == 15 && summ == 0 && (seconddigit == 4 || seconddigit == 7))
    {
        printf("AMEX\n");

    }
    else
    {
        printf("INVALID\n");

    }

}