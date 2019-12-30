#include <fstream>

const int MAX_LENGTH = 512;

int frequency(const char* target);

int edit_distance(const char* a, const char* b, int max_d = 2);

int d(const char* a, const char* b, const int i, const int j);

bool spell_correct(const char* word, char* fixed);