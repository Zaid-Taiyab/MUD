#include "Game.h"
#include <iostream>
#include <string>
#include "Commands.h"
#include "utils.h"

using namespace std;

/**
 * Basic constructor that initializes the World object
 * @param mw
 */
Game::Game(World *mw): myWorld(mw) {
    player = new Player();
    player->setLocation(myWorld->getStartingLocation());
}

/**
 * Starts the game loop, runs in a continuous loop until doCommand returns false (i.e., a quit is detected)
 */
void Game::start(){
    Commands c;
    string input;

    while (true) {

        cout << myWorld->getRoomInfo(player->getLocation());

        cout << "> ";  // Prompt for user input

        getline(std::cin, input);  // Get input from user
        cout << endl;

        input = stringToLower(input);
        
        if (!c.doCommand(myWorld, player, input)) {
            break;
        }

    }

}
