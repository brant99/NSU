#include "wordCount.h"

int main() {
    Table countWord;
    countWord.readWord("input.txt");
    countWord.printTab("output.csv");
    return 0;
}