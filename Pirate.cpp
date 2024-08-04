//
// Created by hussa on 8/4/2024.
//
#include "Pirate.h"
pirate::pirate(int salary, int id, int rank):salary(salary),id(id),rank(rank) {

}

int pirate::getRank() const {
    return this->rank;
}

int pirate::getSalary() const {
    return this->salary;
}

int pirate::paySalary(int money) {
    this->salary+=money;
}

int pirate::getId() const {
    return this->id;
}