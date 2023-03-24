#include "Bids.h"
#include <fstream>
#include <sstream>
#include <iostream>

Bid_List::Bid_List(std::string filename){
    std::ifstream file(filename);

    if(!file.is_open()){
        throw filename + " " + errors::missing_f;
    }

    file >> l_size;
    bid_list = new Bid*[l_size];
    char arr[512];
    file.getline(arr,512);

    for (size_t i = 0; i < l_size; i++) {
        file.getline(arr,512);
        std::string tmp_name = arr;
        unsigned tmp_type;
        file >> tmp_type;

        unsigned tmp_price;
        file >> tmp_price;

        unsigned tmp_value;
        file >> tmp_value;
        try{
            Bid* tmpBid = new Bid(tmp_value, tmp_price, tmp_name, (Category)tmp_type);
            bid_list[i] = tmpBid;
        } catch(std::bad_alloc&){
            std::cout << "Memory allocation error when creating new Bid:" << i;
        }
        file.getline(arr,512);
    }
    file.close();
}

void Bid::writeOut(){
    std::cout << " " << name << " Starting price: $" << start_price << " Estimated value: $" << value << std::endl;
}

void Bid_List::writeAll(){
    for (size_t i = 0; i < l_size; i++){
        std::cout << i+1;
        bid_list[i]->writeOut();
    }
}

void Bid_List::reset(){
    for (size_t i = 0; i < l_size; i++){
        delete bid_list[i];
    }
    l_size = 0;
    delete[]bid_list;
}
