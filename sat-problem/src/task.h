#include <ctime>
#include <vector>
#include <fstream>
#include <functional>
#include "clause.h"

#define MIN_ALLOWED_TIME 0.00001
// CLOCKS_PER_SEC is about 1 * 10^(6)
// so I allow minimal time of about 10^(-5) 



class Task;
class Task {
    std::vector<int> weights;
    std::vector<Clause> clauses;

    uint no_sat_clauses(const std::vector<bool> & bitset);
    void print();
    void print(const std::vector<bool> & bitset);
public:
    Task(std::vector<int> && a_weights, std::vector<Clause> && a_clauses) 
            : weights(std::move(a_weights)), clauses(std::move(a_clauses)) {};
    Task(Task && task) : weights(std::move(task.weights)),
                         clauses(std::move(task.clauses)) {};

    int get_theoretical_best(double fitness_koef);
    int solve_annealing(int max_steps, double starting_temp, int frozen_const,
                        int equlibrium_const, double cooling_koef,
                        int neighbour_const, double fitness_koef);

    template <typename Call>
    std::pair<int, double> time_call(Call call);

    std::pair<int, double> time_annealing(int max_steps, double starting_temp,
                int frozen_const, int equlibrium_const, double cooling_koef,
                int neighbour_const, double fitness_koef) { 
        return time_call(std::bind(&Task::solve_annealing, this,
                                   max_steps, starting_temp, frozen_const, 
                                   equlibrium_const, cooling_koef,
                                   neighbour_const, fitness_koef)); };
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
        //      until you get something larger than MIN_ALLOWED_TIME
        number_of_runs *= 16;
        begin = std::clock();
        for(int i = 0; i < number_of_runs; i++)
            call();
        end = std::clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
    }

    //std::cout << result << " | " << time / number_of_runs << std::endl;
    return std::make_pair(result, time / number_of_runs);
}


