
#include <cassert>
#include <iostream>
#include "record_collector.h"

double RecordCollector::relative_miss(double optimal, double approx) {
    return (optimal - approx) / optimal;
}

void RecordCollector::add_record(int ref_price,
                                 int bf_price, double bf_time,
                                 int he_price, double he_time) {
    assert(ref_price == bf_price);
   
    count += 1;
    double he_miss = relative_miss(ref_price, he_price); 

    heuristic_miss += he_miss;
    bruteforce_time += bf_time;
    heuristic_time += he_time;

    if (he_miss > max_heuristic_miss) max_heuristic_miss = he_miss;
    if (bf_time > max_bruteforce_time) max_bruteforce_time = bf_time;
    if (he_time > max_heuristic_time) max_heuristic_time = he_time;
}

void RecordCollector::print_result(std::ostream & os) {
    os << problem_category << " "  
       << (heuristic_miss / count) << " " 
       << (bruteforce_time / count) << " " 
       << (heuristic_time / count) << " " 
       << max_heuristic_miss << " " 
       << max_bruteforce_time << " " 
       << max_heuristic_time << " " << std::endl;
}
