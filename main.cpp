#include <iostream>
#include "ParseFromString.h"
#include "MapCreator.h"
#include "StationInfo.h"

#define DRIVER 1
#define RIDE 2
#define VEHICLE 3
#define DRIVER_LOCATION 4
#define STRART_DRIVING 6
#define EXIT 7

using namespace std;
int main(int argc, char **argv) {
    string gridSize,obs,obsChain="";
    string input;
    int numObs,mission;
    int startX,startY;
    int endX,endY;
    int id;
    std::getline(cin, gridSize);
    cin>>numObs;
    if (numObs > 0) {
        for (int i = 0; i < numObs; i++) {
            cin >> obs;
            obsChain += obs;
            obsChain += " ";
        }
    }
StationInfo info= StationInfo();
    TaxiStation* tx = new TaxiStation();
    Trip* t;
    Driver d = Driver(12, 30, 1, 10, 122);
cin>>mission;
    while (1) {
            switch (mission) {
                case DRIVER: {
                    cin >> input;
                    tx->addDriver(info.getDriver(input));
                    break;
                }
                case RIDE: {
                    cin >> input;
                    t = info.getRide(input, startX, startY, endX, endY);
                    tx->addTrip(t,gridSize,numObs,obsChain);
                    break;
                }
                case VEHICLE: {
                    cin >> input;
                    tx->addCab(info.getVehicle(input));
                    break;
                }
                case DRIVER_LOCATION: {
                   cin>>id;
                    tx->getDriverLocation(id);
                    break;
                }
                case STRART_DRIVING: {
                    tx->startAll();
                    break;
                }
                case EXIT:
                {
                    delete(tx);
                    return 0;
                }
                case 9:
                {
                   // Driver d1 = *tx->getDriver(12);
                   // d1.doOneStep();
                    tx->start();
                }
            }

        cin>>mission;
    }
}
