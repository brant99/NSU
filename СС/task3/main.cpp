#include <iostream>
#include "GamerType/ConsoleGamer.h"
#include "ViewType/ConsoleView.h"
#include "Controller.h"
#include <cxxopts.hpp>
#include <string>
int main(int argc, char* argv[]) {
    Controller game;
    game.play(argc,argv);
    return 0;
}