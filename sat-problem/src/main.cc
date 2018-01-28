
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <limits.h>
#include <random>
#include "task.h" 
#include "record_collector.h" 

#define uint unsigned int
#define VAR_COUNT 5000
#define CLAUSE_COUNT 8000

#define MIN_VAR_COUNT 5
#define MAX_VAR_COUNT 5000

#define REPEAT 10

// simulated annealing
// max_steps, starting_temp, frozen_const, equlibrium_const, cooling_koef
#define SA_MAX_STEPS 10000 
#define SA_START_TEMP VAR_COUNT * CLAUSE_COUNT / 10 + 20000
#define SA_FROZEN_CONST 0.4 * VAR_COUNT
#define SA_EQULIBRIUM_CONST 10 
#define SA_COOLING_KOEF 0.965
#define SA_NEIGHBOUR_CONST std::pow(std::log(VAR_COUNT), 1.3) 
//+ 0.1 * std::pow(std::log(VAR_COUNT), 1.8)
#define SA_FITNESS_KOEF 1000 * VAR_COUNT / CLAUSE_COUNT 


// SAT problem generator
Task sat_gen(int var_count, int clause_count) {
    std::random_device rd;  //Used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::bernoulli_distribution rand_bool(0.5);
    std::uniform_int_distribution<> rand_weight(0, 100);
    std::uniform_int_distribution<> rand_var(0, var_count - 1);
     
    std::vector<int> weights(var_count);
    std::vector<Clause> clauses(clause_count);

    for ( auto& w : weights )
        w = rand_weight(gen);

    for ( auto& c : clauses )
        for ( auto& var : c ) {
            var.first = rand_bool(gen); // not
            var.second = rand_var(gen); // variable id
        }

    return Task(std::move(weights), std::move(clauses));
}

int main(){
    srand (time(NULL));


    std::cout << "PARAMETER (miss time max_miss max_time)"
              << " bruteforce annealing"
              << std::endl;
    std::cerr << " start_temp = " << SA_START_TEMP 
              << " frozen_const = " << SA_FROZEN_CONST 
              << " ngh_const = " << SA_NEIGHBOUR_CONST 
              << " fit_koef = " << SA_FITNESS_KOEF 
              << std::endl;


    RecordCollector collector{};
    auto task = sat_gen(VAR_COUNT, CLAUSE_COUNT);

    auto ref = task.get_theoretical_best(SA_FITNESS_KOEF);

    for (int i = 0; i < REPEAT; i++) {
        // max_steps, starting_temp, frozen_const, equlibrium_const,
        // cooling_koef, neighbour_const, fitness_koef
        std::pair<int, double> rec = task.time_annealing(SA_MAX_STEPS, SA_START_TEMP,
                                       SA_FROZEN_CONST, SA_EQULIBRIUM_CONST,
                                       SA_COOLING_KOEF, SA_NEIGHBOUR_CONST,
                                       SA_FITNESS_KOEF);

        collector.add_record(ref, rec);
    }

    collector.print_result(std::cerr);

    return 0;
}
