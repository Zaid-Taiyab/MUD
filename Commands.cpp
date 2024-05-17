#include "Commands.h"
#include <sstream>

/**
 * Convert a value from a string to input, if the conversion fails return -1
 * @param input
 * @return the new integer value
 */
int convertToNumeric(string input){
    int number =-1;
    // Create a stringstream from the input
    stringstream ss(input);

    // CODE: Try to read an integer from the stringstream, if successful return number else return -1 and give error message
    if (ss>>number) { // using the ss like cin into a number
         return number;
    } else {
         cout << "Error: The input is not a valid integer." << endl;
    }
    return -1;
}

/**
 * Get numeric input from the user
 * @return the integer value entered unless not convertible then a -1
 */
int getNumericInput(){
    string input;
    // GET FROM USER
    cin>>input;
    return convertToNumeric(input);
}

/**
 * Handle the commands entered by the player in the game loop
 * @param myWorld
 * @param player
 * @param input
 * @return
 */

bool Commands::doCommand(World *myWorld, Player *player, string input){
    //cout<<myWorld->getRoomInfo(player->getLocation());
    if(input[0]=='u'){
        myWorld->move(player,"u");
        return true;
    }
    if(input[0]=='s'){
        myWorld->move(player,"s");
        return true;
    }
    if(input[0]=='n'){
        myWorld->move(player,"n");
        return true;
    }
    if(input[0]=='e'){
        myWorld->move(player,"e");
        return true;
    }
    if(input[0]=='w'){
        myWorld->move(player,"w");
        return true;
    }
    if (input[0] == 'n' || input[0] == 's' || input[0] == 'e' || input[0] == 'w' || input[0] == 'u' || (input[0] == 'd' && (input.size()==1 || input[1] == 'o') ) ) {
        return true;
    }
    size_t space_pos = input.find(" ");
    string command = input.substr(0,space_pos);
    string commandParam = "";

    // Check if a space is found in input, if it is we may have a commandParam too add a null character at the end

    if (command == "teleport"||command=="Teleport") {  // teleport
        // CODE: uses a numeric commandParam to determine destination room Id
        //convertToNumeric("teleport");
        commandParam=input.substr(space_pos+1);
        size_t spaceChecker=commandParam.find(" ");
        commandParam=commandParam.substr(spaceChecker+1);
        int x=convertToNumeric(commandParam);
        //cout<<x<<endl;
        player->teleport(x);
    }
    
    if (command[0] == 'l') {  // look
        commandParam=input.substr(space_pos+1);
        cout<<myWorld->look(player->getLocation(),commandParam);
    }
    
    if (command[0] == 'g') { 
        commandParam=input.substr(space_pos+1);
            cout<<myWorld->pickupObjectByName(player,commandParam)<<endl;    
    }
    if (command[0] == 'i') {  // inventory
        
        cout<<myWorld->getObjectNames(player->getInventory())<<endl;
    }
    if (command[0] == 'd') {  // drop
        // CODE: if the player has items in their inventory then print them out with a number index of each, read in the number index, and drop the item
        myWorld->dropObject(player, 0);
        myWorld->dropObject(player, 1);
    }
    if(command[0]=='1'){
        return true;
    }
    if (command[0] == 'a') {  // attack
        // CODE: use the attack method found in the World class
        //cout<<"Guardian"<<endl;
        myWorld->performAttack(player);
        if(player->getLocation()==10418){
            cout<<"You have killed the Guardian.";
        }
    }
    if (input == "exit" || input == "quit" || input == "q") {
        cout << "Exiting game loop. Goodbye!\n";
        return false;
    }
    //myWorld->getObjectNames({1,2});
    return true;
}

/**
 * Get a list of commands
 * @return a list of possible commands the player might use
 */
string Commands::getCommands(){
    ostringstream infoStream;

    infoStream << "look, drop, get, inventory, teleport, help, and attack ";

    return infoStream.str();
}
