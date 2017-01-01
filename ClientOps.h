//
// Created by ran on 29/12/16.
//

#ifndef SERVER_CLIENTOPS_H
#define SERVER_CLIENTOPS_H


#include "TaxiStation.h"
#include "StationInfo.h"
#include "Socket.h"

class ClientOps {
private:
    Socket* con;
    vector<Driver*>driverVec;
    vector<Trip*>tripVec;
    vector<Cab*>cabVec;
    StationInfo sInfo;
    int driverId;

public:
    ClientOps();
    ~ClientOps();
    Socket* getConnection();
    void updateDriver(char* buffer,int size);
    void addCab(char* buffer,int size);
    void addTrip(char* buffer,int size);
    void addDriver(string dInput);
    void sendDriver();
    Node* getLocation();
    int getDriverId();
    //std::string bufferToString(char* buffer,int bufferSize);
};


#endif //SERVER_CLIENTOPS_H
