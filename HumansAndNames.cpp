#include "HumansAndNames.h"
#include "Utility.hpp"
#include <iostream>

using namespace::random_gen;

Name_List::Name_List(std::string filename){
    std::ifstream file;
    file.open (filename);

    if(!file.is_open()){
        throw filename + " " + errors::missing_f;
    }


    file >> l_size;
    all_names = new std::string[l_size];
    for(size_t i = 0; i < l_size; i++)
    {
        file >> all_names[i];
    }
    file.close();
}

Name_List::~Name_List(){ delete[] all_names;}

Human::Human(Name_List& surnames, Name_List& firstnames){
    GenNames(surnames, firstnames);
}
void Human::GenNames(Name_List& surnames, Name_List& firstnames){
    std::string first_name;
    std::string second_name;

    first_name = firstnames[randomUI(firstnames.getSize()-1)];
    second_name = surnames[randomUI(surnames.getSize()-1)];

    name = first_name + " " + second_name;
}



