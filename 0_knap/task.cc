
#include <sstream>
#include <iostream>
#include <algorithm>
#include "task.h"


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

// O*(1)
uint Task::get_first_zero_bit(uint bits){
    uint mask = 1;
    uint index = 0;
    while ((bits & mask) != 0) {
        mask = (mask<<1);
        index++;
    }
    return index;
}

int Task::add_or_delete(uint id, std::vector<bool> & bitset) {
    bitset[id] = !bitset[id]; 
    return (bitset[id]) ? 1 : -1;
}

int Task::solve_bruteforce() {
    std::vector<bool> curr_bitset(items.size(), false); 
     
    std::vector<bool> best_bitset;
    best_bitset = curr_bitset;
    int best_price = 0;

    uint i = 0, x;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        x = get_first_zero_bit(i);

        //std::cout << "i: " << i << " x: " << x << std::endl;
        if (x >= items.size()) // Hamiltonian path reached non-existing element
            return best_price;  

        int sign = add_or_delete(x, curr_bitset);        
        curr_price += sign * items[x].price;
        curr_weight += sign * items[x].weight;
        //Solution(id, curr_price, curr_bitset).print();

        if (curr_weight <= capacity && curr_price > best_price) {
            best_bitset = curr_bitset;
            best_price = curr_price;
        }

        i++;
    }
}


int Task::solve_heuristic() {
    std::sort(items.begin(), items.end());
     
    uint i = items.size() - 1;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        Item & item = items[i];
        if (i > items.size() || curr_weight + item.weight > capacity)
            return curr_price;

        curr_price += item.price;
        curr_weight += item.weight;
        i--;
    }
    return curr_price;
}


std::pair<int, double> Task::time_call(Solve_call call) {
  //using namespace std;
  std::clock_t begin = std::clock();

  int result = call();

  std::clock_t end = std::clock();
  return std::make_pair(result, double(end - begin) / CLOCKS_PER_SEC);
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
        std::cout << i << " -> " << Task::get_first_zero_bit(i) << std::endl; 

    return true;
}
