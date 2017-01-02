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
Driver* Server::setDriver() {
    char buffer[1024];
    soc->reciveData(buffer,sizeof(buffer));
    string serial_str (buffer,sizeof(buffer));
    Driver* driver;

    boost::iostreams::basic_array_source<char> device3((char *) serial_str.c_str(), (char *) serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
    boost::archive::binary_iarchive ia(s3);
    ia >> driver;
    return driver;


}
void Server::sendTrip(Trip* trip) {
    //serialize

        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << trip;
        s.flush();
        soc->sendData(serial_str);


}
void Server::sendCab(Cab* cab) {

        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << cab;
        s.flush();
        soc->sendData(serial_str);
}
void Server::moveOn(Node* loc) {
    soc->sendData("9");

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << loc;
    s.flush();
    soc->sendData(serial_str);
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
Socket* Server::getConnection() {
    return soc;
}