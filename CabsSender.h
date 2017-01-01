//
// Created by ran on 27/12/16.
//

#ifndef EX3_DRIVERSCONTAINER_H
#define EX3_DRIVERSCONTAINER_H

#include "Udp.h"
#include <unistd.h>
#include <boost/archive/text_oarchive.hpp>
#include "boost/archive/text_iarchive.hpp"
#include <fstream>
#include "TaxiStation.h"

class CabsSender {
private:
    Cab* cab;

public:
    CabsSender(Cab* cabInput);
    void sendCab(Udp con);

};



#endif //EX3_DRIVERSCONTAINER_H
