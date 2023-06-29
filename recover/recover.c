#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCK_SIZE 512
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");//Creating an input file.
    if (raw_file == NULL)
    {
        printf("WRONG FILE\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    char pict_name[8];//Char used to store names for recovered pictures.
    int picts = 0;// This int is used as a counter to show how many picture were retrived.
    FILE *image = NULL; //Creating an output file and setting it to NULL.
    while (fread(buffer, 1, BLOCK_SIZE, raw_file))
    {
        if (buffer[0] == 0xFF && buffer [1] == 0xd8 && buffer [2] == 0xff && (buffer [3] & 0xf0) == 0xe0)//
        {
            sprintf(pict_name, "%03i.jpg", picts);
            image = fopen(pict_name, "w");
            picts++;
        }
        if (image != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, image);
        }
    }
    fclose(image);
    fclose(raw_file);
}