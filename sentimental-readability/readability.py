import cs50


def count_letters(txt):
    count = 0
    x = 0
    for i in txt:
        if (txt[x] >= 'A' and txt[x] <= 'Z') or (txt[x] >= 'a' and txt[x] <= 'z'):
            count = count+1
        x = x+1
    return count


def count_words(txt):
    count = 1
    x = 0
    for i in txt:
        if txt[x] == ' ':
            count = count+1
        x = x+1
    return count


def count_sentences(txt):
    count = 0
    x = 0
    for i in txt:
        if txt[x] in ['.', '!', '?']:
            count = count+1
        x = x+1
    return count


def main():
    print("Text: ", end='')
    text = input()
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    #print(f"letters {letters}")
    #print(f"words {words}")
    #print(f"sentence {sentences}")
    l = letters / words * 100
    s = sentences / words * 100
    index = 0.0588 * l - 0.296 * s - 15.8
    #print(f"index {index}")
    rounded_index = round(index)

    if rounded_index >= 16:  # If rounded index is 16 ang higher.
        print("Grade 16+\n")
    elif rounded_index < 1:  # If rounded index is below 1.
        print("Before Grade 1\n")
    else:
        print(f"Grade {rounded_index}")


if __name__ == "__main__":
    main()