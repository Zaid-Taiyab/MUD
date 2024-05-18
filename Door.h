#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include <string>
#include "json11.hpp"

using json = json11::Json;
using namespace std;

class Door {
    
    // a room exit will be a room id within the same area
    int exitToRoomId;

    // If existing then this door will transport the user through a portal to another area in the game
    // portal names are strings
    // Example: from Midgaard to Mud School    
    std::string exitToPortal;

public:
    Door(){
        exitToRoomId = -1;
        exitToPortal = "";
    }

    void loadJson(int minANum, json doorJson);
    
    friend ostream& operator<<(std::ostream& os, const Door& door);

    bool exitsToRoom(int roomId){
        return exitToRoomId == roomId;
    }
    
    bool exitsToPortal(string portalToFind);
    
    bool hasAnExit();

    int getExitRoomId(map<string, int> portals);
    
};

#endif

