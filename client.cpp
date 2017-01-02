//
// Created by yanaiela on 12/10/16.
//
#include <iostream>

#define STOP_ADVANCE '7'
#include "Udp.h"
#include "TaxiStation.h"
#include "StationInfo.h"
#include "ClientOps.h"
#include <unistd.h>



using namespace std;

int main(int argc, char *argv[]) {
    ClientOps co = ClientOps();

    string input;

    cin >> input;

    co.addDriver(input);
    co.sendDriver();

    char missionNum[1024];///
    char buffer[1024];
    co.getConnection()->reciveData(missionNum, sizeof(missionNum));
    while (true) {
        switch(missionNum[0]) {
            case '2':
            {

                co.addTrip(buffer,sizeof(buffer));
                break;
            }
            case '3':
            {

                co.addCab(buffer,sizeof(buffer));
                break;

            }
            case '7':
            {
                co.~ClientOps();
                return 0;

            }
            case '9':
            {
                co.updateDriver(buffer,sizeof(buffer));
                break;
            }

        }
        co.getConnection()->reciveData(buffer, sizeof(buffer));
    }
    co.~ClientOps();
    return 0;
}