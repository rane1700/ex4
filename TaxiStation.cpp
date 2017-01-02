//
// Created by shani on 11/28/16.
//

#include "TaxiStation.h"
#include "MapCreator.h"

/**
 * Empty constructor
 */
TaxiStation::TaxiStation(){
    server = Server();
}
/**
 * Destructor to delete all the vectors
 */
TaxiStation::~TaxiStation() {
    for (int i=0;i<drivers.size();i++) {
        delete(drivers[i]);
    }
    for (int i=0;i<cabs.size();i++) {
        delete(cabs[i]);
    }
   for (int i=0;i<trips.size();i++){
        delete(trips[i]);
    }
}
/**
 * add driver to driver's vector
 * @param driver Driver object to be added
 */
void TaxiStation::addDriver(){
    drivers.push_back(server.setDriver());

}
/**
 * Add Cab to the cab's vector
 * @param cab Cab object to be added
 */
void TaxiStation::addCab(Cab* cab) {
    server.sendCab(cab);
    cabs.push_back(cab);

}
/**
 * add Trip to trip's vector
 * @param trip Trip to be added
 * @param gridSize size of grid for creation of mao
 * @param numObs number of obstacles expected in map
 * @param obsChain string of obstacles
 */
void TaxiStation::addTrip(Trip* trip) {
    /**
     * Use the MapCreator parser class to turn string inputs into
     * a Map object
     */
    MapCreator creator = MapCreator(trip->getGridSize(), trip->getEndX(),
                                    trip->getEndY(), trip->getStartX(), trip->getStartY(),
                                    trip->getNumObs(), trip->getObsChain());
    Map* m = creator.getMap();
    //drivers[0]->addTrip(trip);
    //Set map in Trip class
    trip->setMap(m);
    //drivers[0]->addTrip(trip);
    server.sendTrip(trip);
    trips.push_back(trip);

}
/**
 * Get Driver object by id
 * @param id input
 * @return Driver object
 */
Driver* TaxiStation::getDriverByID(int id) {
    std::vector<Driver*>::iterator it;
    for (it = drivers.begin(); it != drivers.end(); it++) {
        if ((*it)->getDriverID()==id) {
            return (*it);
        }
    }
}
/**
 * Get Cab object by id
 * @param id input
 * @return Cab object
 */
Cab* TaxiStation::getCab(int id) {
    std::vector<Cab*>::iterator it;
    for (it = cabs.begin(); it != cabs.end(); it++) {
        if ((*it)->getCabID()==id) {
            return (*it);
        }
    }
}
/**
 * prints the driver current location by id given
 * @param id input
 */
void TaxiStation::getDriverLocation(int id) {
    /**
     * location is saved uniqely in driver object
     */
    if (trips.size() == 0) {
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers[i]->getDriverID() == id) {
                cout << (*drivers[i]->getLocation()) << endl;
                return;
            }
        }
    } else {
        /**
         * Extract location from the appropriate trip from trip
         */
        for (int i = 0; i < trips.size(); i++) {
            if (drivers[i]->getDriverID() == id) {
                cout << *trips[i]->getMapCurrent() << endl;
                return;
            }
        }
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers[i]->getDriverID() == id) {
                cout << (*drivers[i]->getLocation()) << endl;
                return;
            }
        }
    }
}
/**
 * Get Trip object by id
 * @param id input
 * @return Trip object
 */
Trip* TaxiStation::getTrip(int id) {
    for (int i = 0; i < trips.size(); i++) {
        if (trips[i]->getRideID() == id) {
            return trips[i];
        }
    }
}
/**
 * Start all trips added
 */
void TaxiStation::startAll() {
    int id;
    Driver* d;
    for (int i=0;i<drivers.size();i++) {
        for (int j=0;j<trips.size();j++) {
            //find if any driver arrived to desired place erlier
            d = findDriverAlreadyArrived(trips[j]->getStartX(),trips[j]->getStartY(),drivers[i]->getDriverID());
            if (d == NULL) {
                if (drivers[i]->getLocation()->getX() == trips[j]->getStartX() &&
                    drivers[i]->getLocation()->getY() == trips[j]->getStartY()) {
                    trips[j]->getNext(1);
                    //make a copy of trip current location after the ride is ended
                    p = trips[j]->getMapCurrent()->clone();
                    drivers[i]->setLocation(p);
                    drivers[i]->increaseSteps();
                    id = findTripNumInVector(trips[j]->getRideID());
                    delete (trips[j]);
                    //delete the trip from vector
                    trips.erase(trips.begin() + id);
                }
            } else {
                //A driver Arrived before
                trips[j]->getNext(1);
                //make a copy of trip current location after the ride is ended
                p = trips[j]->getMapCurrent()->clone();
                d->setLocation(p);
                d->increaseSteps();
                id = findTripNumInVector(trips[j]->getRideID());
                delete (trips[j]);
                //delete the trip from vector
                trips.erase(trips.begin() + id);
            }
            if (trips.size() == 0) {
                return;
            }
        }
    }
}
/**
 * Look for a driver which came for wanted spot before you
 * @param startX start of trip X
 * @param startY start of trip Y
 * @param id of driver we check about
 * @return NULL if no one was here before , Driver object else
 */
Driver* TaxiStation::findDriverAlreadyArrived(int startX,int startY,int id) {
    if (startX == 0 && startY == 0) {
        return NULL;
    }
    int min = getDriverByID(id)->getSteps();
    int idMin = getDriverByID(id)->getDriverID();
    //Check which driver had done the least steps to desired point
    for (int i=0;i<drivers.size();i++) {
        if (drivers[i]->getLocation()->getX() == startX && drivers[i]->getLocation()->getY() ==startY) {
            if (drivers[i]->getSteps()<min) {
                idMin = drivers[i]->getDriverID();
                min = drivers[i]->getSteps();
            }
        }
    }
    if (idMin != id) {
        return getDriverByID(idMin);
    } else {
        return NULL;
    }
}
/**
 * Method to find where the trip is located in the vector.
 * @param tripId id of trip
 * @return position of trip
 */
int TaxiStation::findTripNumInVector(int tripId) {
    for (int i=0;i<trips.size();i++) {
        if (trips[i]->getRideID() == tripId) {
            return i;
        }
    }
}

void TaxiStation::start() {
    if (drivers[0]->istripDone() == true) {
        drivers[0]->addTrip(matchTrip());
        drivers[0]->setTripDone(false);
        drivers[0]->getTrip()->createPass(1);
        clock.incTime();
        return;
    }
    //else if(drivers[0]->getTrip()->isDone() == false) {
    if (drivers[0]->getTrip()->getTimeOfStart() <= clock.getTime()) {
        /*
        if(drivers[0]->getTrip()->getpass().size() == 0){
            drivers[0]->getTrip()->createPass(1);
        }
        else
         */drivers[0]->doOneStep();
        if(drivers[0]->getTrip()->isDone() == true){
        int x = findTripNumInVector(drivers[0]->getTrip()->getRideID());
        trips.erase(trips.begin() + x);
            delete(drivers[0]->getTrip());
            drivers[0]->setTrip(NULL);
            drivers[0]->setLocation(NULL);
            drivers[0]->setTripDone(true);

            cout<<"end of trip"<<endl;
    }
    //} else{
        //drivers[0]->deletetrip();

    }
    clock.incTime();
}

Driver* TaxiStation::getDriver() { return drivers[0];}

Trip* TaxiStation:: matchTrip(){
    Trip* maxTrip = trips[0];
    for(int i = 0; i < trips.size(); i++){
        if(maxTrip->getTimeOfStart() > trips.at(i)->getTimeOfStart()){
            maxTrip = trips.at(i);
        }
    }
    return maxTrip;
}
Server TaxiStation::getConn() {
    return server;
}