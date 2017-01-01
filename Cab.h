//
// Created by shani on 11/28/16.
//

#ifndef EX2_CAB_H
#define EX2_CAB_H
#include <vector>
//#include "Driver.h"
//#include "Passenger.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#define SPEED 1
class Cab {
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & color;
        ar & cabID;
        ar & numOfKMPassed;
        ar & taxiType;
        ar & manufacturer;
    }
protected:
    char color;
    int cabID;
    double numOfKMPassed;
    char manufacturer;
    double taarif;
    int taxiType;
public:

    /**
    * constractor
    * @param cabIDInput - the cab's ID
    * @param taxiTypeInput - the type of the cab
    * @param manufacturerInput - char of the cab's manufacturer first letter
    * @param colorInput - char of the cab's color first letter
    */
    Cab(int cabIDInput,int taxiTypeInput, char manufacturerInput, char colorInput);
/**
 * constructor
 */
    Cab();
/**
 * destructor
 */
    ~Cab();
/**
 *
 * @return false because this is a regular cab.
 */
    bool IsLuxuryCab();
/**
 *
 * @return cab ID
 */
    int getCabID();
/**
 *
 * @return KM passed
 */
    double getKMPassed();
/**
 *
 * @return the speed (1 because it is a regular cab)
 */
    int getSpeed();
};


#endif //EX2_CAB_H
