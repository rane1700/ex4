//
// Created by ran on 01/01/17.
//

#include "DriverData.h"
DriverData::DriverData(int id,Node* loc) {
    driverId = id;
    location = loc;
}
DriverData::~DriverData(){
    delete location;
}
int DriverData::getDriverId() {
    return driverId;
}
Node* DriverData::getLocation() {
    return location;
}