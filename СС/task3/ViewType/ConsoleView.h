//
// Created by anton on 11/30/18.
//

#ifndef TASK3_CONSOLEVIEW_H
#define TASK3_CONSOLEVIEW_H

#include "../Interfaces.h"
#include "../Model.h"

class ConsoleView: public GameView {
    Model * data;
public:
    ConsoleView(Model* model);
    void PrintWinner( )override;
    void draw() override;
};


#endif //TASK3_CONSOLEVIEW_H
