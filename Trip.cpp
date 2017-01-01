//
// Created by shani on 11/28/16.
//

#include "Trip.h"
#include "PointHistory.h"

/**
 * constructor
 */
Trip::Trip(){}
/**
 * destructor
 */
Trip::~Trip(){
    delete(layout);
    return;
}
/**
 * constructor
 * @param idPar - ID of the trip
 * @param startXP - x of start point
 * @param startYP - y of start point
 * @param endXP - x of end point
 * @param endYP - y of end point
 * @param numPass - num of passengers in the trip
 * @param taa - the tarrif of the trip
 */
Trip::Trip(int idPar,int startXP,int startYP,int endXP,int endYP,int numPass,int taa,
           int timeOfSt) {
    RideID  = idPar;
    startP = new PointHistory(PointBase(startXP, startYP));
    destP = new PointHistory(PointBase(endXP, endYP));
    numPassengers = numPass;
    taarif = taa;
    layout = NULL;
    timpOfStart = timeOfSt;
    currentP = startP;
    pass = vector<Node*>();
}
/**
 *
 * @return metter passed
 */
double Trip:: getMetterPassed(){return 0.0;}
/**
 *
 * @return ride ID
 */
int Trip:: getTimeOfStart(){ return timpOfStart;}
int Trip:: getRideID(){ return RideID;}
/**
 *
 * @return taarif
 */
double Trip::getTaarif() { return taarif;}
/**
 *
 * @return x of the start point
 */
int Trip::getStartX(){
    return startP->getX();
}
/**
 *
 * @return y of the start point
 */
int Trip::getStartY(){
    return startP->getY();
}
/**
 *
 * @return x of the end point
 */
int Trip::getEndX(){
    return destP->getX();
}
/**
 *
 * @return y of the end point
 */
int Trip::getEndY(){
    return destP->getY();
}
/**
 *
 * @param mapInput - the new map
 */
void Trip::setMap(Map* mapInput) {
    layout = mapInput;
}
/**
 *
 * @return the map
 */
Map* Trip::getMap() {
    return layout;
}
/**
 *
 * @return current map
 */
Node* Trip:: getMapCurrent(){
    return layout->getCurrent();
}
/**
 * starts the trip
 * @param speed - the speed of the cab
 */
Node* Trip::getNext(int speed){
    currentP = pass.front();
    pass.erase(pass.begin());
    int x = 0;
    x++;
    //if((currentP->getX() == destP->getX()) && (currentP->getY() == destP->getY())){
    if(pass.size() == 0){
        done = 1;
        std::cout<<"wow"<<std::endl;
    }
    return currentP;
}
int Trip::isDone() { return done;}

string Trip:: getGridSize(){return gridSize;}
void Trip:: setGridSize(string gridSizeInput){gridSize = gridSizeInput;}
int Trip:: getNumObs(){ return numObs;}
void Trip::setNumObs(int numObsInput){ numObs = numObsInput;}
string Trip:: getObsChain(){ return obsChain;}
void Trip:: setObsChain(string obsChainInput){ obsChain = obsChainInput;}
vector<Node*> Trip:: getpass(){
    return pass;
}
void Trip:: createPass(int speed){
    layout->run(speed);
    pass = layout->getPass();
}