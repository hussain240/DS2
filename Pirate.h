//
// Created by hussa on 8/4/2024.
//

#ifndef DS2_PIRATE_H
#define DS2_PIRATE_H
class pirate{
    int salary;
    int id;
    int rank;
    int fleetId;
public:
    pirate(int salary,int id,int rank,int fleetId);
    int getRank()const;
    int getSalary()const;
    void paySalary(int money);
    int getFleetId()const;
    ~pirate()=default;
};

#endif //DS2_PIRATE_H
