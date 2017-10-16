
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

int add_or_delete(uint id, std::vector<bool> & bitset) {
    bitset[id] = !bitset[id]; 
    return (bitset[id]) ? 1 : -1;
}

double Item::get_price_per_weight() const {
    if (price_per_weight == -1) 
        price_per_weight = 1.0 * price / weight;

    return price_per_weight;
}

bool Item::operator<(const Item & it) const {
    return get_price_per_weight() < it.get_price_per_weight();
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
    
    std::vector<bool> best_bitset;
    best_bitset = curr_bitset;
    int best_price = 0, best_weight = 0;

    uint i = 0, x;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        x = get_first_zero_bit(i);
        std::cout << "i: " << i << " x: " << x << std::endl;
        if (x >= items.size()) // Hamiltonian path reached non-existing element
            return Solution(id, best_price, best_bitset);  

        int sign = add_or_delete(x, curr_bitset);        
        curr_price += sign * items[x].price;
        curr_weight += sign * items[x].weight;
        //Solution(id, curr_price, curr_bitset).print();

        if (curr_weight <= capacity && curr_price > best_price) {
            best_bitset = curr_bitset;
            best_price = curr_price;
            best_weight = curr_weight;
        }

        i++;
    }
}

bool Task::cpm_items_idx(uint a, uint b) {
    return items[a] < items[b];
}

Solution Task::solve_heuristic() {
    std::vector<uint> items_idx;
    items_idx.reserve(items.size());
    for (uint i = 0; i < items.size(); i++)
        items_idx[i] = i;

    std::sort(sorted_items.begin(), sorted_items.end(), cmp_items_idx);
     
    std::vector<bool> curr_bitset(items.size(), false); 

    uint i = items.size() - 1;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        uint idx = item_idx[i];
        Item & item = items[idx];
        if (curr_weight + item.weight > capacity)
            return Solution(id, curr_price, bitset);

        curr_price += item.price;
        curr_weight += item.weight;
        curr_bitset[idx] = true;
    }
    return Solution(id, curr_price, curr_bitset);
}

void Solution::print() {
    std::cout << "ID: " << id << std::endl\
        << "tot_price: " << total_price << std::endl;
    for (uint i = 0; i < bitset.size(); i++) 
        std::cout << bitset[i] << std::endl;
    std::cout << std::endl;
}

void Task::print() {
    std::cout << "ID: " << id << std::endl << "cap: " << capacity << std::endl;
    for (uint i = 0; i < items.size(); i++) 
        std::cout << items[i].price << " / " << items[i].weight << std::endl;
    std::cout << std::endl;
}

bool test() {
    std::cout << "get_first_zero_bit()" << std::endl;    
    for (uint i = 0; i < 17; i++)
        std::cout << i << " -> " << get_first_zero_bit(i) << std::endl;    

    return true;
}
