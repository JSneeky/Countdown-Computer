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

char *wordFiles(int target_len) {
    if (target_len == 9) return "nine_words.txt";
    else if (target_len == 8) return "eight_words.txt";
    else if (target_len == 7) return "seven_words.txt";
    else if (target_len == 6) return "six_words.txt";
    else if (target_len == 5) return "five_words.txt";
    else if (target_len == 4) return "four_words.txt";
    else if (target_len == 3) return "three_words.txt";
    else if (target_len == 2) return "two_words.txt";
    else return "one_words.txt";
}

int permutation(int target_len, int pos, bool* used, char* letters, char* curr_result) {
    if (pos == target_len) {
        curr_result[target_len] = '\0';
        FILE *words = fopenCheck(wordFiles(target_len), "r"); 
        char word[10];
        fgets(word, 10, words);
        while (! feof(words)) {
            if (strcmp(word, curr_result) == 0) {
                printf("%s\n", curr_result);
                return 0;
            }
            // If past curr_result in dictionary alphabetically, stop
            if (word[0] > curr_result[0]) break;
            fgets(word, 10, words);
        }

        return -1;
    }

    for (int i = 0; i < 9; i++) {
        if (used[i] == true) continue;

        used[i] = true;
        curr_result[pos] = letters[i];
        if (permutation(target_len, pos + 1, used, letters, curr_result) == 0) return 0;
        used[i] = false;
    }

    return -1;
}

void allPermutations(char *letters) {
    char curr_result[10];
    bool used[10];

    for (int i = 0; i < 9; i++) {
        used[i] = false;
    }
    
    for (int i = 9; i > 0; i--) {
        if (permutation(i, 0, used, letters, curr_result) == 0) return;
    }

    return;
}

int main(void) {
    char letters[] = {'r', 'g', 'l', 'o', 'a', 'i', 'm', 'h', 't'};
    allPermutations(letters);
    return 0;
}