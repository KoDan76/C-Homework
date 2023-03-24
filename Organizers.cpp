#include <ostream>
#include <fstream>
#include "Organizers.h"


Organizer::Organizer(Name_List& first_n, Name_List& second_n, Bid& chosen_bid, size_t buyer_number, unsigned min_money, unsigned max_money) :Human(second_n, first_n), on_display(chosen_bid), buyers_list() {
    setHighest_offer(chosen_bid.getStart_price());
    buyers_list = new Buyer_List(first_n, second_n, buyer_number, min_money, max_money);
}

Buyer* Organizer::startAuction(){

    std::cout << titles::auction_start1 << getName() << std::endl;
    std::cout << on_display.getName() << titles::auction_start2 << on_display.getStart_price() << titles::auction_start3 << std::endl;

    Buyer* lead = nullptr;
    highest_offer = on_display.getStart_price();
    bool undecided = true;

    bool biddin_begun = false;
    int zero_offers = 0;
    int no_new_offers = 0;

    while (undecided){
        no_new_offers += 1;
        for(size_t i = 0; i < buyers_list->getSize(); i++){


            if ((*buyers_list)[i]->behaviour(on_display, highest_offer)){

                (*buyers_list)[i]->makeOffer(on_display, highest_offer);
                highest_offer = (*buyers_list)[i]->getOffer();
                std::cout << (*buyers_list)[i]->getName() << " offers $" << (*buyers_list)[i]->getOffer() << std::endl;

                lead = (*buyers_list)[i];

                no_new_offers = 0;
                biddin_begun = true;
            }
        }
        (no_new_offers > 0 && !biddin_begun) ? zero_offers++ : zero_offers = 0;

        if (zero_offers == 1) {
            std::cout << titles::lower_price << std::endl;
            highest_offer = on_display.getStart_price()/2;
            no_new_offers = 0;
        } else {
            if (zero_offers == 2){
                std::cout << titles::reset_price << std::endl;
                highest_offer = 2;
                no_new_offers = 0;
            } else {
                switch (no_new_offers){
                case 1: std::cout << highest_offer << titles::call_first;
                    break;
                case 2: std::cout << highest_offer << titles::call_second;
                    break;
                case 3: std::cout << highest_offer << titles::call_third;
                        undecided = false;
                    break;
                default:
                    if (random_gen::randomI(6) >= def_val::flavor_text_roll_criteria) std::cout << titles::intense_AF << std::endl;
                }
            }
        }
    }
    return lead;
}

void Organizer::writeWinner(){
    Buyer* to_write = startAuction();
    std::cout << std::endl << to_write->getName() << " takes " << on_display.getName() << " for $" << highest_offer << std::endl;

    std::ofstream write_to;

    write_to.open(titles::txt_archives, std::ios::app);
    write_to << to_write->getName() << std::endl << on_display.getName() << std::endl << highest_offer << std::endl;
    write_to.close();
}



