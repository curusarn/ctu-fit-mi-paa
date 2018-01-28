
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <limits.h>
#include <random>
#include <cmath>
#include "task.h"

#define REF_FITNESS_KOEF 1

int _add_or_delete(uint id, std::vector<bool> & bitset) {
    bitset[id] = !bitset[id]; 
    return (bitset[id]) ? 1 : -1;
}


bool _is_sat(const Clause & clause, const std::vector<bool> & bitset) {
    for (auto& var : clause) 
        if (var.first ^ bitset[var.second]) return true;
    return false;
}

uint Task::no_sat_clauses(const std::vector<bool> & bitset) {
    uint count = 0;

    for (auto& clause : clauses) 
        if (_is_sat(clause, bitset)) count++;
    return count;
}

int Task::get_theoretical_best(double fitness_koef) {
    int sum_all_weights = 0; // this will be used to count fitness
    for (int w : weights)
        sum_all_weights += w;
    int ref_fitness_koef = int(sum_all_weights * REF_FITNESS_KOEF); 
    return (clauses.size() * ref_fitness_koef + sum_all_weights);
}

// simulated annealing

bool _use_new_solution(int old_price, int new_price, double temp, double rand) {
    if (new_price > old_price)
        return true;
    return rand < std::exp( +(new_price - old_price) / temp);
}

double _fitness(double weight_sum, uint no_sat_clauses, double koef) {
    //assert(weight_sum < (no_sat_clauses + 1) * koef);
    // more sat clauses is better than greater weight sum
    
    return weight_sum + no_sat_clauses * koef;
}

int Task::solve_annealing(int max_steps, double starting_temp,
                          int frozen_const, int equlibrium_const,
                          double cooling_koef, int neighbour_const,
                          double fitness_koef) {
    std::random_device rd;  //Used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> rand_prob(0, 1.0);
    std::uniform_int_distribution<> rand_var(0, weights.size() - 1);
    std::uniform_int_distribution<> 
                            rand_bit_cnt(0, neighbour_const);

    std::vector<bool> curr_bitset(weights.size(), false); 
    // maybe start with all true?

    // get fitness koef
    int sum_all_weights = 0; // this will be used to count fitness
    for (int w : weights)
        sum_all_weights += w;
    //int abs_fitness_koef = int(sum_all_weights * fitness_koef); 
    int abs_fitness_koef = int(fitness_koef); 

    uint curr_nsat = no_sat_clauses(curr_bitset); // number of sat clauses
    int curr_wsum = 0; // sum of weights
    int curr_fitness = _fitness(curr_wsum, curr_nsat, abs_fitness_koef);

    double temp = starting_temp;

    int steps_wo_new_state = 0; // frozen
    //int no_new_states = 0; // equlibrium
    int steps_since_cooling = 0; // equlibrium
    for (int i = 0; i < max_steps; i++) {
        std::cout << i << " " << curr_fitness << " " << temp 
                  << " " << (curr_nsat * abs_fitness_koef) 
                  << " " << curr_wsum
                  << " " << (clauses.size() * abs_fitness_koef + sum_all_weights) 
                  << " " << (clauses.size() * abs_fitness_koef) 
                  << " " << sum_all_weights << std::endl;
        steps_since_cooling++;

        if (steps_wo_new_state > frozen_const) {
            //std::cerr << "FROZEN" << std::endl;
            break; // frozen
        }
        
        if (steps_since_cooling > equlibrium_const) {
            temp *= cooling_koef;
            steps_since_cooling = 0;
        }
        
        // get neighbour
        uint bit_cnt = rand_bit_cnt(gen);
        auto var_ids = std::vector<uint>();
        var_ids.reserve(bit_cnt);

        uint new_nsat;
        int new_wsum = curr_wsum;
        int new_fitness;
        for (uint j = 0; j < bit_cnt; j++) { 
            int var_id = rand_var(gen);
            //std::cout << " @@@" << var_id;
            var_ids.push_back(var_id);
            int sign = _add_or_delete(var_id, curr_bitset);
            new_wsum += weights[var_id] * sign;
        }
        std::cout << std::endl;
        new_nsat = no_sat_clauses(curr_bitset); 
        new_fitness = _fitness(new_wsum, new_nsat, abs_fitness_koef); 

        if (new_fitness > curr_fitness) {
            curr_wsum = new_wsum;
            curr_nsat = new_nsat;
            curr_fitness = new_fitness;

            steps_wo_new_state = 0;

            continue;
        }

        // try solution
        if (_use_new_solution(curr_fitness, new_fitness,
                              temp, rand_prob(gen))) {
            curr_wsum = new_wsum;
            curr_nsat = new_nsat;
            curr_fitness = new_fitness;

            steps_wo_new_state = 0;
        }
        else {
            // revert add_or_delete
            for (uint j = 0; j < var_ids.size(); j++)  
                _add_or_delete(var_ids[j], curr_bitset);

            steps_wo_new_state++;
        }
    }

    int ref_fitness_koef = int(sum_all_weights * REF_FITNESS_KOEF); 
    return ref_fitness_koef * curr_nsat + curr_wsum;
}

void Task::print() {
    std::cerr << "TASK: " << std::endl;
    for (uint i = 0; i < weights.size(); i++) 
        std::cerr << weights[i] << std::endl;
    std::cerr << std::endl;
    for (uint i = 0; i < clauses.size(); i++) 
        for (uint j = 0; j < clauses[i].size(); j++) {
            std::cerr << " " << (clauses[i][j].first ? "-" : "+")
                      << clauses[i][j].second;
        }
    std::cerr << std::endl;
}

void Task::print(const std::vector<bool> & bitset) {
    std::cerr << "TASK: " << std::endl;
    for (uint i = 0; i < weights.size(); i++) 
        std::cerr << i << ": " 
                  << weights[i] << " -> " 
                  << bitset[i] << std::endl;
    std::cerr << std::endl;
    for (uint i = 0; i < clauses.size(); i++) {
        for (uint j = 0; j < clauses[i].size(); j++) {
            std::cerr << " " << (clauses[i][j].first ? "-" : "+")
                      << clauses[i][j].second;
        }
        std::cerr << " -> ";
        for (uint j = 0; j < clauses[i].size(); j++) {
            std::cerr << " " 
                      << (clauses[i][j].first ^ bitset[clauses[i][j].second])
                      << "(" << bitset[clauses[i][j].second] << ")";
        }
        std::cerr << std::endl;
    }
    std::cerr << std::endl;
}
