
#ifndef EX1_GRID_H
#define EX1_GRID_H
#define MAX_SIZE 10
#include "Bfs.h"
#include "PointBase.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
/*#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>*/
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/export.hpp>

class Grid: public Map {
private:
    int length;
    int width;
    Bfs gridPath;
    PointHistory start;
    PointHistory goal;
    Node* matrix[MAX_SIZE][MAX_SIZE];

    vector<Node*>obstacles;
    Node* currentP;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & boost::serialization::base_object<Map>(*this);
        ar & length;
        ar & width;
        //ar & gridPath;
        ar & start;
        ar & goal;
        ar & matrix;
        ar & obstacles;
        ar & currentP;

    }
public:
    /**
     * destructor
     */
    ~Grid();
    Grid();
    /**
      * constractor
      * @param gridLength - the length
      * @param gridWidth - the width
      * @param gridGoalX  - the x of the goal point
      * @param gridGoalY - the y of the goal point
      * @param gridStartx - the x of the start point
      * @param gridStartY - the y of the start point
       * @param obs - map of obsticals
      */
    Grid(int  gridLength, int  gridWidth, int gridGoalX, int gridGoalY, int gridStartx, int gridStartY,vector<Node*>obs);
    /**
     * gets the path from a start point to a goal point
     * @param speed - the speed of the cab (1 or 2)
     * @return false if there is no path to the goal point, else return true.
     */
    Node* run(int speed);
    /**
    * prints the shortest path from the start point to the dest point
    */
    void print();
    /**
   *
   * @param xAxes - the x axes
   * @param yAxes - the y axes
   * @param neighbors - empty vector
   * @return true if there are any neighbors, and false if not.
   */
    bool getNeighbors(int xAxes, int yAxes, vector<Node *> *neighbors,int speed);
    /**
     * get current location in grid
     * @return Node object
     */
    Node* getCurrent();

};

#endif //EX1_PATH_H