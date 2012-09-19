#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <sstream>
using namespace std;

class Room
{
public:
    Room * NorthPointer;
    Room * EastPointer;
    Room * WestPointer;
    Room * SouthPointer;
    int xCoord;
    int yCoord;
    int allowedPaths [4];


    Room ()
    {
        xCoord = 0;
        yCoord = 0;
        srand(time(NULL));
        for( int i = 0; i < 4; i++)
        {
            int canPass = rand() % 2;
            allowedPaths[i] = canPass;
        }
    }

    Room (Room * origin, int direction)
    {
        srand(time(NULL));
        for( int i = 0; i < 4; i++)
        {
            int canPass = rand() % 2;
            allowedPaths[i] = canPass;
        }
        allowedPaths[direction] = 1;

        if (direction == 0)
        {
            NorthPointer = origin;
            origin -> SouthPointer = this;
            yCoord = origin -> yCoord - 1;
            xCoord = origin -> xCoord;
        }
        if (direction == 1)
        {
            EastPointer = origin;
            origin -> WestPointer = this;
            yCoord = origin -> yCoord;
            xCoord = origin -> xCoord - 1;
        }
        if (direction == 2)
        {
            WestPointer = origin;
            origin -> EastPointer = this;
            yCoord = origin -> yCoord ;
            xCoord = origin -> xCoord + 1;
        }
        if (direction == 3)
        {
            SouthPointer = origin;
            origin -> NorthPointer = this;
            yCoord = origin -> yCoord + 1;
            xCoord = origin -> xCoord;
        }


    }

    void printRoom()
    {
        cout << "\n\n";
        for(int row =0; row < 21; row++)
        {
            for (int column = 0; column < 80; column++ )
            {
                //TOP
                if (row < 7)
                {
                    if (allowedPaths[0] == 0)
                    {
                        cout << "-";
                    }
                    else
                    {
                        if( column < 30 || column > 50)
                        {
                            cout << "-";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                //MIDDLE
                else if (row >= 7 && row <= 14)
                {
                            //WEST
                            if (column < 30)
                            {
                                if(allowedPaths[2] == 0)
                                {
                                    cout << "-";
                                }
                                else
                                {
                                    if (row < 10 || row > 12)
                                    {
                                        cout << "-";
                                    }
                                    else
                                     {
                                        cout << " ";
                                     }
                                }
                            }
                            //CENTER
                            else if (column >= 30 && column <= 50)
                            {
                                cout << " ";
                            }
                            //EAST
                            if (column > 50)
                            {
                                if(allowedPaths[1] == 0)
                                {
                                    cout << "-";
                                }
                                else
                                {
                                    if (row < 10 || row > 12)
                                    {
                                        cout << "-";
                                    }
                                    else
                                     {
                                        cout << " ";
                                     }
                                }
                            }
                }
                //BOTTOM
                if (row > 14)
                {
                    if (allowedPaths[3] == 0)
                    {
                        cout << "-";
                    }
                    else
                    {
                        if( column < 30 || column > 50)
                        {
                            cout << "-";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
            }
            cout << "\n";
        }
        cout << "(" << xCoord << ", " << yCoord << ")";
    }

    string toString()
    {
        stringstream convert;
        convert << xCoord << "," << yCoord;
        return convert.str();
    }

    ~Room()
    {
        delete NorthPointer;
        delete EastPointer;
        delete WestPointer;
        delete SouthPointer;
    }
};

int main ()
{
    std::map<string, Room*> RoomMap;
    cout << "\n";
    //this is the setup
    Room * current = new Room();
    RoomMap[current -> toString()] = current;
    //till here

    string input;
    int direction;
    bool chadash;

    input = "";
    while(input != "exit")
    {
        current -> printRoom();
        cin >> input;
        if(input == "north")
        {
            if(current -> NorthPointer == NULL)
            {
                direction = 3;
                chadash = true;
            }
            else
            {
                chadash = false;
                current = current -> NorthPointer;
            }
        }
        else if(input == "east")
        {
            if(current -> EastPointer == NULL)
            {
                direction = 2;
                chadash = true;
            }
            else
            {
                chadash = false;
                current = current -> EastPointer;
            }
        }
        else if(input == "west")
        {
            if(current -> WestPointer == NULL)
            {
                direction = 1;
                chadash = true;
            }
            else
            {
                chadash = false;
                current = current -> WestPointer;
            }
        }
        else if(input == "south")
        {
            if(current -> SouthPointer == NULL)
            {
                direction = 0;
                chadash = true;
            }
            else
            {
                chadash = false;
                current = current -> SouthPointer;
            }
        }

        if(chadash == true)
        {
            Room* temp = new Room(current, direction);
            //RoomMap.find(temp -> toString());
            if(RoomMap.find(temp -> toString()) == RoomMap.end())
            {
                RoomMap[current -> toString()] = temp;
                current = temp;
            }
            else
            {
                if(direction == 0) //north
                {
                    current -> SouthPointer = RoomMap[temp->toString()];
                    RoomMap[temp->toString()] -> NorthPointer = current;

                }
                if(direction == 1) //east
                {
                    current -> WestPointer = RoomMap[temp->toString()];
                    RoomMap[temp->toString()] -> EastPointer = current;
                }
                if(direction == 2) //west
                {
                    current -> EastPointer = RoomMap[temp->toString()];
                    RoomMap[temp->toString()] -> WestPointer = current;
                }
                if(direction == 3) //south
                {
                    current -> NorthPointer = RoomMap[temp->toString()];
                    RoomMap[temp->toString()] -> SouthPointer = current;
                }
            }
        }

    }
    return 0;
}

