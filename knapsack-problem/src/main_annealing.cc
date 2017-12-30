
#include <iostream>
#include <vector>
#include <cassert>
#include <limits.h>
#include "task.h" 
#include "record_collector.h" 

#include "knapgen/knapcore.h"


#define uint unsigned int
#define NEUTRAL_WEIGTH 100
#define NEUTRAL_PRICE 40
#define NEUTRAL_RATIO 0.65  
#define NEUTRAL_GRANULARITY 0 
#define NEUTRAL_PROBLEM_SIZE 100 

#define X_VALUES 42
#define REPEAT 100
#define MIN_PROBLEM_SIZE 5 
#define MAX_PROBLEM_SIZE 24 

// simulated annealing
// max_steps, starting_temp, frozen_const, equlibrium_const, cooling_koef
#define SA_MAX_STEPS 6000
#define SA_START_TEMP 60
#define SA_FROZEN_CONST 50
#define SA_EQULIBRIUM_CONST 10 
#define SA_COOLING_KOEF 0.99


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

// C++ binding + wrapper for knapcore included from knapgen/knapcore.h
Task knapgen(int max_weight, int max_price, double cap_sum_ratio,
             int granularity, double gran_exp, int pr_size = 7) {
    //int n = pr_size % (MAX_PROBLEM_SIZE - MIN_PROBLEM_SIZE) + MIN_PROBLEM_SIZE;
    int n = pr_size;
    std::vector<int> weights(n);
    std::vector<int> costs(n);

    // I would like to use this moment to say thanks to C++11 and to it's 
    //      std::vector.data() method for keeping my code "malloc-less".
    int total_weight = knapcore(weights.data(), costs.data(), n, 
                            max_weight, max_price, gran_exp, granularity);

    int capacity = cap_sum_ratio * total_weight;

    return Task(capacity, weights, costs);
}

int main(int argc, char * argv[]){
    srand (time(NULL));


    std::cout << "PARAMETER (miss time max_miss max_time)"
              << " dynamic heuristic annealing"
              << std::endl;


    RecordCollector collector(42, 2);
    auto task = knapgen(NEUTRAL_WEIGTH, NEUTRAL_PRICE,
                        NEUTRAL_RATIO, NEUTRAL_GRANULARITY,
                        NEUTRAL_GRANULARITY, NEUTRAL_PROBLEM_SIZE); 


    auto ref = task.time_dynamic_programming_by_price();

    for (int i = 0; i < REPEAT; i++) {
        std::vector<std::pair<int,double>> record;
        record.emplace_back(ref);
        // max_steps, starting_temp, frozen_const, equlibrium_const, cooling_koef
        record.emplace_back(task.time_annealing(SA_MAX_STEPS, SA_START_TEMP,
                    SA_FROZEN_CONST, SA_EQULIBRIUM_CONST, SA_COOLING_KOEF));

        collector.add_record(record[0].first, record);
    }

    collector.print_result(std::cerr);
    

    return 0;
}
