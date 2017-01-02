#include <iostream>
#include "ParseFromString.h"
#include "MapCreator.h"
#include "StationInfo.h"
#include "Udp.h"
#include "CabsSender.h"
#include "Server.h"
#include <unistd.h>


#define RECIEVE_DRIVER 1
#define RIDE 2
#define VEHICLE 3
#define DRIVER_LOCATION 4
#define STRART_DRIVING 6
#define EXIT 7
using namespace std;
int main(int argc, char **argv) {


    /*Node* n = new PointBase(0,0);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << n;
    s.flush();

    cout << serial_str << endl;
    Node* a;
//    string txt =
//    StandardCab *trip2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> a;

//    cout << *trip2;
//    MainFlow mainFlow;
//    mainFlow.getNext();

    //  delete trip2;
    return 0;*/

    Server *server = new Server();
    string gridSize, obs, obsChain = "";
    string input;
    int numObs, mission;
    int startX, startY;
    int endX, endY;
    int id;
    int numDrivers;
    std::getline(cin, gridSize);
    cin >> numObs;
    if (numObs > 0) {
        for (int i = 0; i < numObs; i++) {
            cin >> obs;
            obsChain += obs;
            obsChain += " ";
        }
    }
    StationInfo info = StationInfo();
    TaxiStation *tx = new TaxiStation();
    Trip *t;
    Cab* cab;
    Driver* driver = new Driver(123, 30, 'h', 10, 1233);
    tx->addDriver(driver);
    cin >> mission;
    while (1) {
        switch (mission) {
            case RECIEVE_DRIVER: {
                cin >> numDrivers;
                server->setDriver();
                //tx->addDriver(info.getDriver(input));
                break;
            }
            case RIDE: {
                cin >> input;
                t = info.getRide(input, startX, startY, endX, endY);
                t->setGridSize(gridSize);
                t->setNumObs(numObs);
                t->setObsChain(obsChain);
                //server->addTrip(t);
                tx->addTrip(t);
                //server->sendTrip(t);
                break;
            }
            case VEHICLE: {
                cin >> input;
                cab = info.getVehicle(input);
                server->addCab(cab);
                //server->sendCab(info.getVehicle(input));
                tx->addCab(info.getVehicle(input));
                //server->sendCab(cab);
                break;
            }
            case DRIVER_LOCATION: {
                cin >> id;
                tx->getDriverLocation(id);
                break;
            }
            case STRART_DRIVING: {
                tx->startAll();
                break;
            }
            case 9: {
                //server->moveOn();
                tx->start();
                //server->sendLocation(driver->getLocation());
                break;
            }
            case EXIT: {
                delete (tx);
                return 0;
            }
        }

        cin >> mission;
    }
}

