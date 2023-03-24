#include "Archives.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "Utility.hpp"

void Archive::writeOut() {
    std::cout << buyer_name << " bought " <<bid_name << " for $"<<buying_price << std::endl;
}

void Archive_List::writeAll(){
    std::cout << titles::archive_title << std::endl;
    for (size_t i = 0; i < l_size; i++){
        archives[i]->writeOut();
    }
}

Archive_List::Archive_List (std::string filename){
    std::ifstream file(filename);

    if (!file.is_open()){
        throw filename + " " + errors::missing_f;
    }

    char arr[512];
    l_size = 0;
    for (size_t i = 0; file.getline(arr,512); i++) {
        std::string tmp_buyer = arr;
        file.getline(arr,512);
        std::string tmp_bid = arr;
        unsigned tmp_price;
        file >> tmp_price;
        Archive* tmpArch = new Archive(tmp_buyer, tmp_bid, tmp_price);
        add(tmpArch);
        file.getline(arr,512);
    }
    file.close();
}

void Archive_List::add(Archive* new_item){
    if (l_size == 0){
        archives = new Archive*[l_size+1];
        archives[l_size++] = new_item;
    } else {
        Archive** tmp_archives = new Archive*[l_size+1];
        for(size_t i = 0; i < l_size; i++){
            tmp_archives[i] = archives[i];
        }

        tmp_archives[l_size] = new_item;
        delete[] archives;
        archives = tmp_archives;
        l_size++;
    }
}

Archive_List::~Archive_List(){
    if (archives != nullptr){
        for (size_t i = 0; i < l_size; i++){
            delete archives[i];
        }
    delete[] archives;
    }
}

void createArchives(){
    Archive_List full_archives(titles::txt_archives);
    full_archives.writeAll();
}



