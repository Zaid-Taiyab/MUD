#ifndef CPPMUD_GAME_H
#define CPPMUD_GAME_H
#include "World.h"
#include "Player.h"

class Game{
private:
    World *myWorld;
    Player *player;

public:
    Game(World *mw);
    void start();


};

#endif //CPPMUD_GAME_H
