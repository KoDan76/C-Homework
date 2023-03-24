#ifndef BUYERS_INCLUDED
#define BUYERS_INCLUDED
#include "memtrace.h"
#include "HumansAndNames.h"
#include "Utility.hpp"

// class to refer to a buyer of the auction.
// Buyers have names, money, preference as to what types of producsts they want to buy.
// Patience and a count_down meter that serve to determine how long they wish to participate in the auction.
// And "offer" to count the money they offer for a bid
class Buyer :public Human{

    // A buyer's preference as to what types of producsts they want to buy.
    Category preference;
    // Under a certain patience value the buyer will quit the auction.
    unsigned patience;
    // the current amount of fund the buyer may spend on the auction. If this value is lower then the bid, they can't make a new offer.
    unsigned curr_money;
    // The offer the buyer made most recently
    unsigned offer;
    // serves mainly for easier handling by the organizer. When the count_down hits 0 the buyer will not make a new offer.
    unsigned count_down;
    // Default constructor. Should not be used explicitly!
    Buyer();

public:
    // parameter constructor to create new Buyer object.
    //Expects: list of first names, list of second names  the maximal amount of money and the minimal amount of money a buyer can have. In this order.
    Buyer(Name_List& first_n, Name_List& second_n, unsigned max_money, unsigned min_money);

    // returns the patience of the buyer
    unsigned getPatience() {return this-> patience ;}

    // sets the patience of the buyer. Expects the new value in unsigned
    void setPatience(unsigned new_patience) { this->patience = new_patience; }

    // returns the amount of money the buyer has left
    unsigned getCurr_Money() { return this->curr_money;}

    // sets the amount of money the buyer has. Excpects the new value in unsigned
    void setCurr_money(unsigned curr_money);

    // A simple "AI" to determine if the buyer wishes to remain in the auction. Uses random number generation.
    // Negatively affected by low patience and a lack of preference for the bid that is being auction.
    // Expects: The bid that is being auctioned, and the current highest offer for it, in this order.
    bool behaviour(Bid interest, unsigned curr_highest);

    // sets the buyer's current offer based on the decision of their behaviour.
    // In practice this increases the highest offer by a random amount, that is affected by the value of the bid on auction.
    // Expects: The bid that is being auctioned, and the current highest offer for it, in this order.
    void makeOffer(Bid interest, unsigned curr_highest);

    // returns the current offer of the buyer.
    unsigned getOffer() {return this->offer;}

    // returns the preference for any type of product of the buyer.
    Category getPreference() {return this->preference;}

    // destructor, should not be called explicitly!
    ~Buyer (){};
};

// Class to contain a heterogeneous collection of buyers
class Buyer_List{

    // the size of the collection
    size_t l_size;
    // The heterogeneous collection of buyers
    Buyer** list_of_buyers;

public:
    // default constructor, should not be called explicitly!
    Buyer_List() :l_size(0) { list_of_buyers = nullptr; }

    // parameter constructor to create a new heterogeneous collection.
    // Expects: The list of first names, The list of second names. The number of possible buyers. The minimal, and maximal amount of money they can have. In this order.
    Buyer_List(Name_List& first_n,Name_List& second_n,size_t buyer_number,unsigned min_money,unsigned max_money);

    // returns size of the collection
    size_t getSize() {return l_size;}

    // sets the size of the collection. expects new value in size_t
    void setSize(size_t new_size) {l_size = new_size;}

    // index operator to return a member of the collection reffered to it by its index.
    Buyer* operator[](size_t ix) {return list_of_buyers[ix];}

    // destructor. Should not be called explicitly
    ~Buyer_List();
};

#endif // BUYERS_INCLUDED





