
#include <ctime>
#include <vector>
#include <fstream>
#include <functional>
#include "item_solution.h"
#define uint unsigned int


typedef std::function<int()> Solve_call;

class Task;
class Task {
    uint id;
    int capacity;
    std::vector<Item> items;

    static int add_or_delete(uint id, std::vector<bool> & bitset);
public:
    Task(const std::string & line);
    Task(const Task & task) : id(task.id), capacity(task.capacity),
                              items(task.items) {};
    static uint get_first_zero_bit(uint64_t bits); 
    void print();

    int solve_bruteforce();
    int solve_heuristic();

    std::pair<int, double> time_call(Solve_call call);

    std::pair<int, double> time_bruteforce() { 
        return time_call(std::bind(&Task::solve_bruteforce, this)); };
    std::pair<int, double> time_heuristic() { 
        return time_call(std::bind(&Task::solve_heuristic, this)); };

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
