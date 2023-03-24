#ifndef BIDS_INCLUDED
#define BIDS_INCLUDED
#include "memtrace.h"
#include <iostream>
#include "Utility.hpp"

// object to refer to a bid that may be auctioned and all its properties
class Bid{
    // the presumed value of the bid
    unsigned value;

    // the starting price of the bid
    unsigned start_price;

    // the name of the bid
    std::string name;

    // the type of the bid (eg: weapon, luxury product, etc...)
    Category type;

public:
    // default constructor. Should not be used explicitly!
    Bid() :value(0), start_price(0), type(invalid) {};

    // parameter constructor to create new Bid object. Expects: value, starting_price, name, type in this order.
    Bid(unsigned base_val, unsigned initial_p, std::string set_name, Category category) :value(base_val), start_price(initial_p), name(set_name), type(category) {}

    // returns value of the given bid
    unsigned getValue() {return value;}

    // returns the name of the given bid
    std::string getName() {return name;}

    // returns the start_price of the given bid
    unsigned getStart_price() {return start_price;}

    // returns the type of the given bid
    Category getType() {return type;}

    // writes out all properties of the bid in this format: " <name> Starting price: $<starting price> Estimated value <value>"
    void writeOut();

    // deconstructor. Should not be explicitly used!
    ~Bid(){};
};

// object to contain heterogeneous collection  of Bid objects
class Bid_List{

    // The heterogeneous collection
    Bid** bid_list;

    // The size of the collection
    size_t l_size;

    // Default constructor. Should not be used explicitly!
    Bid_List();

public:
    // parameter constructor to read bids from aruk.txt. Expects "aruk.txt" will throw exception otherwise
    Bid_List(std::string filename);

    // index operator to return a bid referred to by its index. expects ix: the index of the required archive in the list
    Bid& operator[](size_t ix) {return *bid_list[ix];}

    // returns the size of the heterogenic collection
    size_t getSize() {return l_size;}

    // calls all writeOut functions in the list
    void writeAll();

    // resets the heterogenic collection and sets the size to 0. Should only be used as part of deconstructor.
    void reset();

    // deconstructor to free up memory and destroy the object. Should not be explicitly used!
    inline ~Bid_List(){ reset(); }
};

#endif // BIDS_INCLUDED
