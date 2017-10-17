
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
    bruteforce_time += bf_time;
    heuristic_time += he_time;
    heuristic_miss += relative_miss(ref_price, he_price); 
}

void RecordCollector::print_result(std::ostream & os) {
    os << problem_category << " "  
       << (heuristic_miss / count) << " " 
       << (bruteforce_time / count) << " " 
       << (heuristic_time / count) << " " << std::endl;
}
