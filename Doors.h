#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <iostream>
#include <string>
#include "json11.hpp"
#include <map>
#include "Door.h"

using json = json11::Json;
using namespace std;

class Doors {
private:
    map<string, Door> doorsMap;

public:
    int MAX_DIRS = 6;
    enum DIRS {NORTH='n', SOUTH='s', EAST='e', WEST='w', UP='u', DOWN='d'};
    string DIRECTIONS[6] = {"n","s","e","w","u","d"};

    Doors();

    void loadJson(int minAnum, const json& jsonDir);

    string getExits();
    int goThroughDoor(string direction, map<string, int> portals);
    int hasPortalNamed(const string& portalNameToFind);
    friend std::ostream& operator<<(std::ostream& os, const Doors& doors);
};

#endif
