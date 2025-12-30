#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

#define EXIT_CODE 1

typedef struct {
    int n;
    char *letters;
} letter_args;

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

int letterPerm(int target_len, int pos, bool* used, char* letters, char* curr_result) {
    if (pos == target_len) {
        curr_result[target_len] = '\0';
        FILE *words = fopenCheck(wordFiles(target_len), "r"); 
        char word[target_len+1];
        fgets(word, target_len+1, words);
        while (! feof(words)) {
            // If past curr_result in dictionary alphabetically, stop
            if (word[0] > curr_result[0]) break;
            // If first letter doesn't match skip
            if (word[0] != curr_result[0]) {
                fgets(word, target_len+1, words);
                continue;
            }
            if (strcmp(word, curr_result) == 0) {
                printf("%s\n", curr_result);
                return 0;
            }
            fgets(word, target_len+1, words);
        }

        return -1;
    }

    for (int i = 0; i < 9; i++) {
        if (used[i] == true) continue;

        used[i] = true;
        curr_result[pos] = letters[i];
        if (letterPerm(target_len, pos + 1, used, letters, curr_result) == 0) return 0;
        used[i] = false;
    }

    return -1;
}

void *pthreadPerm(void* args) {
    letter_args *input = (letter_args*)args; 
    char *letters = input->letters;
    
    char curr_result[10];
    bool used[10];

    for (int i = 0; i < 9; i++) {
        used[i] = false;
    }

    letterPerm(input->n, 0, used, letters, curr_result);
    return NULL;
}

letter_args *createLetterArgs(int n, char * letters) {
    letter_args* args = malloc(sizeof(letter_args));
    args->n = n;
    args->letters = letters;
    return args;
}

void lettersGame(char *letters) {
    pthread_t perm1, perm2, perm3, perm4, perm5, perm6, perm7, perm8, perm9;

    letter_args* args = createLetterArgs(9, letters);
    pthread_create(&perm9, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(8, letters);
    pthread_create(&perm8, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(7, letters);
    pthread_create(&perm7, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(6, letters);
    pthread_create(&perm6, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(5, letters);
    pthread_create(&perm5, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(4, letters);
    pthread_create(&perm4, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(3, letters);
    pthread_create(&perm3, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(2, letters);
    pthread_create(&perm2, NULL, pthreadPerm, (void*)args);
    args = createLetterArgs(1, letters);
    pthread_create(&perm1, NULL, pthreadPerm, (void*)args);

    pthread_join(perm9, NULL);
    pthread_join(perm8, NULL);
    pthread_join(perm7, NULL);
    pthread_join(perm6, NULL);
    pthread_join(perm5, NULL);
    pthread_join(perm4, NULL);
    pthread_join(perm3, NULL);
    pthread_join(perm2, NULL);
    pthread_join(perm1, NULL);
}

int checkOps(int *nums, char *ops, int target, int closest) {
    // TEMPORARY
    return 1;
}

int opPerm(int target_len, int pos, int *nums, char *curr_result, char *ops, int target, int closest) {
    if (pos == target_len) {
        checkOps(nums, curr_result, target, closest);
    }

    for (int i = 0; i < target_len; i++) {
        curr_result[pos] = ops[i % 4];
        opPerm(target_len, pos+1, nums, curr_result, ops, target, closest);
    }

    // TEMPORARY
    return 1;
}

int numPerm(int target_len, int pos, bool* used, int *nums, int *curr_result, int target, int closest) {
    if (pos == target_len) {
        char ops[] = {'+', '-', '*', '\\'};
        char opResult[5];
        opPerm(target_len-1, 0, curr_result, opResult, ops, target, closest);
        //TEMPORARY
        return 1;
    }
    
    for (int i = 0; i < 6; i++) {
        if (used[i] == true) continue;

        used[i] = true;
        curr_result[pos] = nums[i];
        if (numPerm(target_len, pos + 1, used, nums, curr_result, target, closest) == 0) return 0;
        used[i] = false;
    }

    // TEMPORARY
    return 1;
}

void numbersGame(int *nums, int target) {

}

void getLetters(char **args, char* letters) {
    for (int i = 0; i < 9; i++) {
        letters[i] = args[i+2][0];
    }
}

int main(int n, char **args) {
    if (n != 11) {
        error();
    }
    else if (args[1][1] == 'l') {
        char letters[10];
        getLetters(args, letters);
        lettersGame(letters);
    }    
    else if (args[1][1] == 'n') {

    }
    else error();
    return 0;
}