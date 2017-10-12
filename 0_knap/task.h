
#include <vector>
#include <fstream>

class Item {
    const int price;
    const int weight;
    double price_per_weight = -1;

public:
    Item(int p, int w) : price(p), weight(w) {};
    double get_price_per_weight();
};

class Solution {
    uint id;
    int capacity;
    int total_price;
    std::vector<bool> solution;

public:
    Solution(const std::string & line);
    Solution(uint i, int c, int tp, std::vector<bool> sol) : 
        id(i), capacity(c), total_price(tp), solution(sol) {}
    Solution(const Solution & sol) : 
        id(sol.id), capacity(sol.capacity), 
        total_price(sol.total_price), solution(sol.solution) {};
};

class Task {
    uint id;
    int capacity;
    std::vector<Item> items;

public:
    Task(const std::string & line);
    Task(const Task & task) : id(task.id), capacity(task.capacity),
                              items(task.items) {};
    Solution solve_bruteforce();
    Solution solve_heuristic();
};


template <typename T>
std::vector<T> parse(std::ifstream & infile) {
    std::vector<T> list;
    std::string line;
    while (std::getline(infile, line)) {
        list.emplace_back(T(line));
    }

    return list;
}
