#include "World.h"
#include <vector>
#include <iostream>
#include <sstream>

/**
 * Basic constructor for world
 */
World::World()= default;

/**
 * Searches through all the rooms to find the roomId with the portal name either in its room.portal or its doors
 * @param portalName
 * @return roomId or -1
 */
int World::findRoomIdByPortal(string portalName){
    //cout << "World::findRoomIdByPortal placeholder " << portalName << endl;
    //return 89;
    for(auto& room:rooms){
        if(room.second.getRoomIdWithPortal(portalName)!=-1){
            return room.second.getRoomIdWithPortal(portalName);
        }
    }
    return -1;
}

void World::addPortals(const json& jsonPortals){
    //cout << "World::addPortals placeholder " << jsonPortals.dump() << endl;
    for(auto jp:jsonPortals.array_items()){
        //json jp=entry["portal"];
         string from= jp["from"].string_value();
        bool twoway=jp["two-way"].bool_value();
        string to=jp["to"].string_value();
        addPortal(from,to,twoway);
    }
}

/*
{
    "two-way": false,
    "from": "midgaard-8-down",
    "to": "sewer-2"
  }
*/

/**
 * Discovers the to and from roomId's for the portals and stores them in World's portal
 * If twoway is true then it reverses the from and to and stores that as well
 * @param from
 * @param to
 * @param twoway
 */
void World::addPortal(const string& from, string to, bool twoway){
    //cout << "World::addPortal placeholder " << from <<  " " << to << " " << twoway << endl;
    // find id with map;
    // getRoomIds with from and to
    // roomId of from and to and then store the id and name of rooms in the map 
    // pass string value and store index of room at to
    if(!(from=="")){
        portals[from]=findRoomIdByPortal(to);
        //cout<<from<<endl;
    }
    if(twoway){
        portals[to]=findRoomIdByPortal(from);
    }
}


/**
 * Adds all the rooms of an area (e.g., Midgaard) to the world according to their modified minRoomIdForArea (minAnum + room Id)
 * using Room constructor and World::addRoom
 * @param minAnum
 * @param jsonRooms
 */
void World::addRooms(int minRoomIdForArea, int minObjectIdForArea, int minMobIdForArea, const json &jsonRooms){
    //cout << "World::addRooms placeholder " << minRoomIdForArea <<  " " << jsonRooms.dump() << endl;
    for(const auto& entry:jsonRooms.array_items()){
        Room *room=new Room(minRoomIdForArea,minObjectIdForArea,minMobIdForArea,entry);
        if(room->isStarting()){
            startingRoom=room->getRoomId();
        }
        addRoom(room);
    }
}


/**
 * Add a room to World::rooms map.
 * @param room
 */
void World::addRoom(Room *room) {
    //cout << "World::addRoom placeholder " << room->getRoomId() << endl;
    rooms[room->getRoomId()]=*room;
}
/**
 * Adds all the objects of an area (e.g., Midgaard) to the world according to their modified objectId (minObjectIdForArea + object Id)
 * using the Object constructor and World::addObject
 * @param minAnum
 * @param jsonRooms
 */
void World::addObjects(int minObjectIdForArea, const json &jsonRooms){
    //cout << "World::addObjects placeholder " << minObjectIdForArea <<  " " << jsonRooms.dump() << endl;
    for(auto entry:jsonRooms.array_items()){
    Object *object=new Object(minObjectIdForArea,entry);
    addObject(object);
    }
}

/**
 * Adds an object to the World's map of objects
 * @param object
 */
void World::addObject(Object *object) {
    //cout << "World::addObject placeholder " << object->getObjectInfo() << endl;
    //cout<<object->getObjectInfo()<<endl<<object->getObjectId()<<endl;
    objects[object->getObjectId()]=*object;
}

/**
 * Adds all the Mobs of an area (e.g., Midgaard) to the world according to the modified mobId (minMobIdForArea + mob Id)
 * using the Mob constructor and World::addMob
 * @param minAnum
 * @param jsonMobs
 */
void World::addMobs(int minMobIdForArea, const json &jsonMobs){
    //cout << "World::addMobs placeholder " << minMobIdForArea <<  " " << jsonMobs.dump() << endl;
    for(auto entry:jsonMobs.array_items()){
    Mob *mob=new Mob(minMobIdForArea,entry);
    addMob(mob);
    } 
}

/**
 * Add the mob object to World::mobs
 * @param mob
 */
void World::addMob(Mob *mob) {
    //cout << "World::addMob placeholder " << mob->getName() << endl;
    mobs[mob->getMobId()]=*mob;
}

/**
 * Moves the player in a direction if the direction is available. The direction is a string direction that can be
 * any portion of north, south, east, west, up, down
 * @param player
 * @param direction
 * @return
 */
bool World::move(Player *player, string direction){
    //cout << "World::move placeholder " << player->getHitpoints() <<  direction << endl;
    int locationToCheck=player->getLocation();
    int locationToSet=rooms[locationToCheck].goThroughDoor(direction,portals);
    player->setLocation(locationToSet);
    if(player->getLocation()==locationToSet&&player->getLocation()!=-1){
        return true;
    }
    else {
       player->setLocation(locationToCheck); 
    }
    return false;
}

/**
 * Gets the starting location of the world
 * @return
 */
int World::getStartingLocation() const {
    return startingRoom;
}

/**
 * Generates information for a room including basic room info, ID, room name, room description, room objects,
 * mob info, and exits. It returns all of this information as a string
 * @param roomId
 * @return
 */
string World::getRoomInfo(int roomId){
    ostringstream infoStream;

    // Can use infoStream like this to concatenate strings
    //infoStream << rooms[roomId].getRoomInfo() <<endl;
    
    string x = rooms[roomId].getRoomInfo();
    cout<<x;
    //infoStream << getObjectInfo(rooms[roomId].getObjectIds()) <<endl;
    // cout<<"Hi"<<endl;
    cout<<"You see ";
    for(int i:rooms[roomId].getObjectIds()){
        cout<<objects[i].getName();
        cout<<", ";
    }
    cout<<endl;
    //
    if(rooms[roomId].getMobIds().size()>0){
        for(int i:rooms[roomId].getMobIds()){
            cout<<mobs[i].getName();
        }
    }
    infoStream<<endl;
    
    return infoStream.str();
}

/**
 * From within a room, look at an item with the provided name and return the item description.
 * @param roomId
 * @param item
 * @return the object's description
 */
string World::look(int roomId, string item){
    //cout << "World::look placeholder " << roomId <<  item << endl;
    return objects[getObjectIdByNameInRoom(rooms[roomId],item)].getObjectDetails();
}
/**
 * Search through all the objects and check if objectIdExistsInRoom and if itemNameToFind matches the object found in the room * 
 * The name match can be a substring of the Object name but must match the entire itemNameToFind
 * Example: if itemNameToFind is "sci" and their is a scimitar in the room then the item exists in the room
 *          for the partial match you might use .getName().substr(0, itemNameToFind.size())
 *          if multiple objects in the room match, it will return the first one that matches
*/
int World::getObjectIdByNameInRoom(Room r, string itemNameToFind){
    //cout << "World::getObjectIdByNameInRoom placeholder " << itemNameToFind << endl;
    //r.getObjectIds();
    //r.getObjectIds.find(object.getObjectId())!=r.getObjectIds().end()
    int matchingObjId = -1;
    for (auto objPair : objects){
        auto object = objPair.second;
        // CODE: check for object
        if(object.getName()==itemNameToFind){
            matchingObjId=object.getObjectId();
        }
    }
    for (auto objPair : objects){
        auto object = objPair.second;
        // CODE: check for object
        if(object.getName().substr(0, itemNameToFind.size())==itemNameToFind){
            matchingObjId=object.getObjectId();
            for(int i:r.getObjectIds()){
                if (i==object.getObjectId()){
                return matchingObjId;
                }
            }  
        }
    }
    return matchingObjId;
}

/**
 * Given the player's location, pickup the item and place it into the player's inventory
 * @param player
 * @param itemName
 * @return the name of the item that was picked up
 */
string World::pickupObjectByName(Player *player, string itemNameToFind){
    //cout << "World::pickupObjectByName placeholder " << itemNameToFind << endl;
    int roomId=player->getLocation();
    int objectId=getObjectIdByNameInRoom(rooms[roomId],itemNameToFind);
    string returner=objects[objectId].getName();
    player->addToInventory(getObjectIdByNameInRoom(rooms[player->getLocation()],itemNameToFind));
    rooms[player->getLocation()].removeObject(getObjectIdByNameInRoom(rooms[player->getLocation()],itemNameToFind));
    return returner;
}

/**
 * Given the player's location, drop the item with the provided indexId and place it on the floor in the current room.
 * @param player
 * @param indexId
 * @return the object's name
 */
string World::dropObject(Player *player, int indexId){
    //cout << "World::dropObject placeholder " << player <<  " " << indexId << endl;
    cout<<objects[player->getInventory()[indexId]].getName();
    addObject(&objects[player->getInventory()[indexId]]);
    string returner=objects[player->getInventory()[indexId]].getName();
    //player->getInventory().pop_back();
    return returner;
}

/**
 * Given a vector of Object ids it will return the list of inventory items using an index
 * @param inventoryItems
 * @return
 */
string World::getObjectNames(const vector<int>& inventoryItems) {
    ostringstream infoStream;
    //cout << "World::getObjectNames placeholder " << inventoryItems.at(0)  << endl;
    for(int i : inventoryItems){
        infoStream<<objects.at(i).getObjectInfo()<<endl;
    }
    return infoStream.str();
}

/**
 * Get the first mob in a room
 * @param roomId
 * @return Mob object
 */
Mob World::getMob(int roomId){
    //cout << "World::getMob placeholder " << roomId << endl;
    if(mobs[roomId].getMobId()!=-1){
        return mobs[roomId];
    }
    return Mob(); // default return when not found
}

/**
 * Remove a mob with the mobId from the room and update the room in the rooms map.
 * @param roomId
 * @param mobId
 */
void World::removeMob(int roomId, int mobId){
    //cout << "World::removeMob placeholder " << roomId <<  " " << mobId << endl;
    rooms[roomId].removeMob(mobId);
}

/**
 * The sequence of actions where a player attacks a mob and the mob attacks the player until one of the dies
 * On death of the mob, the mob is removed from the world the player is notified "You win, you have killed the "
 * On death of the player, the player is notified "You Died! You have been killed by"
 * As this gets more complicated, it should be extracted into its own class
 * @param player
 */
void World::performAttack(Player *player) {
    //cout << "World::performAttack placeholder " << player->getHitpoints() << endl;
    //player->getHitpoints();
    //getMob(player->getLocation());
    int playerAttack=0;
    int mobHp;
    int playerHp;
    Mob mob=getMob(player->getLocation());
    mobHp=mob.rollForHitPoints();
    playerHp=player->getHitpoints();
    while(playerHp>0 && mobHp>0){
        playerAttack=player->rollForAttack();
        mobHp-=playerAttack;
        if(mobHp<=0){
            cout<<"You win, you have killed the ";
            cout<<mob.getName()<<endl;
            break;
        }
        int mobAttack=mob.rollForAttack();
        playerHp-=mobAttack;
        if(playerHp<=0){
            cout<<"You Died! You have been killed by";
            cout<<mob.getName()<<endl;
            break;
        }
    }
    //removeMob(player->getLocation(),mob.getMobId());
}
