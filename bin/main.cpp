//#include "python3"
#include "iostream"
#include "vector"
#include "lib/adapter.hpp"
#include "map"

int main () {
    std::map<int,int> v1= {{1,2},{3,4}, {5,6}};
    //std::set<int> v1 = {1,2,3,4,5};
    auto res2 = v1 | keys() | filter([](int i){return i == 3;});
    for (auto val : res2 ) {
        std::cout << val << " ";
    } std::cout << '\n';

}