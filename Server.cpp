//
// Created by ran on 27/12/16.
//
#include "Server.h"

Server::Server() {
    soc = new Udp(1,1111);
    int bla = soc->initialize();
    cout<<bla<<endl;
    flag = false;

}
void Server::setDriver() {
    char buffer[1024];
    char* charId;
    soc->reciveData(buffer,sizeof(buffer));
    charId = buffer;
    driverId = atoi(charId);

}
void Server::sendTrip() {
    //serialize
        Trip *trip = serverTrips[0];
        serverTrips.pop_back();
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << trip;
        s.flush();
        soc->sendData(serial_str);


}
void Server::sendCab() {
    if (serverCabs.size() > 0) {
        Cab* cab = serverCabs[0];
        serverCabs.pop_back();
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << cab;
        s.flush();
        flag = true;
    }
}
void Server::moveOn() {
 //   soc->sendData("9");
   // sendCab();
    sendTrip();
    if (location == goalPoint) {
        delete (goalPoint);
        goalPoint = new PointHistory(PointBase(serverTrips[0]->getEndX(),serverTrips[0]->getEndY()));
        setLocation();
    }
}
void Server::setLocation() {
    char buffer[1024];
    soc->reciveData(buffer, sizeof(buffer));
    int xAxes,yAxes;
    char* string1 = buffer;
    ParseFromString p = ParseFromString(buffer);
    p.parse(',',&xAxes,&yAxes);
    PointHistory ph = PointHistory(PointBase(xAxes,yAxes));
    location = &ph;
}
void Server::getDriver() {
    char buffer[1024];
    soc->reciveData(buffer, sizeof(buffer));
}
void Server::getLocation(int id) {
    soc->sendData(""+id);

}
void Server::printLocation() {
    cout<<*location<<endl;
}
void Server::exit(){
    soc->~Socket();
}
bool Server::isDriverSet(){
    return flag;
}
void Server::addTrip(Trip* t) {
    serverTrips.push_back(t);
    if (serverTrips.size() == 1) {
        goalPoint = new PointHistory(PointBase(t->getEndX(),t->getEndY()));
    }
}
void Server::addCab(Cab* c){
    serverCabs.push_back(c);
}