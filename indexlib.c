#include "indexlib.h"

char *intelligent_strstr (char *String, char *WordToSearch) {
    if (strstr(String, WordToSearch) == NULL) {
        return NULL;
    }

    else {
        char *Token;
        Token = strtok(String, " \n.;,-()!?\":");

        while (Token != NULL) {
            if (strcmp(WordToSearch, Token) == 0) {
                return WordToSearch;
            } else {
                Token = strtok(NULL, " \n.;,-()!?\":");
            }
        }
        
        return NULL;
    }
}

int compare_word_count (const void* a, const void* b)
{
    return ((word_t *)a)->HowManyLines - (( word_t*)b)->HowManyLines;
}

int compare_word_length (const void* a, const void* b)
{
    return strlen(((word_t *)a)->Word) - strlen((( word_t*)b)->Word);
}

void sort_by_word_count (word_t *Index, int n) {
    qsort(Index, n, sizeof(word_t), compare_word_count);
    return;
}

void sort_by_word_length (word_t *Index, int n) {
    qsort(Index, n, sizeof(word_t), compare_word_length);
    return;
}

word_t search_for_word (char *WordToSearch, FILE *File) {
    char Buffer[BUFSIZE];
    int FileLineNumber = 0;

    word_t *Word = NULL;
    Word = (word_t *) malloc(sizeof(word_t));

    Word->Word = WordToSearch;
    Word->HowManyLines = 0;
    Word->LinesWithWord = malloc(MAXLINES*sizeof(int));

    while (fgets(Buffer, BUFSIZE, File)) {
        FileLineNumber++;
        if (intelligent_strstr(Buffer, WordToSearch) != NULL) {
            Word->LinesWithWord[Word->HowManyLines] = FileLineNumber;
            Word->HowManyLines++;
        }
    }
    rewind(File);

    return *Word;
}

word_t *create_index (char **Words, int n, FILE *File) {
    word_t *Index = NULL;
    Index = (word_t *) malloc(MAXWORDS * sizeof(word_t));

    for (int i = 0; i < n; i++) {
        Index[i] = search_for_word(Words[i], File);
    }

    return Index;
}

void print_index (int n, word_t *Index) {
    for (int i = 0; i < n; i++) {
        if (Index[i].HowManyLines != 0) {    
            printf("Word \"%s\" appeared in %d lines: ", Index[i].Word, Index[i].HowManyLines);
            for (int j = 0; j < Index[i].HowManyLines; j++) {
                printf ("%d ", Index[i].LinesWithWord[j]);
            }
            printf("\n");
        }   else {
            printf ("Word \"%s\" not found\n", Index[i].Word);
        }
    }
}




