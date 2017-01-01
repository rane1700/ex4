//
// Created by ran on 01/01/17.
//

#ifndef SERVER_DRIVERDATA_H
#define SERVER_DRIVERDATA_H


#include "Node.h"

class DriverData {
private:
    int driverId;
    Node* location;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & driverId;
        ar & location;
    }
    public:
    DriverData(int id,Node* loc);
    ~DriverData();
    int getDriverId();
    Node* getLocation();
};


#endif //SERVER_DRIVERDATA_H
