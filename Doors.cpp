#include "Doors.h"
#include <sstream>
#include "utils.h"
/**
 * A default constructor for Doors
 */
Doors::Doors(){
    for (auto d : DIRECTIONS){
        doorsMap[d] = Door();
    }
}

/**
 * Get a string containing the letter of a direction n,s,e,w,u,d
 * @param strDirection
 * @return
 */
string getDirLetter(string strDirection){
    string letter = strDirection.substr(0,1);
    return stringToLower(letter);
}

/**
 * Override << to print out the doors
 * @param os
 * @param doors
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Doors& doors) {
    for (auto strDirection : doors.DIRECTIONS){
        Door d = doors.doorsMap.at(getDirLetter(strDirection));
        os << strDirection << " " << d << " ";
    }
    return os;
}


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
void Doors::loadJson(int minRoomIdForArea, const json& jsonDoors){
    //cout << "Doors::loadJson placeholder for compilation " << minRoomIdForArea << " " << jsonDoors.dump() << endl;
    for(const auto& entry:jsonDoors.array_items()){
        Door *door = new Door();
        door->loadJson(minRoomIdForArea,entry);
        doorsMap[entry["dir"].string_value().substr(0,1)]=*door;
    }
}

/**
 * Return a string list of the exits the current doors offer
 * The list must be comma delimited + space delimited with no extra comma on the end
 * n, s, e, w, u, d
 * @return
 */
string Doors::getExits(){

    ostringstream infoStream;
    bool isFirst = true;

    for (auto strDirection : DIRECTIONS){
        //cout << "Doors::getExits placeholder " << strDirection << " " << endl;
        // CODE: get the door that's in that direction;
        // CODE: if it has an exit (either another room direct or portal) print this direction as a single letter
        if(doorsMap.at(strDirection).hasAnExit()){
            cout<<strDirection<<endl;
        }
    }

    return infoStream.str();
}

/**
 * Return the results of moving through a door in the given direction (i.e., the room Id)
 * @param direction
 * @param portals
 * @return
 */
int Doors::goThroughDoor(string direction, map<string, int> portals){
    // CODE: get the door using the map and then get the room id of the destination of that door (will need to pass in portals)    
    //cout << "Doors::getExits placeholder " << direction << " " << endl;
    map<string,int> x=portals;
    return doorsMap.at(direction).getExitRoomId(portals);
}

/**
 * Check if this set of doors has a remote location with the given portal name
 * @param key
 * @return
 */
int Doors::hasPortalNamed(const string& portalNameToFind){
    //cout << "Doors::hasPortalNamed placeholder " << portalNameToFind << " " << endl;
    // CODE: check if the doors include a portal named portalName
    for(auto& door:doorsMap){
        if(door.second.exitsToPortal(portalNameToFind)==true){
            return true;
        }
    }
    //if(doorsMap.find(portalNameToFind)==doorsMap.end()){
     //   return false;
    //}
    return false;
}
