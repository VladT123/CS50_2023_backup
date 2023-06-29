#include <cs50.h>
#include <stdio.h>

void build(int x);


int main(void)
{
    int x, y, input; //x=Outer counter/ y=inner counter

    do
    {
        input = get_int("How tall do you want this pyramid to be. Max 38\n");
        if (input < 0)
        {
            printf("no negative values\n");
        }
        if (input == 0)
        {
            printf("no Zero values\n");
        }
        if (input > 8)
        {
            printf("Maximum size is 8\n");
        }
    }
    while (input < 1 || input > 8);

    for (x = 1; x <= input; x++)
    {

        for (y = input - 1; y >= x; y--)//offsets 1st half of the pyramid
        {
            printf(" ");
        }
        build(x);         //Builds 1st half of the pyramid
        printf("  ");       //empty space between pyramid
        build(x);         //Builds 2nd half of the pyramid
        printf("\n");       //New line
    }
}
void build(int x)
{
    int i;
    for (i = 0; i < x; i++)
    {
        printf("#");
    }
}