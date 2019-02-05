//
// Created by anton on 11/30/18.
//

#include "ConsoleView.h"
#include <iostream>
ConsoleView::ConsoleView(Model *model)  {
    this->data=model;
}

void ConsoleView::PrintWinner() {
    std::cout<<"Congratulations "<<data->getName()<<"!"<<std::endl;
}

void ConsoleView::draw(){
    const char nameColumn[10]={'a','b','c','d','e','f','g','h','i','j'};
    std::cout<<"  ";
    for(int i=0;i<20;i++) {
        std::cout << nameColumn[i % 10];
        if (i ==9)
            std::cout << "    ";
    }
    std::cout<<std::endl;
    for(int i=0;i<10;i++)
        std::cout <<data->getLine(i+1)<<std::endl;
}