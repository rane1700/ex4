//
// Created by shani on 11/28/16.
//

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <array>
#include "Node.h"
#include "Trip.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
enum MaterialStatus{S, M, D, W};
class Driver {
private:
    Trip* trip;
    Node* location;
    int ID;
    int age;
    string materialStatus;
    int yearsOfExperience;
    double avgsatisfaction;
    int cabID;
    int steps;
    //vector<Node*> pass = NULL;
    enum material {S,M,D,W};

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & ID;
        ar & age;
        ar & materialStatus;
        ar & yearsOfExperience;
        ar & cabID;
    }

public:
    /**
     * constructor
     */
    Driver();
    /**
     * destructor
     */
    ~Driver();
    /**
     * constructor
     * @param ID1 - the driver's ID
     * @param age1 - the driver's age
     * @param materialStatus1 - the driver's material status
     * @param yearsOfExperience1 - the driver's years of experience
     * @param avgDestination1 - the driver's avg destination
     * @param cabID1 - the driver's cab ID
     */
    Driver(int ID1, int age1, char materialStatus1, int yearsOfExperience1, int cabID1);
    /**
     *
     * @return avg of satisfaction
     */
    double getAvgSatisfaction();
    /**
     *
     * @return driver ID
     */
    int getDriverID();
    /**
     *
     * @return current location of the driver
     */
    Node* getLocation();
    /**
     * sests the location to a new one
     * @param p - the new location
     */
    void setLocation(Node* p);
    void increaseSteps();
    int getSteps();
    void doOneStep();
    void addTrip(Trip* newTrip);
    void deletetrip();
    vector<Node*> getpass();
};


#endif //EX2_DRIVER_H