//
// Created by shani on 11/28/16.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H


//#include "Cab.h"

#include "Map.h"
#include "PointHistory.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;
class Trip {
private:
    int RideID;
    double totalMeterPassed;
    PointHistory* startP;
    PointHistory* destP;
    int numPassengers;
    double taarif;
    Map* layout;
    int timpOfStart;
    int done = 0;
    string gridSize;
    int numObs;
    string obsChain;
    Node* currentP;
    vector<Node*> pass;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & RideID;
        ar & startP;
        ar & destP;
        ar & numPassengers;
        ar & taarif;
    }
public:
    /**
     * constructor
     */
    Trip();
    /**
     * destructor
     */
    ~Trip();
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
    Trip(int idPar,int startXP,int startYP,int endXP,int endYP,int numPass,int taa, int timeOfSt);
    /**
     *
     * @return metter passed
     */
    double getMetterPassed();
    /**
     *
     * @return ride ID
     */
    int getRideID();
    /**
     *
     * @return taarif
     */
    double getTaarif();
    /**
     *
     * @return x of the start point
     */
    int getStartX();
    /**
     *
     * @return y of the start point
     */
    int getStartY();
    /**
     *
     * @return x of the end point
     */
    int getEndX();
    /**
     *
     * @return y of the end point
     */
    int getEndY();
    /**
     *
     * @param mapInput - the new map
     */
    void setMap(Map* mapInput);
    /**
     *
     * @return the map
     */
    Map* getMap();
    /**
     *
     * @return current map
     */
    Node* getMapCurrent();
    /**
     * starts the trip
     * @param speed - the speed of the cab
     */
    Node* getNext(int speed);
    int isDone();
    int getTimeOfStart();
    string getGridSize();
    void setGridSize(string gridSizeInput);
    int getNumObs();
    void setNumObs(int numObsInput);
    string getObsChain();
    void setObsChain(string obsChainInput);
    vector<Node*> getpass();
    void createPass(int speed);
};

#endif //EX2_TRIP_H