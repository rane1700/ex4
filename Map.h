//
// Created by shani on 11/28/16.
//

#ifndef EX2_MAP_H
#define EX2_MAP_H

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include "Node.h"
//#include "PointHistory.h"

class Map {
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & , unsigned ) {}
public:
    /**
     * constructor
     */
    Map();
    /**
     * destructor
     */
    virtual ~Map();
    /**
     *
     * gets neighbors of certian points according to map
     */
    /**
     *
     * gets neighbors of certian points according to map
     */
    virtual bool getNeighbors();
    /**
     *
     * @return current point
     */
    virtual Node* getCurrent();
    /**
     * gets the path from a start point to a goal point
     * @param speed - the speed of the cab (1 or 2)
     * @return false if there is no path to the goal point, else return true.
     */
    virtual Node* run(int speed);
    /**
     * prints map
     */
    virtual void print();

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Map);
#endif //EX2_MAP_H
