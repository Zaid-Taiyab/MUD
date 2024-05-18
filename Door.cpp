#include "Door.h"
#include "utils.h"

/**
 * Loads the door's json data include to and portal values
 * The to and portal values are mutually exclusive
 * if to is_null() then we have a portal exit otherwise we have a normal room exit
 * 
*/

/**
 * Load the Door and direction information from a json object, from inside room
 * "doors": [
            {
                "dir": "north",
                "to": 54,
                "portal": null
            },
            {
                "dir": "south",
                "to": 5,
                "portal": null
            },...]
 * @param minRoomIdForArea
 * @param jsonDoors
 */

void Door::loadJson(int minRoomIdForArea, json doorJson){        
    // CODE: check which one is not null and use it.
    //exitToRoomId == -1;
    //exitToPortal = "";
    if(doorJson["portal"].is_null()){
        exitToRoomId=doorJson["to"].int_value()+minRoomIdForArea;
    }
    else {
        exitToPortal=doorJson["portal"].string_value();
    }
}

/**
 * Override the << to print out a door in a specific direction
 * @param os
 * @param dir
 * @return
 */
ostream& operator<<(std::ostream& os, const Door& door){
    if (door.exitToRoomId > -1) {
        os << "ID:" << door.exitToRoomId << " ";
    } else {
        os << "portal:" << door.exitToPortal;
    }
    return os;
}

/**
 * Checks if this door uses the provided portal name
*/
bool Door::exitsToPortal(string portalToFind){    
    return caseInsensitiveCompare(portalToFind, exitToPortal);
}

/**
 * A direction has either an exit room ID or a remote location associatd with it
 * @return bool
 */
bool Door::hasAnExit(){
    return exitToRoomId != -1 || exitToPortal.length() == 0;
}

/**
 * If exitToPortal has a value then return the roomId from the portals Map
 * else return exitToRoomId 
 * @return the roomId int that this door exits to
*/
int Door::getExitRoomId(map<string, int> portals){
    //cout << "Door::getExitRoomId placeholder " << exitToPortal << " in " << portals[exitToPortal] << endl ; 
    // CODE: if there's a portal exit then provide the ID of the destination room
    if(exitToPortal!=""){
        return portals.at(exitToPortal);
    }
    else{
        return exitToRoomId;
    }
    return -1;
}
