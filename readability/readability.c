#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string txt);
int count_words(string txt);
int count_sentences(string txt);
int main(void)
{
    int letters, words, sentences, rounded_index;
    float index, l, s;
    string txt = get_string("Text: ");
    letters = count_letters(txt); //Counts letters.
    words = count_words(txt);// Counts words.
    sentences = count_sentences(txt); //Counts sentences.
    l = (float)letters / words * 100;
    s = (float)sentences / words * 100;
    index = 0.0588 * l - 0.296 * s - 15.8;//Calculates index using Coleman-Liau formula.
    rounded_index = round(index);
    if (rounded_index >= 16) //If rounded index is 16 ang higher.
    {
        printf("Grade 16+\n");
    }
    else if (rounded_index < 1) //If rounded index is below 1.
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", rounded_index);

    }
}








int count_letters(string txt)
{
    int count = 0;
    for (int x = 0; txt[x] != '\0'; x++)
    {
        if ((txt[x] >= 'A' && txt[x] <= 'Z') || (txt[x] >= 'a' && txt[x] <= 'z'))
        {
            count++;
        }
    }
    return count;

}

int count_words(string txt)
{
    int count = 1; //Starting from 1 because there is no ' ' character after the last word.
    for (int x = 0; txt[x] != '\0'; x++)
    {
        if (txt[x] == ' ')
        {
            count++;
        }
    }
    return count;

}



int count_sentences(string txt)
{
    int count = 0;
    for (int x = 0; txt[x] != '\0'; x++)
    {
        if (txt[x] == '.' || txt[x] == '!' || txt[x] == '?')
        {
            count++;
        }
    }
    return count;
}
