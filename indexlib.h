#ifndef INDEXLIB_H
#define INDEXLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define BUFSIZE 8192            // lines shorter than 8kB
#define MAXLINES 1000           // word appears at most 1000 times
#define MAXWORDS 100            // index for at most 100 words

/* functions for creating an index; the created index is an array of word_t structures */

// structure holding a single index entry
typedef struct word {
    char *Word;         // the stored word
    int HowManyLines;   // the number of lines the word appeared in
    int *LinesWithWord; // an array containing the indices of lines that contain said word
} word_t;

/* function that returns WordToSearch if it finds an exact match of it in String, and NULL
otherwise (for example, it will find "John" in "Mr John Smith" but not in "MrJohnSmith") */
char *intelligent_strstr (char *String, char *WordToSearch);

/* comparison funtion for qsort to sort an index by how many lines each word appeared in */
int compare_word_count (const void* a, const void* b);

/* comparison funtion for qsort to sort an index by how how long each word is */
int compare_word_length (const void* a, const void* b);

/* function that sorts an index with qsort by how many lines each word appeared in, from fewest to most */
void sort_by_word_count (word_t *Index, int n);

/* function that sorts an index with qsort by word length, from shortest to longest */
void sort_by_word_length (word_t *Index, int n);

/* function that searches for a given word in a given file and returns
a word_t structure based on how many lines the word has been found in*/
word_t search_for_word (char *WordToSearch, FILE *File);

/* function that creates an array of word_t structures based on an array of Words to search and a File */
word_t *create_index (char **Words, int n, FILE *File);

/* function that prints an index into the terminal */
void print_index (int n, word_t *Index);

#endif