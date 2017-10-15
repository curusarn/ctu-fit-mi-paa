
#include <sstream>
#include <iostream>
#include "task.h"

// O*(n)
uint get_first_zero_bit(uint bits){
    uint mask = 1;
    uint index = 0;
    while ((bits & mask) != 0) {
        mask = (mask<<1);
        index++;
    }
    return index;
}

int add_or_delete(uint id, std::vector<bool> bitset) {
    if (!bitset[id]) {
        bitset[id] = true;
        return 1;
    }

    bitset[id] = false;
    return -1;
}

double Item::get_price_per_weight() {
    if (price_per_weight == -1) 
        price_per_weight = 1.0 * price / weight;

    return price_per_weight;
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

Task::Task(const std::string & line) {
    std::istringstream iss(line);

    uint n; // count
    int p, w; // price, weight
    iss >> id >> n >> capacity;
    items.reserve(n);
    for (uint i = 0; i < n; i++) {
        iss >> w >> p;
        items.emplace_back(p, w);
    }
}


Solution Task::solve_bruteforce() {
    std::vector<bool> curr_bitset(items.size(), false); 
    
    std::vector<bool> best_bitset = curr_bitset;
    int best_price = 0, best_weight = 0;

    uint i = 0, x;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        x = get_first_zero_bit(i);
        if (x >= items.size()) // Hamiltonian path reached non-existing element
            return Solution(id, capacity, best_price, best_bitset);  

        int sign = add_or_delete(x, curr_bitset);        
        curr_price += sign * items[x].price;
        curr_weight += sign * items[x].weight;

        if (curr_weight <= capacity && curr_price > best_price) {
            best_bitset = curr_bitset;
            best_price = curr_price;
            best_weight = curr_weight;
        }

        i++;
    }
}

Solution Task::solve_heuristic() {
    return Solution(0,0,0,std::vector<bool>());
}

void Task::print() {
    std::cout << "ID: " << id << std::endl << "cap: " << capacity << std::endl;
    for (uint i = 0; i < items.size(); i++) 
        std::cout << items[i].price << " / " << items[i].weight << std::endl;
    std::cout << std::endl;
}
