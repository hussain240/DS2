//
// Created by hussa on 8/4/2024.
//

#ifndef DS2_FLEET_H
#define DS2_FLEET_H
class fleet{
    int id;
    int numOfShip;
    int lastRank;
    int numOfPirate;
public:
    fleet(int id);
    int getNumOfShip()const;
    int getLastRank();
    int getNumOfPirate()const;
    int getId()const;
    void addNumOfShip(int num);
    void addNumOfPirate(int toAdd);
};
#endif //DS2_FLEET_H
