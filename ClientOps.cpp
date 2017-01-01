//
// Created by ran on 29/12/16.
//

#include "ClientOps.h"
#include "Udp.h"
#include "DriverData.h"

ClientOps::ClientOps() {
    sInfo = StationInfo();
    con = new Udp(0,1111);
    con->initialize();
}
ClientOps::~ClientOps() {
    for (int i=0;i<driverVec.size();i++) {
        delete driverVec[i];
    }

    con->~Socket();
}
Socket* ClientOps::getConnection() {
    return con;
}
void ClientOps::updateDriver(char *buffer,int size) {
    std::string serial_str (buffer, size);
    DriverData* dData;
    //unserialize the vehicle
    boost::iostreams::basic_array_source<char> device2((char *) serial_str.c_str(), (char *) serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia(s2);
    ia >> dData;
    for (int i=0;i<driverVec.size();i++){
        if (driverVec[i]->getDriverID() == dData->getDriverId()) {
            driverVec[i]->setLocation(dData->getLocation());
            //if (driverVec[i].isDone() == true)
            //driverVec[i].setTrip(tripVec[0])
            //tripVec.erase(tripVec.begin())
        }
    }
}
void ClientOps::addTrip(char *buffer, int size) {
    string serial_str (buffer, size);
    Trip* trip;

    boost::iostreams::basic_array_source<char> device3((char *) serial_str.c_str(), (char *) serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
    boost::archive::binary_iarchive ia(s3);
    ia >> trip;
    tripVec.push_back(trip);
}
void ClientOps::addCab(char* buffer,int size) {
    std::string serial_str (buffer, size);
    Cab* cab;

    boost::iostreams::basic_array_source<char> device2((char *) serial_str.c_str(), (char *) serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia(s2);
    ia >> cab;

    for(int i=0;i<driverVec.size();i++){
        //if (driverVec[i].getDriverId == cab.getDriverId()
        //driverVec[i].setCab(cab)
    }

}
void ClientOps::addDriver(string dInput) {
    Driver* d = sInfo.getDriver(dInput);
    driverVec.push_back(d);
}

void ClientOps::sendDriver() {
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverVec[0];
    s.flush();
    con->sendData(serial_str);
}

std::string bufferToString(char* buffer,int bufferSize){
    std::string ret(buffer,bufferSize);
    return ret;
}