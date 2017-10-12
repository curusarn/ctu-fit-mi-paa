
#include <sstream>
#include "task.h"

double Item::get_price_per_weight() {
    if (price_per_weight == -1) 
        price_per_weight = 1.0 * price / weight;

    return price_per_weight;
}

Solution::Solution(const std::string & line) {
    std::istringstream iss(line);

    uint n, b; // count, bool
    iss >> id >> n >> total_price;
    for (uint i = 0; i < n; i++) {
        iss >> b;
        solution.push_back(b);
    }
}

Task::Task(const std::string & line) {
    std::istringstream iss(line);

    uint n; // count
    int p, w; // price, weight
    iss >> id >> n >> capacity;
    for (uint i = 0; i < n; i++) {
        iss >> w >> p;
        items.push_back(Item(p, w));
    }
}

Solution Task::solve_bruteforce() {
    return Solution(0,0,0,std::vector<bool>());
}
Solution Task::solve_heuristic() {
    return Solution(0,0,0,std::vector<bool>());
}
