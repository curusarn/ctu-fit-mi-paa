
#include <iostream>
#include <sstream>
#include "item_solution.h"

double Item::get_price_per_weight() const {
    if (price_per_weight == -1) 
        price_per_weight = 1.0 * price / weight;

    return price_per_weight;
}

bool Item::operator<(const Item & it) const {
    return get_price_per_weight() < it.get_price_per_weight();
}

Item& Item::operator=(const Item & it) {
    price = it.price;
    weight = it.weight;
    price_per_weight = it.price_per_weight;
    return *this;
}



Solution::Solution(const std::string & line) {
    std::istringstream iss(line);

    uint n, b; // count, bool
    iss >> id >> n >> total_price;
    bitset.reserve(n);
    for (uint i = 0; i < n; i++) {
        iss >> b;
        bitset.push_back(b);
    }
}

bool Solution::operator==(const Solution & sol) const {
    return total_price == sol.get_total_price();
}

void Solution::print() {
    std::cout << "ID: " << id << std::endl\
        << "tot_price: " << total_price << std::endl;
    for (uint i = 0; i < bitset.size(); i++) 
        std::cout << bitset[i] << std::endl;
    std::cout << std::endl;
}
