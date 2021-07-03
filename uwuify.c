#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 2021
 * I dont know anymore
 */

char matchCase(char chr, char match);

int isVowel(char chr);
int isAlpha(char chr);

char isUpper(char chr);
char isLower(char chr);

char toUpper(char chr);
char toLower(char chr);

int main(int argc, char **argv)
{
    int word;
    int chr_i = 0;
    char chr;
    char next_chr;
    char prev_chr;

    // Seed rand from urandom
    FILE *random_device = fopen("/dev/urandom", "r");

    // Use time if it cant be opened
    if (random_device == NULL)
    {
        srand((unsigned)time(NULL));
    }
    else
    {
        long unsigned int seed;

        size_t result = fread(&seed, sizeof(seed), 1, random_device);

        if (result < 0)
        {
            srand((unsigned)time(NULL));
        }
        else
        {
            srand(seed);
        }

        fclose(random_device);
    }

    // Avoid all the loopy things by exiting early
    // if there arent any args
    if (argc == 1)
        return(0);

    // Loop through all arguments, and each char of the arguments
    for (word = 1; word < argc; word++)
    {
        // Loop until the end of the string.
        chr_i = 0;
        while ((chr = argv[word][chr_i]) != '\0')
        {
            next_chr = argv[word][chr_i + 1];

            // Only set prev_char if there is one
            prev_chr = (chr_i > 0) ? argv[word][chr_i - 1] : '\0';
            /* putchar(chr); */

            switch (toLower(chr))
            {
                case 'i':
                    // Change "ie" to "ei"
                    if (toLower(next_chr) == 'e')
                    {
                        putchar(next_chr);
                        putchar(chr);
                        chr_i++;
                    }
                    // Change "i?e" to "ie?"
                    // Only if the char between them is a letter
                    else if (isAlpha(toLower(next_chr)) &&
                             toLower(argv[word][chr_i + 2] == 'e'))
                    {
                        // put the i
                        putchar(chr);

                        // put the e
                        putchar(argv[word][chr_i + 2]);

                        // put the extra char
                        putchar(next_chr);

                        // Skip both
                        chr_i += 2;
                    }
                    else
                    {
                        putchar(chr);
                    }
                    break;

                case 'e':
                    // Change "ei" to "ie"
                    if (toLower(next_chr) == 'i')
                    {
                        putchar(next_chr);
                        putchar(chr);
                        chr_i++;
                    }
                    else
                    {
                        putchar(chr);
                    }
                    break;

                case 'r':
                    // Only replace r with w if at the start of a word
                    // UPDATE: Replace only if next isnt a d or if it
                    // the prev char isnt e and its at the end
                    /*if (!(chr_i == 0
                        || (chr_i > 0) ? (argv[word][chr_i - 1] == ' ') : 0)) */
                    if (toLower(next_chr) == 'd' ||
                        (toLower(prev_chr) == 'e' &&
                         (next_chr == '\0' || next_chr == ' ')
                        ) ||
                        toLower(next_chr) == 'u'
                       )
                    {
                        putchar(chr);
                        break;
                    }
                case 'l':
                    if (chr_i != 0 && next_chr != 'i')
                        putchar(matchCase('w', chr));
                    else
                        putchar(chr);
                    break;

                case 't':
                    // Replace "th" with 'd' unless at the end,
                    // then with "ff"
                    if (toLower(next_chr) == 'h')
                    {
                        if (argv[word][chr_i + 2] == '\0'
                            || argv[word][chr_i + 2] == ' ')
                        {
                            putchar(matchCase('f', chr));

                            putchar(matchCase('f', next_chr));
                        }
                        else
                        {
                            putchar(matchCase('d', chr));
                        }

                        chr_i++;
                    }
                    else
                    {
                        putchar(chr);
                    }
                    break;

                case 'o':
                    // 'o' to "ow" if in the middle of a word and next
                    // isnt w or vowel or f
                    putchar(chr);
                    if (chr_i != 0 &&
                        !(next_chr == ' ' ||
                          next_chr == '\0') &&
                        !isVowel(next_chr) &&
                        toLower(next_chr) != 'w' &&
                        toLower(next_chr) != 'f' &&
                        toLower(next_chr) != 'r')
                    {
                        putchar(matchCase('w', chr));
                    }
                    break;

                case 'u':
                    // "ue" to "u"
                    putchar(chr);
                    if (toLower(next_chr) == 'e')
                        chr_i++;
                    break;

                default:
                    putchar(chr);
            }

            chr_i++;
        }

        // This for loop avoid putting a trailing space char
        if (word < argc -1)
            putchar(' ');
    }

    // Add a little something at the end
    // Hehe no watning https://stackoverflow.com/a/18435398
    enum { num_endings = 8 };
    char endings[num_endings][20] = {"owo",
                                     "uwu",
                                     "nya!",
                                     "-w-",
                                     "•w•",
                                     "≧◡≦",
                                     "(˙▿˙)",
                                     ":3"};

    // Yes there are fairer ways of getting random numbers no i dont
    // care
    putchar(' ');
    printf("%s", endings[random() % num_endings]);

    putchar('\n');

    return(0);
}


char matchCase(char chr, char match)
{
    // Make chr have the same case as match
    if (isUpper(match))
        return(toUpper(chr));

    else if (isLower(match))
        return(toLower(chr));

    return(chr);
}


int isVowel(char chr)
{
    char lower = toLower(chr);
    return(lower == 'a'
           || lower == 'e'
           || lower == 'i'
           || lower == 'o'
           || lower == 'u');
}


int isAlpha(char chr)
{
    char lower = toLower(chr);
    return('a' <= lower && lower <= 'z');
}


char isLower(char chr)
{
    return(('a' <= chr && chr <= 'z'));
}


char isUpper(char chr)
{
    return(('A' <= chr && chr <= 'Z'));
}


// I use the isUpper and isLower so symbols arent affected
char toLower(char chr)
{
    // Set the lowercase bit
    if (isUpper(chr))
        return(chr | 0x20);

    return(chr);
}


char toUpper(char chr)
{
    // Reset the lowercase bit
    if (isLower(chr))
        return(chr & 0x5f);

    return(chr);
}

