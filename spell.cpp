#include "spell.h"
#include <cstring>
#include <iostream>
using namespace std;

int frequency(const char* target) {
    ifstream in;
    in.open("words.dat");
    int freq;
    char word[MAX_LENGTH];

    in >> freq;
    in >> ws >> word;
    while (!in.fail()) {
        if (strcmp(target, word) == 0)
            return freq;

        in >> freq;
        in >> ws >> word;
    }
    
    in.close();
    return 0;
}

int edit_distance(const char* a, const char* b, int max_d) {
    int a_len = strlen(a);
    int b_len = strlen(b);

    if (max_d < 0 || min(a_len, b_len) == 0)
        return max(a_len, b_len);

    int indicator = a[0] == b[0] ? 0 : 1;

    int del = edit_distance(a+1, b, max_d - 1) + 1;
    int ins = edit_distance(a, b+1, max_d - 1) + 1;
    int rep = edit_distance(a+1, b+1, max_d) + indicator;

    if (a_len > 1 && b_len > 1 && a[0] == b[1] && a[1] == b[0]) {
        int trans = edit_distance(a+2, b+2, max_d - 1) + 1;
        return min( min(del, ins), min(rep, trans));
    }

    return min( min(del, ins), rep );
}

bool spell_correct(const char* word, char* fixed) {
    strcpy(fixed, word);
    ifstream in;
    in.open("words.dat");

    int freq;
    int best_freq = 0;
    int d;
    int min_d = 2;
    char list_word[MAX_LENGTH];

    in >> freq;
    in >> ws >> list_word;

    while (!in.fail()) {
        d = edit_distance(word, list_word);
        if (d < min_d || (d == min_d && freq > best_freq)) {
            strcpy(fixed, list_word);
            min_d = d;
            best_freq = freq;
        }

        in >> freq;
        in >> ws >> list_word;
    }
    in.close();

    if (strcmp(fixed, word) == 0)
        return false;

    return true;
}