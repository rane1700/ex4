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

    char buffer[1024];
    co.getConnection()->reciveData(buffer, sizeof(buffer));
    while (buffer[0] != STOP_ADVANCE) {
        co.updateDriver(buffer,sizeof(buffer));
        co.getConnection()->reciveData(buffer, sizeof(buffer));
    }
    co.~ClientOps();
    return 0;
}