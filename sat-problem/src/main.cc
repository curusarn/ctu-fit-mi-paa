
#include <iostream>
#include <vector>
#include <cassert>
#include <limits.h>
#include <random>
#include "task.h" 
#include "record_collector.h" 

#define uint unsigned int
#define VAR_COUNT 100
#define CLAUSE_COUNT 50 

#define REPEAT 1

// simulated annealing
// max_steps, starting_temp, frozen_const, equlibrium_const, cooling_koef
#define SA_MAX_STEPS 10000 
#define SA_START_TEMP 200 
#define SA_FROZEN_CONST 100
#define SA_EQULIBRIUM_CONST 10 
#define SA_COOLING_KOEF 0.98
#define SA_NEIGHBOUR_CONST 10 
#define SA_FITNESS_KOEF 0.04 


const char* DATA_PATH = "data/";
const int BF_LIMIT = 26;

std::string instance_path(uint problem_category) {
    return std::string(DATA_PATH) + "knap_" +
           std::to_string(problem_category) + ".inst.dat";
}

std::string solution_path(uint problem_category) {
    return std::string(DATA_PATH) + "knap_" +
           std::to_string(problem_category) + ".sol.dat";
}


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


    RecordCollector collector(REPEAT, 2);
    auto task = sat_gen(VAR_COUNT, CLAUSE_COUNT);

    auto ref = task.get_theoretical_best(SA_FITNESS_KOEF);

    for (int i = 0; i < REPEAT; i++) {
        std::vector<std::pair<int,double>> record;
        record.emplace_back(ref);
        // max_steps, starting_temp, frozen_const, equlibrium_const,
        // cooling_koef, neighbour_const, fitness_koef
        record.emplace_back(task.time_annealing(SA_MAX_STEPS, SA_START_TEMP,
                                        SA_FROZEN_CONST, SA_EQULIBRIUM_CONST,
                                        SA_COOLING_KOEF, SA_NEIGHBOUR_CONST,
                                        SA_FITNESS_KOEF));

        collector.add_record(record[0].first, record);
    }

    collector.print_result(std::cerr);

    return 0;
}
