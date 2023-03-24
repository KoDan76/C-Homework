#include <iostream>
#include <ctime>
#include "Organizers.h"
#include "Utility.hpp"
#include "HumansAndNames.h"
#include "Bids.h"
#include "gtest_lite.h"
#include "Archives.h"

using namespace std;
// Functions for testing various aspects of the program 
namespace tests{
	// Tests out contructors that are not explicitly called in the control menu
    void constructorTest(){
        TEST(random,number){
            EXPECT_GE(def_val::def_funds_max,random_gen::capRandomUI(def_val::def_funds_min,def_val::def_funds_max)) << "random gen error";
        } END

        TEST(the_bids, ctor_copy){
            Bid test_bid(500,400,"Teknospancelzat",luxury);
            EXPECT_EQ((unsigned)400, test_bid.getStart_price())<< errors::s_p_getter;
            EXPECT_EQ((unsigned)500, test_bid.getValue()) << errors::val_getter;
            EXPECT_EQ("Teknospancelzat",test_bid.getName()) << errors::name_getter;
            EXPECT_EQ(luxury, test_bid.getType()) << errors::typ_getter;

            Bid test_bid2(test_bid);
            EXPECT_EQ((unsigned)400, test_bid2.getStart_price())<< errors::cpy_error;
            EXPECT_EQ((unsigned)500, test_bid2.getValue()) << errors::cpy_error;
            EXPECT_EQ("Teknospancelzat",test_bid2.getName()) << errors::cpy_error;
            EXPECT_EQ(luxury, test_bid2.getType()) << errors::cpy_error;
        }END

        TEST(bid_file_reading, ctor){
            Bid_List test_bid_list(titles::txt_bids);
            EXPECT_EQ("Sandwich of Lord Sandwich",test_bid_list[0].getName()) << errors::bid_read;
        }END

        TEST(Organizer, ctor){
            Name_List test_first_names(titles::txt_firstnames);
            Name_List test_second_names(titles::txt_secondnames);
            Bid test_bid(500,400,"Teknospancelzat",luxury);
            Organizer test_org(test_first_names, test_second_names, test_bid, def_val::def_buyer_num, def_val::def_funds_min, def_val::def_funds_max);
            cout << "Name generated:" << test_org.getName() << endl;
            EXPECT_NE("",test_org.getName()) << errors::name_getter ;
        } END

        TEST(Buyer_test, ctor_getter){
            Name_List test_first_names(titles::txt_firstnames);
            Name_List test_second_names(titles::txt_secondnames);
            Buyer test_buyer(test_first_names, test_second_names, def_val::def_funds_min, def_val::def_funds_min);
            EXPECT_GE(def_val::def_funds_max,test_buyer.getCurr_Money()) << "Buyer fund generation error";
            EXPECT_LE(def_val::def_funds_min,test_buyer.getCurr_Money()) << "Buyer fund generation error";
            EXPECT_NE(invalid,test_buyer.getPreference()) << "Buyer preference generation error";
        } END
    }
	
	// Checks if all source files are in their required place
    void fileTest(bool &no_errors){
        try{
            Name_List test_first_names(titles::txt_firstnames);
        } catch (std::string prob ){
            cout << prob;
            no_errors = false;
        }
        try{
            Name_List test_second_names(titles::txt_secondnames);
        } catch (std::string prob){
            cout << prob;
            no_errors = false;
        }
        try{
            Archive_List test_archives(titles::txt_archives);
        } catch (std::string prob){
            cout << prob;
            no_errors = false;
        }
        try{
            Bid_List test_bids(titles::txt_bids);
        }catch(std::string prob){
            cout<< prob;
            no_errors = false;
        }
    }
	
	// Runs N number of tests to see if there are memory allocation anomalies or memory leak
    void memoryTest(int N){
        int i;
        for (i = 0; i < N; i++){
            Name_List* first_names = new Name_List(titles::txt_firstnames);
            Name_List* second_names = new Name_List(titles::txt_secondnames);
            Bid_List* bids = new Bid_List(titles::txt_bids);
            Organizer* auction = new Organizer(*first_names, *second_names, (*bids)[random_gen::randomUI(bids->getSize()-1)], def_val::def_buyer_num, def_val::def_funds_min, def_val::def_funds_max);
            delete auction;
            delete first_names;
            delete second_names;
            delete bids;
        }
        std::cout << i << errors::mem_check << std::endl;
    }
}

// main testing environment 
int main()
{
    bool quit = false;
    char command;
    srand (time(NULL));
    cout << titles::greeting << endl;
    bool no_errors = true;

    tests::fileTest(no_errors);

    if(no_errors){
        cout << titles::integrity_check << endl;

        Name_List* first_names = new Name_List(titles::txt_firstnames);
        Name_List* second_names = new Name_List(titles::txt_secondnames);
        Bid_List* bids = new Bid_List(titles::txt_bids);

        while (!quit){
            cout << titles::main_menu << endl;
            cin >> command;
            cin.ignore();

            char choice;
            switch (tolower(command)){
            case 'n':
                cout << titles::chose_scenario << endl;
                cin >> choice;
                if (choice == 'd'){
                    try {
                    Organizer* auction = new Organizer(*first_names, *second_names, (*bids)[random_gen::randomUI(bids->getSize()-1)], def_val::def_buyer_num, def_val::def_funds_min, def_val::def_funds_max);
                    auction->writeWinner();
                    delete auction;
                    } catch (const std::bad_alloc&){
                        std::cout << "Couldn't allocate memory. Terminating";
                    }

                }
                if (choice == 'c'){
                    cout << titles::chose_b_num;
                    unsigned custom_num;
                    cin >> custom_num;
                    cin.ignore();

                    cout << titles::chose_min_funds;
                    unsigned custom_min;
                    cin >> custom_min;
                    cin.ignore();

                    cout << titles::chose_max_funds;
                    unsigned custom_max;
                    cin >> custom_max;
                    cin.ignore();

                    if (custom_min > custom_max){
                        unsigned tmp = custom_min;
                        custom_min = custom_max;
                        custom_max = tmp;
                    }

                    bids->writeAll();
                    cout << titles::chose_bid;
                    size_t custom_ix;
                    cin >> custom_ix;
                    if (custom_ix == 0 ||  custom_ix >= bids->getSize()) custom_ix = random_gen::randomUI(bids->getSize());
                    cin.ignore();

                    Organizer* auction = new Organizer(*first_names, *second_names, (*bids)[custom_ix-1], custom_num, custom_min, custom_max);
                    cout << titles::generate_scenario;
                    auction->writeWinner();
                    delete auction;
                }
                break;

            case 'q': quit = true;
                break;

            case 'a': createArchives();
                break;

            case 't':
                tests::memoryTest(def_val::def_mem_test);
                tests::constructorTest();
                break;

            default:
                cout << titles::invalid_command << endl;
            }
        }
        delete first_names;
        delete second_names;
        delete bids;
    } else {
        cout << errors::missing_source;
    }
}
