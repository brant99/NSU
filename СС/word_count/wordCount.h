#include <map>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class Table{
    string word;
    int amount=0;
    map <string,int> saveWord;
public:
    void readWord(string );
    void printTab(string );
};
