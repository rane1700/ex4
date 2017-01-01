//
// Created by ran on 27/12/16.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H
#include <boost/serialization/export.hpp>
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
#include "Udp.h"
#include "Cab.h"
#include "Trip.h"
#include "ParseFromString.h"
#include "PointHistory.h"





class Server {
private:
    int driverId;
    Socket* soc;
    Node* location;
    bool flag;
    vector<Trip*>serverTrips;
    vector<Cab*>serverCabs;
    Node* goalPoint;
public:
    Server();
    void setDriver();
    void sendTrip();
    void sendCab();
    void moveOn();
    void addTrip(Trip* t);
    void addCab(Cab* c);
    void getDriver();
    void setLocation();
    void getLocation(int id);
    void printLocation();
    bool isDriverSet();
    void exit();
};
#endif //EX3_SERVER_H
