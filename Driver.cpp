//
// Created by shani on 11/28/16.
//

#include "Driver.h"
#include "PointBase.h"
#include "PointHistory.h"

/**
 * constractor
 */
Driver::Driver() {}
/**
 * constructor
 * @param ID1 - the driver's ID
 * @param age1 - the driver's age
 * @param materialStatus1 - the driver's material status
 * @param yearsOfExperience1 - the driver's years of experience
 * @param avgDestination1 - the driver's avg destination
 * @param cabID1 - the driver's cab ID
 */
Driver::Driver(int ID1, int age1, char materialStatus1, int yearsOfExperience1, int cabID1){
    ID = ID1;
    age = age1;
    materialStatus = materialStatus1;
    yearsOfExperience = yearsOfExperience1;
    cabID = cabID1;
    avgsatisfaction = 0;
    location = new PointHistory(PointBase(0,0));
    steps = 0;
    isTripDone = true;
    trip = NULL;
    //trips = vector<Trip*>;
}
/**
 * Destructor
 */
Driver::~Driver() {
    delete (location);
    return;
}
/**
 *
 * @return avg of satisfaction.
 */
double Driver:: getAvgSatisfaction(){ return avgsatisfaction;}
/**
 *
 * @return driver ID
 */
int Driver :: getDriverID(){ return ID;}
/**
 *
 * @return location
 */
Node* Driver:: getLocation(){ return location;}
/**
 * sests the location to a new one
 * @param p - the new location
 */
void Driver::setLocation(Node* p) {
    if (location!= NULL) {
        delete (location);
    }
    location = p;
}
/*
bool Driver::isTripDone() {
    return isTripDone;
}*/
/**
 * steps discribes each trip made by driver
 */
void Driver::increaseSteps() {
    steps++;
}
/**
 *
 * @return number of trips made by driver
 */
int Driver::getSteps() { return steps;}

void Driver::doOneStep() {

    location = trip->getNext(1);
    if (location->getX() == trip->getEndX() && location->getY() == trip->getEndY()) {
        isTripDone = true;
    }
}

void Driver::addTrip(Trip* newTrip){
    trip = newTrip;
    isTripDone = true;
}
bool Driver::tripDone() {
    return isTripDone;
}
Trip* Driver:: getTrip(){ return trip;}
bool Driver:: istripDone(){ return isTripDone;}
void Driver::setTripDone(bool b){ isTripDone = b;}
/*
void Driver::deletetrip() {
    trips.erase(trips.begin());
}*/
/*
vector<Node*> Driver:: getpass(){
    return pass;
}*/