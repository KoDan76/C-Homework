#ifndef ORGANIZERS_INCLUDED
#define ORGANIZERS_INCLUDED
#include "memtrace.h"
#include "Buyers.h"
#include "Bids.h"
#include "HumansAndNames.h"

// class to refer to the organizer of the auction. The organizer's task is to conduct an auction and call the winner at the end.
// Achieves this by calling the different functions of the members in the contained Buyer_List.
class Organizer :public Human{

    // the bid on display and to be auctioned away.
    Bid& on_display;
    // the current highest offer for the bid on display.
    unsigned highest_offer;
    // A heterogenic collection of the buyers in the auction
    Buyer_List* buyers_list;
    // Default constructor, should not be called explicitly!
    Organizer();
    // complex function to conduct the auction.
    // Buyers make their offers for the bid in order according to their behavior.
    // If there is no offer for the product the price will be first halved, then set to zero. After three turns of no new offers, the winner is called. And the bid is sold
    // Returns Buyer* <the winner of the auction> for writeWinner()
    Buyer* startAuction();

public:
    // Parameter constructor to create a new Organizer and the contained buyers_list.
    // Expects the list of first names, the list of second names, the chosen bid, the number of buyer, the minimum and the maximum funds of a buyer, in this order.
    Organizer(Name_List& first_n, Name_List& second_n, Bid& chosen_bid, size_t buyer_number, unsigned min_money, unsigned max_money);

    // returns the current highest offer for the bid on display
    unsigned getHighest_offer() {return this->highest_offer;}

    // sets the highest offer for the bid on display
    void setHighest_offer( unsigned new_offer ) {this->highest_offer = new_offer;}

    // calls startAuction() then writes the winner into the screen and into archives.txt
    void writeWinner();

    // destructor to free up memory and delete the contained list. Should not be called explicitly.
    ~Organizer(){ delete buyers_list;}
};

#endif // ORGANIZERS_INCLUDED
