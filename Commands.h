#ifndef CPPMUD_COMMANDS_H
#define CPPMUD_COMMANDS_H
#include "World.h"
#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

class Commands {

public:

    bool doCommand(World *myWorld, Player *player, string input);

    string getCommands();
};

#endif
