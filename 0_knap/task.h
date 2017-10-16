
#include <vector>
#include <fstream>
#define uint unsigned int

class NoSolutionException : std::exception {
public:
    const char * what() { return "No solution found."; }; 
};

class Item {
    mutable double price_per_weight = -1;

public:
    int price;
    int weight;

    Item(int p, int w) : price(p), weight(w) {};
    double get_price_per_weight() const;
    bool operator<(const Item & it) const;
    Item& operator=(const Item& it); 
};

class Solution {
    uint id;
    int total_price;
    std::vector<bool> bitset;

public:
    Solution(const std::string & line);
    Solution(uint i, int tp, std::vector<bool> sol) : 
        id(i), total_price(tp), bitset(sol) {}
    Solution(const Solution & sol) : 
        id(sol.id), total_price(sol.total_price),
        bitset(sol.bitset) {};

    const std::vector<bool> & get_bitset() const { return bitset; };
    std::vector<bool> & get_bitset() { return bitset; };
    bool operator==(const Solution & sol) const;
    int get_total_price() const { return total_price; };
    void set_total_price(int t) { total_price = t; };
    void print();
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
    int solve_heuristic();
    void print();
};


template <typename T>
std::vector<T> parse(std::ifstream & infile) {
    //std::cout << "parse" << std::endl;
    std::vector<T> list;
    std::string line;
    while (std::getline(infile, line)) {
        list.emplace_back(line);
    }

    return list;
}

bool test();
