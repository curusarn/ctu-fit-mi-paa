
#include <ctime>
#include <vector>
#include <fstream>
#include <functional>
#include "item_solution.h"
#define uint unsigned int

#define MIN_ALLOWED_TIME 0.00001
// CLOCKS_PER_SEC is about 1 * 10^(6)
// so I allow minimal time of about 10^(-5) 


//typedef std::function<int()> Solve_call;

class Task;
class Task {
    uint id;
    int capacity;
    std::vector<Item> items;

    static int add_or_delete(uint id, std::vector<bool> & bitset);
    static uint get_first_zero_bit(uint64_t bits); 
    int _solve_branch_and_bound(const std::vector<int> &, int &,
                                int, int, uint);
    int get_safe_weight(const std::vector<std::vector<int>> & weights,
                        int item_idx, int price) const;
public:
    Task(const std::string & line);
    Task(const Task & task) : id(task.id), capacity(task.capacity),
                              items(task.items) {};
    void print();

    int solve_bruteforce();
    int solve_branch_and_bound();
    int solve_heuristic();
    int solve_dynamic_programming_by_price();
    int solve_fptas(double epsilon);

    template <typename Call>
    std::pair<int, double> time_call(Call call);

    std::pair<int, double> time_bruteforce() { 
        return time_call(std::bind(&Task::solve_bruteforce, this)); };
    std::pair<int, double> time_heuristic() { 
        return time_call(std::bind(&Task::solve_heuristic, this)); };
    std::pair<int, double> time_branch_and_bound() { 
        return time_call(std::bind(&Task::solve_branch_and_bound, this)); };
    std::pair<int, double> time_dynamic_programming_by_price() { 
        return time_call(std::bind(&Task::solve_dynamic_programming_by_price,
                                   this)); };
    std::pair<int, double> time_fptas(double epsilon) { 
        return time_call(std::bind(&Task::solve_fptas, this, epsilon)); };
};

template <typename Call>
std::pair<int, double> Task::time_call(Call call) {
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
