//
// Created by hussa on 8/4/2024.
//
#include "Fleet.h"
fleet::fleet(int id):id(id),numOfShip(1),lastRank(1),numOfPirate(0) {

}

int fleet::getId() const {
    return this->id;
}

int fleet::getLastRank() {
    return this->lastRank++;
}

int fleet::getNumOfPirate() const {
    return this->numOfPirate;
}

int fleet::getNumOfShip() const {
    return this->numOfShip;
}

void fleet::addNumOfPirate() {
    this->numOfPirate++;
}

void fleet::addNumOfShip() {
    this->numOfShip++;
}
