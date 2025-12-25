#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define EXIT_CODE 1

void error() {
    fprintf(stderr, "Input error.\n");
    exit(EXIT_CODE);
}

/*
 * Checks that the file exists and can/has been opened without error
 */
FILE *fopenCheck(char *filename, char *mode) {
    FILE *f = fopen(filename, mode);
    if (f != NULL) return f;
    fprintf(stderr, "Can't open %s.\n", filename);
    exit(EXIT_CODE);
    
    return 0;
}

void permutation(int target_len, int pos, bool* used, char* letters, char* curr_result) {
    if (pos == target_len) {
        curr_result[target_len] = '\0';
        FILE *words = fopenCheck("nine_words.txt", "r"); 
        char word[10];
        fgets(word, 10, words);
        while (! feof(words)) {
            if (strcmp(word, curr_result) == 0) printf("%s\n", curr_result);
            // If past curr_result in dictionary alphabetically, stop
            if (word[0] > curr_result[0]) break;
            fgets(word, 10, words);
        }

        return;
    }

    for (int i = 0; i < 9; i++) {
        if (used[i] == true) continue;

        used[i] = true;
        curr_result[pos] = letters[i];
        permutation(target_len, pos + 1, used, letters, curr_result);
        used[i] = false;
    }
}

void allPermutations(char *letters) {
    char curr_result[10];
    bool used[10];

    for (int i = 0; i < 9; i++) {
        used[i] = false;
    }
    
    permutation(9, 0, used, letters, curr_result);

    // TODO: Return best result
    // for (int i = 9; i >= 1; i--) {
    //     result = permutation(i, 0, used, letters, curr_result);
    // }
}

int main(void) {
    char letters[] = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'h', 'm'};
    allPermutations(letters);
    return 0;
}