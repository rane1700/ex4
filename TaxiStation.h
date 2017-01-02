//
// Created by shani on 11/28/16.
//

#ifndef EX2_STATIONSTATION_H
#define EX2_STATIONSTATION_H

#include <array>

using namespace std;

#include <vector>
#include "Driver.h"
#include "Cab.h"
#include "Trip.h"
#include "Map.h"
#include "Clock.h"
#include <map>

class TaxiStation {
private:
    vector<Driver*> drivers;
    vector<Node*> Location;
    vector<Cab*> cabs;
    vector<Trip*> trips;
    Node *p;
    int findTripNumInVector(int tripId);
    Driver* findDriverAlreadyArrived(int startX,int startY,int id);
    Clock clock;
public:
    /**
     * constructor
     */
    TaxiStation();
    /**
     * destructor
     */
    ~TaxiStation();
    /**
     * add driver to driver's vector
     * @param driver Driver object to be added
     */
    void addDriver(Driver* driver);
    /**
     * Add Cab to the cab's vector
     * @param cab Cab object to be added
     */
    void addCab(Cab* cab);
    /**
     * add Trip to trip's vector
     * @param trip Trip to be added
     * @param gridSize size of grid for creation of mao
     * @param numObs number of obstacles expected in map
     * @param obsChain string of obstacles
     */
    void addTrip(Trip* trip);
    /**
      * Get Driver object by id
      * @param id input
      * @return Driver object
      */
    Driver* getDriverByID(int id);
    /**
     * Get Cab object by id
     * @param id input
     * @return Cab object
     */
    Cab* getCab(int id);
    /**
     * Get Trip object by id
     * @param id input
     * @return Trip object
     */
    Trip* getTrip(int id);
    /**
     * prints the driver current location by id given
     * @param id input
     */
    void getDriverLocation(int id);
    /**
     * Start all trips added
     */
    void startAll();

    void start();

    Driver* getDriver();

    Trip* matchTrip();
};


#endif //EX2_STATIONSTATION_H
