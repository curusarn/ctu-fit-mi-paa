
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "task.h"

#define MIN_ALLOWED_TIME 0.00001
// CLOCKS_PER_SEC is about 1 * 10^(6)
// so I allow minimal time of about 10^(-5) 

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
uint Task::get_first_zero_bit(uint64_t bits){
    uint64_t mask = 1;
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

    uint64_t i = 0;
    uint x;
    int curr_price = 0, curr_weight = 0;
    while (true) {
        x = get_first_zero_bit(i);

        //if (x > 30) std::cerr << "  >>> progress: " << x << " / ~" << items.size() << std::endl;
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
    // sort by price_per_weight
    std::sort(items.begin(), items.end(),
          [](const Item & a, const Item & b){
                return a.get_price_per_weight() < b.get_price_per_weight(); });
     
    assert( items[0].get_price_per_weight() <= items[1].get_price_per_weight() );

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

int Task::_solve_branch_and_bound(const std::vector<int> & price_sums,
                                  int & best_price,
                                  int curr_price, int curr_weigth,
                                  uint item_idx) {
    
    if (item_idx == items.size())
        return curr_weigth; // end of recursion - no more items
      
    if (curr_weigth > capacity)
        return 0; // cut branches that exceed capacity

    if (curr_price + price_sums[item_idx] <= best_price)
        return 0; // cut branches that won't give better solution 

    int res1 = _solve_branch_and_bound(price_sums, best_price,
                                       curr_price + items[item_idx].price,
                                       curr_weigth + items[item_idx].weight,
                                       item_idx + 1);

    best_price = std::max(best_price, res1);
    
    int res0 = _solve_branch_and_bound(price_sums, best_price,
                                       curr_price, curr_weigth,
                                       item_idx + 1);

    best_price = std::max(best_price, res0);

    return best_price;
}

int Task::solve_branch_and_bound() {
    // sort by weight (desc)
    std::sort(items.begin(), items.end(),
          [](const Item & a, const Item & b){ return a.price > b.price; });

    assert( items[0].price >= items[1].price );

    // each member is 
    //      sum of item with same index and all following items
    std::vector<int> price_sums(items.size());

    price_sums[items.size()-1] = items[items.size()-1].price;
    for (int i = static_cast<int>(items.size()-2); i >= 0; i--) 
        price_sums[i] = price_sums[i+1] + items[i].price; 

    int b = 0;
    return _solve_branch_and_bound(price_sums, b, 0, 0, 0);
}


std::pair<int, double> Task::time_call(Solve_call call) {
    //using namespace std;
    std::clock_t begin = std::clock();

    int result = call();

    std::clock_t end = std::clock();

    double time = double(end - begin) / CLOCKS_PER_SEC;

    int number_of_runs = 1;
    while (time < MIN_ALLOWED_TIME) {
        // run call() multiple times and count the average running time
        //      until you get something larget than MIN_ALLOWED_TIME
        number_of_runs *= 16;
        begin = std::clock();
        for(int i = 0; i < number_of_runs; i++)
            call();
        end = std::clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
    }

    return std::make_pair(result, time / number_of_runs);
}


void Task::print() {
    std::cout << "ID: " << id << std::endl << "cap: " << capacity << std::endl;
    for (uint i = 0; i < items.size(); i++) 
        std::cout << items[i].price << " / " << items[i].weight << std::endl;
    std::cout << std::endl;
}
