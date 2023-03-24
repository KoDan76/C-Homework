#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED
#include "memtrace.h"
#include <cstdlib>
#include <string>


enum Category {
    invalid = 0,// for warnings.
    luxury = 1, // luxury products, such as statuette or animal skin
    cloth = 2,  // for clothing
    furniture = 3,
    weapon = 4,
    jewel = 5,
    picture = 6,
    music = 7,  // for instruments
    vehicle = 8
};

namespace random_gen {
    // Returns random unsigned int with minimum of 0 to maximum
    inline unsigned randomI(int maximum){
        maximum = maximum + 1;
        return rand()%maximum;
    }

    // Returns random size_t int with minimum of 0 to maximum
    inline size_t randomUI(size_t maximum){
        maximum = maximum + 1;
        return rand()%maximum;
    }

    // Returns random unsigned int with minimum of low_cap to high_cap
    inline unsigned capRandomI(int low_cap, int high_cap){
        high_cap ++;
        return rand()%(high_cap-low_cap) + low_cap;
    }

    // Returns random size_t int with minimum of low_cap to high_cap
    inline size_t capRandomUI(size_t low_cap, size_t high_cap){
        high_cap++;
        return rand()%(high_cap-low_cap) + low_cap;
    }
}

// From here all constants are for easier recognition and editability.
namespace titles{
    // menu titles
    const std::string greeting = "Welcome to Koppa Daniel's bidding simulator!\n";
    const std::string main_menu = "\nMain Menu: Please type a command!\n  n - start new simulation\n  a - access bidding archives\n  q - quit the application\n  t - testing mode";
    const std::string invalid_command = "Invalid command. Please try something else (h-help)";
    const std::string chose_scenario = "Would you like to load the (d)efault scenario or create a (c)ustom one?\nd or c: ";
    const std::string loading = "Loading default scenario: \n";
    const std::string integrity_check = "File integrity checked.\n";

    const std::string chose_bid = "Chose a bid from the above list to auction by typing its index. (0 for random): ";
    const std::string chose_b_num = "Specify the number of buyers present in the action: ";
    const std::string chose_max_funds = "Specify the maximum funds of bidders in $: ";
    const std::string chose_min_funds = "Specify the minimal funds of bidders in $: ";
    const std::string generate_scenario = "GENERATING CUSTOM SCENARIO:\n\n";

    // function titles
    const std::string archive_title = "All items sold so far in the auction house:\n";
    const std::string auction_start1 = "\nWelcome, ladies and gentleman! My name is ";
    const std::string auction_start2 = " is today's bid for the low low starting price of: $";
    const std::string auction_start3 = ". Without further adu I start the auction!";
    const std::string lower_price = ".\n.\n.\nHow unfortunate, seems no one is interested. Let's start again from half price!";
    const std::string reset_price = ".\n.\n.\nStill? No one seems to be interested. Well, then starting from $2, highest offer wins!";
    const std::string call_first = " first... \n";
    const std::string call_second = " second... \n";
    const std::string call_third = " third! The bid is SOLD!\n";
    const std::string intense_AF = "\nI can see some very intense bidding, here! Can I see it go higher?\n";

    const std::string out_start_price = " Starting price: $";
    const std::string out_value = " Estimated value: $";

    // file names
    const std::string txt_firstnames = "firstnames.txt";
    const std::string txt_secondnames = "surnames.txt";
    const std::string txt_archives = "archives.txt";
    const std::string txt_bids = "aruk.txt";
}

namespace def_val{
    const int def_mem_test = 100;

    // initializers
    const unsigned def_funds_max = 100000;
    const unsigned def_funds_min = 50000;
    const size_t def_buyer_num = 600;
    const unsigned def_patience = 100;
    const unsigned def_cd = 3;

    // behavioral values
    const unsigned decision_roll_High_Value_Interested = 35;
    const unsigned decision_roll_High_Value_Uninterested = 80;
    const unsigned decision_roll_Low_Value_Interested = 1;
    const unsigned decision_roll_Low_Value_Uninterested = 30;

    const unsigned min_patience_loss_Succ_Uninterested = 10;
    const unsigned max_patience_loss_Succ_Uninterested = 15;
    const unsigned min_patience_loss_Fail_Interested = 10;
    const unsigned min_patience_loss_Fail_Uninterested = 20;
    const unsigned max_patience_loss_Fail_Interested = 20;
    const unsigned max_patience_loss_Fail_Uninterested = 60;

    const unsigned offer_min_mod = 1000;
    const unsigned offer_max_mod = 10;

    const unsigned flavor_text_roll_criteria = 6;
}

namespace errors{
    const std::string missing_f = "file not found\n";
    const std::string cpy_error = "copy error";
    const std::string s_p_getter = "start price getter error";
    const std::string val_getter = "value getter error";
    const std::string name_getter = "name getter error";
    const std::string typ_getter = "type getter error";
    const std::string bid_read = "Couldn't properly read aruk.txt";
    const std::string missing_source = "Source files failed to load. Terminating";

    const std::string mem_check = "Auction memory check successful";
}
#endif // UTILITY_INCLUDED
