//
// Created by hussa on 8/4/2024.
//

#ifndef DS2_PIRATE_H
#define DS2_PIRATE_H
class pirate{
    int salary;
    int id;
    int rank;
public:
    pirate(int salary,int id,int rank);
    int getRank()const;
    int getSalary()const;
    int paySalary(int money);
    int getId()const;
    ~pirate()=default;
};

#endif //DS2_PIRATE_H
