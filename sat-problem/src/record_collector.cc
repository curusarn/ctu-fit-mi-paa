
#include <cassert>
#include <cmath>
#include <iostream>
#include "record_collector.h"

double RecordCollector::relative_miss(double optimal, double approx) {
    if (optimal == approx) return 0;
    assert(optimal != 0.0);
    return (optimal - approx) / optimal;
}


void RecordCollector::add_record(int ref_price,
                                 const std::pair<int,double> & record) {
    count += 1;
   
    long int price = record.first;
    double t = record.second;
    double m = relative_miss(ref_price, price);
    time += t;
    miss += m;
    max_time = std::max(max_time, t);
    max_miss = std::max(max_miss, m);
    //std::cerr << heading << " progress: " << count << " / ?50?" << std::endl;
}


void RecordCollector::print_result(std::ostream & os) {
     
    double m = (miss / count);
    os << m << " "
       << (time / count) << " " 
       << max_miss << " " 
       << max_time << "   "; 

    os << std::endl;
}


