#include <iostream>
#include "Buyers.h"
#include "Bids.h"
#include "Utility.hpp"

Buyer_List::Buyer_List(Name_List& first_n, Name_List& second_n, size_t buyer_number, unsigned min_money, unsigned max_money){
    l_size = buyer_number;
    try{
    list_of_buyers = new Buyer*[l_size];
    } catch (std::bad_alloc&){
        std::cout << "No memory when allocating Buyers list";
    }
    for (size_t i = 0; i < l_size; i++){
        try{
        list_of_buyers[i] = new Buyer (first_n,second_n,min_money,max_money);
        } catch (std::bad_alloc&){
            std::cout << "No memory when creating new buyer: " << i;
        }
    }
}

Buyer::Buyer(Name_List& first_n, Name_List& second_n, unsigned min_money, unsigned max_money) :Human(second_n, first_n), preference((Category)random_gen::capRandomI(1,8)), patience(def_val::def_patience), curr_money(random_gen::capRandomI(min_money,max_money)), count_down(def_val::def_cd) {
    offer = 0;
}

bool Buyer::behaviour(Bid interest, unsigned curr_highest){
    bool decision = false;
    if (count_down == 0) patience = 0;

    if(patience != 0 && curr_money > curr_highest && curr_highest != offer){
        if (curr_highest >= interest.getValue()){
            if (preference == interest.getType()){
                decision = random_gen::randomI(patience) > def_val::decision_roll_High_Value_Interested;
            } else {
                decision = random_gen::randomI(patience) > def_val::decision_roll_High_Value_Uninterested;
            }
        } else {
            if (preference == interest.getType()){
                decision = random_gen::randomI(patience) > def_val::decision_roll_Low_Value_Interested;
            } else {
                decision = random_gen::randomI(patience) > def_val::decision_roll_Low_Value_Uninterested;
            }
        }


        if (decision){
            if (preference == interest.getType()){
                count_down = def_val::def_cd;
            } else {
                patience -= random_gen::capRandomI(def_val::max_patience_loss_Succ_Uninterested,def_val::min_patience_loss_Succ_Uninterested);
                count_down = def_val::def_cd;
            }
        } else {
            if (preference == interest.getType()){
                patience -= random_gen::capRandomI(def_val::min_patience_loss_Fail_Interested,def_val::max_patience_loss_Fail_Interested);
                count_down--;
            } else {
                patience -= random_gen::capRandomI(def_val::min_patience_loss_Fail_Uninterested,def_val::max_patience_loss_Fail_Uninterested);
                count_down--;
            }
        }
    }
    if (patience > def_val::def_patience) patience = 0;
    if (count_down > def_val::def_cd) count_down = 0;
    return decision;
}

void Buyer::makeOffer(Bid interest, unsigned curr_highest){
    offer = curr_highest + random_gen::capRandomI(interest.getStart_price()/def_val::offer_min_mod, interest.getValue()/def_val::offer_max_mod);
    if (curr_money < offer) offer = curr_money;
}

Buyer_List::~Buyer_List() {
   if (list_of_buyers) {
        for (size_t i = 0; i < l_size; i++) {
            delete list_of_buyers[i];
        }
        l_size = 0;
        delete[] list_of_buyers;
    }
}
