#include "splitter.h"
#include <iostream>
Splitter::Splitter()
{

}

std::vector<int> Splitter::split(const std::string &need_to_split, const char &parametr){
    std::vector <int> splitted_data;
    std::string buff;
    for(auto sym: need_to_split){
       if ( sym == parametr ){
          splitted_data.push_back(std::atoi(buff.c_str()));
          buff.clear();
          continue;
        }
        buff+=sym;
    }
    splitted_data.push_back(std::atoi(buff.c_str()));
    return  splitted_data;
}
