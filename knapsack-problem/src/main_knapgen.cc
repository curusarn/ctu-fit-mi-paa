
#include <iostream>
#include <vector>
#include <cassert>
#include <limits.h>
#include "task.h" 
#include "record_collector.h" 

#include "knapgen/knapcore.h"


#define uint unsigned int
#define NEUTRAL_WEIGTH 100
#define NEUTRAL_PRICE 100
#define NEUTRAL_RATIO 0.65  
#define NEUTRAL_GRANULARITY 0 

#define X_VALUES 42
#define REPEAT 100 
#define MIN_PROBLEM_SIZE 5 
#define MAX_PROBLEM_SIZE 24 


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
    int n = pr_size % (MAX_PROBLEM_SIZE - MIN_PROBLEM_SIZE) + MIN_PROBLEM_SIZE;
    std::vector<int> weights(n);
    std::vector<int> costs(n);

    // I would like to use this moment to say thanks to C++11 and to it's 
    //      std::vector.data() method for keeping my code "malloc-less".
    int total_weight = knapcore(weights.data(), costs.data(), n, 
                            max_weight, max_price, gran_exp, granularity);

    int capacity = cap_sum_ratio * total_weight;

    return Task(capacity, weights, costs);
}

std::vector<std::pair<int,double>> time_all_methods(Task & task) {
    std::vector<std::pair<int,double>> record;

    record.emplace_back(task.time_bruteforce());

    record.emplace_back(task.time_branch_and_bound());

    record.emplace_back(task.time_dynamic_programming_by_price());

    record.emplace_back(task.time_heuristic());

    return record;
}

int main(int argc, char * argv[]){
    srand (time(NULL));


    std::cout << "PARAMETER (miss time max_miss max_time)"
              << " bruteforce branch_&_bound dynamic_programming heuristic"
              << std::endl;

    //std::cout << "parameter: "
    //          << "0: max_weight"
    //          << "1: max_weight"
    //          << "0: max_weight"
    //          << "0: max_weight"
    //          << std::endl;

    // max weigth
    std::cout << "MAX WEIGTH" << std::endl;
    for (int i = 1; i < X_VALUES; i++) {
        int x = 10 * i + 20;
        RecordCollector collector(x, 4);

        for (int j = 0; j < REPEAT; j++) { 
            auto task = knapgen(x, NEUTRAL_PRICE,
                                NEUTRAL_RATIO, NEUTRAL_GRANULARITY,
                                NEUTRAL_GRANULARITY, j); 
            auto record = time_all_methods(task);
            collector.add_record(record[0].first, record);
        }

        collector.print_result(std::cout);
    }

    // max price
    std::cout << "MAX PRICE" << std::endl;
    for (int i = 1; i < X_VALUES; i++) {
        int x = 10 * i + 20;
        RecordCollector collector(x, 4);

        for (int j = 0; j < REPEAT; j++) { 
            auto task = knapgen(NEUTRAL_WEIGTH, x, 
                                NEUTRAL_RATIO, NEUTRAL_GRANULARITY,
                                NEUTRAL_GRANULARITY, j); 
            auto record = time_all_methods(task);
            collector.add_record(record[0].first, record);
        }

        collector.print_result(std::cout);
    }

    // capacity to total_price ratio
    std::cout << "CAPACITY : TOTAL_PRICE (ratio)" << std::endl;
    double x = 1.0/200;
    for (int i = 1; i < X_VALUES; i++) {
        x *= 1.154;
        RecordCollector collector(x, 4);

        for (int j = 0; j < REPEAT; j++) { 
            auto task = knapgen(NEUTRAL_WEIGTH, NEUTRAL_PRICE, 
                                x, NEUTRAL_GRANULARITY,
                                NEUTRAL_GRANULARITY, j); 
            auto record = time_all_methods(task);
            collector.add_record(record[0].first, record);
        }

        collector.print_result(std::cout);
    }

    // granularity 
    for (int y = -1; y < 2; y += 2) {
        std::cout << "GRANULARITY " << ((y == -1) ? "SMALLER ITEMS" : "BIGGER ITEMS") << std::endl;
        x = 2;
        for (int i = 1; i < X_VALUES; i++) {
            x -= 0.048;
            RecordCollector collector(x, 4);

            for (int j = 0; j < REPEAT; j++) { 
                auto task = knapgen(NEUTRAL_WEIGTH, NEUTRAL_PRICE, 
                                    NEUTRAL_RATIO, x, y, j); 
                auto record = time_all_methods(task);
                collector.add_record(record[0].first, record);
            }

            collector.print_result(std::cout);
        }
    }
    return 0;
}
