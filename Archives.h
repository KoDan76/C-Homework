#ifndef ARCHIVES_INCLUDED
#define ARCHIVES_INCLUDED
#include "memtrace.h"
#include <string>

//class to contain a single record of a past auction
class Archive {

    // the name of the winner of the auction
    std::string buyer_name;
    // the name of the bid that was auction
    std::string bid_name;
    // the price for which the bid was auctioned off
    unsigned buying_price;

public:
    // default constructor. Should not be explicitly used.
    Archive();

    //parameter constructor Expects buyer_name, bid_name, buying_price in this order.
    Archive(std::string bu_name, std::string bi_name, unsigned price) :buyer_name(bu_name), bid_name(bi_name), buying_price(price) {};

    // Writes out all parameters of the Archive in this format: "<Buyer name> bought <price name> for <buying_price>"
    void writeOut();
};

// Dynamic heterogeneous collection container to read in archives from archives.txt and write out their parameters.
class Archive_List {
    // size of the archive list
    size_t l_size;

    // The heterogeneous collection
    Archive** archives;

    // default constructor, should not be explicitly used
    Archive_List(){l_size = 0; archives = nullptr;};

public:

    //parameter constructor to read in archives from given file name. Expects "archives.txt". Will throw exception otherwise
    Archive_List(std::string filename);

    // index operator to return an archive referred to by by it's index. expects ix: the index of the required archive in the list
    Archive* operator[](size_t ix) { return archives[ix]; }

    // adds the expected new archive to the list.
    void add(Archive* new_item);

    // Calls writeOut() for each member of the collection
    void writeAll();

    // returns the size of the collection
    size_t getSize() { return l_size; }

    // destructor. Frees up memory and resets the archive list. Should not be called explicitly!
    ~Archive_List();
};

// creates and writes out archives. Serves for the updatability of the archives without the need to exit the program
void createArchives();

#endif // ARCHIVES_INCLUDED
