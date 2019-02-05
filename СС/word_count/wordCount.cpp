#include "wordCount.h"
void Table::readWord(string name){
    ifstream fi(name);
    int begin=0;
    bool var=0;
    if(!fi){
        cerr<<"Error!input file is not existing";
    }
    while(getline(fi,word)){
        for(int i=0;i<word.size();i++) {
            if(var && !isalnum(word[i])) {
                saveWord[word.substr(begin,i-begin)]++;
                amount++;
                var=false;
            }
            else if(!var && isalnum(word[i])) {
                begin = i;
                var = true;
            }
        }
        if(var){
            saveWord[word.substr(begin,word.size()-begin)]++;
            amount++;
            var=false;
        }
    }
}
void Table::printTab(string name){
    ofstream fo(name);
    multimap<int,string> tab;
    for(auto item=saveWord.begin();item!=saveWord.end();++item){
        tab.insert(make_pair(item->second,item->first));
    }
    for(auto item=tab.rbegin();item!=tab.rend();++item){
        fo<<item->second<<","<<(double)item->first/amount*100<<"%"<<endl;
    }
}
