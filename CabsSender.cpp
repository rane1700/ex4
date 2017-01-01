//
// Created by ran on 27/12/16.
//


#include "CabsSender.h"
#include "Udp.h"

CabsSender::CabsSender(Cab* cabInput) {
    cab = cabInput;


}

void CabsSender::sendCab(Udp con) {

    char buffer[1024];
    std::ofstream ofs(buffer);
    {
        boost::archive::text_oarchive oa(ofs);
        oa << *cab;
        con.sendData(buffer);
    }

}
