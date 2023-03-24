#ifndef HUMANSANDNAMES_INCLUDED
#define HUMANSANDNAMES_INCLUDED
#include "memtrace.h"
#include "Bids.h"
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

// class to contain array of names (std::string). Used to read in and store first and second names.
class Name_List{

    // the size of the array
    size_t l_size;

    // the array to contain the names
    std::string* all_names;

    // default constructor, should not be used explicitly!
    Name_List();

public:
    // parameter constructor to read a list of names from file. Expects surnames.txt or firstnames.txt, will throw exception otherwise
    Name_List(std::string filename);

    // returns the size of the array
    size_t getSize() { return l_size;}

    // sets the size of the array expects size_t l_size
    void setSize(size_t new_size) {l_size = new_size;}

    // index operator to return the referred member of the array. Expects size_t <index of the member>
    std::string operator[](size_t ix) {return all_names[ix];}

    // default destructor to free up memory, should not be called explicitly!
    ~Name_List();
};

// class to refer to a specific Person in the action. Parent of Organizer and Buyer. Mainly responsible for Name Generation
class Human{

    // the person's name
    std::string name;

    // generates names by choosing a surnames and first name from the expected lists at random. Expects: Name_List& list of surnames and Name_List& list of firstnames in this order.
    void GenNames(Name_List& surnames, Name_List& firstnames);

    // Default constructor. Should not be used explicitly!
    Human();

public:

    // Parameter constructor. Expects: Name_List& list of surnames and Name_List& list of firstnames in this order.
    Human(Name_List& surnames, Name_List& firstnames);

    // returns the name of the person
    std::string getName() {return name;};

    // destructor. Should not be used explicitly!
    virtual ~Human(){};
};

#endif // HUMANSANDNAMES_INCLUDED
