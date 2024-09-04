//#include "python3"
#include "iostream"
#include "vector"
#include "lib/adapter.hpp"
#include "map"

int main () {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {25,16,9};
    auto result = test_vector | take(3) | reverse() | transform([](int i){return i * i;});
    for (auto i: result) {
        std::cout << i << ' ';
    }
}