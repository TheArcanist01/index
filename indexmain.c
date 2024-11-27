#include "indexlib.h"

int main (int argc, char **argv) {
    
    FILE *File = fopen(argv[1], "r");

    if (File == NULL) {
        fprintf(stderr, "[%s] Error: Can't find file \"%s\"\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    if (argc < 3) {
        fprintf(stderr, "[%s] Specify at least 1 word to search for\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *Words[MAXWORDS];
    for (int i = 2; i < argc; i++) {
        Words[i-2] = argv[i];
    }
    word_t *Index = create_index(Words, argc - 2, File);

    printf("Press 1 to sort by word length; press 2 to sort by line count; press any other key to continue\n");
    int Temp = getch();
    
    switch (Temp) {
        case 49:
            sort_by_word_length(Index, argc-2);
            break;
        case 50: 
            sort_by_word_count(Index, argc-2);
            break;
        default:
            break;
    }

    print_index(argc - 2, Index);

    free(Index);
    fclose(File);

    return EXIT_SUCCESS;
}