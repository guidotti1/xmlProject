#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;

class Room
{
public :
    Room();
    Room(string nameInit, string descriptionInit, string statusInit, string typeInit);

private :

};

class Item
{
public:
    Item();
    Item(string nameInit, string writingInit, string statusInit, string ownerInit);
    void drop();
    void take();
    void read();
    void turnOn();
    void putInContainer(); //probably should pass the current owner and new owner (e.g. user to container)


private:
    string name;
    string writing;
    string status;
    string owner;
    bool on;
    //trigger itemTrigger;
};


void getItems(XMLNode);
void getTriggers(XMLNode);
void getBorders (XMLNode);
void getContainers(XMLNode);
void getCreatures(XMLNode);
void getCondition(XMLNode node);
void getAttack(XMLNode node);


int main (int argc, char ** argv) {

    string gameFile = "testGame.xml";

    // this opens and parses the correct XML file:
    XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
    int i = 0;
    // get the first room node
    XMLNode roomNode=xMainNode.getChildNode(i++);


    do {
    string roomType, name, description = "";

    //room information
    //room type
    XMLNode roomTypeNode = roomNode.getChildNode("type");
    if (!roomTypeNode.isEmpty())
        {
        roomType = roomTypeNode.getText();
        }

    // Get the room name
    XMLNode nameNode = roomNode.getChildNode("name");
    if (!nameNode.isEmpty())
        {
        name = nameNode.getText();
        }

    //Get the room description
    XMLNode descriptionNode = roomNode.getChildNode("description");
    if (!descriptionNode.isEmpty())
        {
        description = descriptionNode.getText();
        }

    cout << "(room information)" << endl;
    cout << "Name of the room is : " << name << endl;
    cout << "Description of the room is : " << description << endl;
    cout << "Type of the room is : " <<  roomType << endl;


    //get information for items in the room
    getItems(roomNode);
    //get information for triggers in the room
    getTriggers(roomNode);
    //get information for borders in the room
    getBorders(roomNode);
    //get information for containers in the room
    getContainers(roomNode);
    //get information for creatures in the room
    getCreatures(roomNode);




    roomNode=xMainNode.getChildNode(i++);
    } while (!roomNode.isEmpty());

    cout << endl;
    return 0;
}


void getItems(XMLNode node)
{
    int numberItems = node.nChildNode("item");
    for (int nItems = 0; nItems < numberItems; nItems++)
        {
            XMLNode itemNode = node.getChildNode("item", nItems);
            string itemName, itemWriting, itemStatus = "";

            XMLNode itemNameNode = itemNode.getChildNode("name");
            if (!itemNameNode.isEmpty())
                {
                itemName = itemNameNode.getText();
                }

            XMLNode itemWritingNode = itemNode.getChildNode("writing");
            if(!itemWritingNode.isEmpty())
                {
                itemWriting = itemWritingNode.getText();
                }

            XMLNode itemStatusNode = itemNode.getChildNode("status");
            if (!itemStatusNode.isEmpty())
                {
                itemStatus = itemStatusNode.getText();
                }

            cout << "(item information)" << endl;
            cout << "Item name : " << itemName << endl;
            cout << "Item writing : " << itemWriting << endl;
            cout << "Item status : " << itemStatus << endl;

            //turnon information for the item
            XMLNode turnonNode = itemNode.getChildNode("turnon");
            if (!turnonNode.isEmpty())
                {
                string turnonPrint, turnonAction = "";

                XMLNode turnonPrintNode = turnonNode.getChildNode("print");
                if (!turnonPrintNode.isEmpty())
                    {
                    turnonPrint = turnonPrintNode.getText();
                    }

                XMLNode turnonActionNode = turnonNode.getChildNode("action");
                if(!turnonActionNode.isEmpty())
                    {
                    turnonAction = turnonActionNode.getText();
                    }

                cout << "(item turnon information)" << endl;
                cout << "Item turnon print : " << turnonPrint << endl;
                cout << "Item turnon action : " << turnonAction << endl;
                }
        }
}

void getTriggers(XMLNode node)
{
    int numberTriggers = node.nChildNode("trigger");
    for (int nTriggers = 0; nTriggers < numberTriggers; nTriggers++)
        {
            XMLNode triggerNode=node.getChildNode("trigger", nTriggers);
            string triggerType, command, triggerPrint, action = "";

            XMLNode typeNode = triggerNode.getChildNode("type");
            if (!typeNode.isEmpty())
                {
                triggerType = typeNode.getText();
                }

            XMLNode commandNode = triggerNode.getChildNode("command");
            if (!commandNode.isEmpty())
                {
                command = commandNode.getText();
                }

            XMLNode printNode = triggerNode.getChildNode("print");
            if (!printNode.isEmpty())
                {
                triggerPrint = printNode.getText();
                }

            XMLNode actionNode = triggerNode.getChildNode("action");
            if (!actionNode.isEmpty())
                {
                action = actionNode.getText();
                }


            cout << "(trigger information)" << endl;
            cout << "type : " << triggerType << endl;
            cout << "command : " << command << endl;
            cout << "print : " << triggerPrint << endl;
            cout << "action : " << action << endl;

            cout << "condition information for trigger" << endl;
            getCondition(triggerNode);
        }
}

void getBorders (XMLNode node)
{
    int numberBorders = node.nChildNode("border");
    for (int nBorders = 0; nBorders < numberBorders; nBorders++)
        {
        XMLNode borderNode = node.getChildNode("border", nBorders);
        string borderDirection, borderName = "";

        XMLNode borderDirectionNode = borderNode.getChildNode("direction");
        if (!borderDirectionNode.isEmpty())
            {
            borderDirection = borderDirectionNode.getText();
            }

        XMLNode borderNameNode = borderNode.getChildNode("name");
        if (!borderNameNode.isEmpty())
            {
            borderName = borderNameNode.getText();
            }

        cout << "(border information)"<<endl;
        cout << "direction : " << borderDirection << endl;
        cout << "name : " << borderName << endl;
        }
}

void getContainers(XMLNode node)
{
    int numberContainers = node.nChildNode("container");
    for (int nContainers = 0; nContainers < numberContainers; nContainers++)
        {
        XMLNode containerNode = node.getChildNode("container", nContainers);
        string containerName, containerStatus, containerAccept = "";

        XMLNode containerNameNode = containerNode.getChildNode("name");
        if (!containerNameNode.isEmpty())
            {
            containerName = containerNameNode.getText();
            }

        XMLNode containerStatusNode = containerNode.getChildNode("status");
        if (!containerStatusNode.isEmpty())
            {
            containerStatus = containerStatusNode.getText();
            }

        XMLNode containerAcceptNode = containerNode.getChildNode("accept");
        if (!containerAcceptNode.isEmpty())
            {
            containerAccept = containerAcceptNode.getText();
            }
        cout << "(container information)"<<endl;
        cout << "container name : " << containerName << endl;
        cout << "container status : " << containerStatus << endl;
        cout << "container accept :" << containerAccept << endl;

        cout << "(items in container)" << endl;
        getItems(containerNode);

        cout << "(triggers for container)" << endl;
        getTriggers(containerNode);
        }

}

void getCreatures(XMLNode node)
{
    int numberCreatures = node.nChildNode("creature");
    for (int nCreatures = 0; nCreatures < numberCreatures; nCreatures++)
        {
        XMLNode creatureNode = node.getChildNode("creature", nCreatures);
        string creatureName, creatureVulnerability ="";

        XMLNode creatureNameNode = creatureNode.getChildNode("name");
        if (!creatureNameNode.isEmpty())
            {
            creatureName = creatureNameNode.getText();
            }

        XMLNode creatureVulnerabilityNode = creatureNode.getChildNode("vulnerability");
        if (!creatureVulnerabilityNode.isEmpty())
            {
            creatureVulnerability = creatureVulnerabilityNode.getText();
            }

        cout << "(creature information)"<<endl;
        cout << "creature name : "<< creatureName << endl;
        cout << "creature vulnerability : " << creatureVulnerability << endl;
        cout << "attack for creature : " << endl;
        getAttack(creatureNode);
        cout << "trigger for creature : " << endl;
        getTriggers(attackNode);
        }
}

void getCondition(XMLNode node)
{
    int numberConditions = node.nChildNode("condition");
    for (int nConditions = 0; nConditions < numberConditions; nConditions++)
        {
            XMLNode conditionNode = node.getChildNode("condition", nConditions);
            string object, status, has, owner = "";


            XMLNode hasNode = conditionNode.getChildNode("has");
            if (!hasNode.isEmpty())
                {
                has = hasNode.getText();
                }

            XMLNode ownerNode = conditionNode.getChildNode("owner");
            if (!ownerNode.isEmpty())
                {
                owner = ownerNode.getText();
                }

            XMLNode objectNode = conditionNode.getChildNode("object");
            if (!objectNode.isEmpty())
                {
                object = objectNode.getText();
                }

            XMLNode statusNode = conditionNode.getChildNode("status");
            if (!statusNode.isEmpty())
                {
                status = statusNode.getText();
                }

            cout << "(condition information)"<<endl;
            cout << "owner : " << owner << endl;
            cout << "has : " << has << endl;
            cout << "object : " << object << endl;
            cout << "status : " << status << endl;
            }
}

void getAttack(XMLNode node)
{
        XMLNode attackNode = node.getChildNode("attack");
        cout << "condition for attack " <<endl;
        getCondition(attackNode);

        string print ="";
        XMLNode printNode = attackNode.getChildNode("print");
        if (!printNode.isEmpty())
            {
            print = printNode.getText();
            }
        int numberActions = attackNode.nChildNode("attack");
        cout << "actions for attack " << endl;
        for (int nActions = 0; nActions < numberActions; nActions ++)
            {
            XMLNode actionNode = node.getChildNode("action", nActions);
            string actionInfo = actionNode.getText();
            cout << "actionInfo " << actionInfo << endl;
            }



}

