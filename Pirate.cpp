//
// Created by hussa on 8/4/2024.
//
#include "Pirate.h"
pirate::pirate(int salary, int id, int rank,int fleetId):salary(salary),id(id),rank(rank),fleetId(fleetId) {

}

int pirate::getRank() const {
    return this->rank;
}

int pirate::getSalary() const {
    return this->salary;
}

void pirate::paySalary(int money) {
    this->salary+=money;
}

int pirate::getFleetId() const {
    return this->fleetId;
}