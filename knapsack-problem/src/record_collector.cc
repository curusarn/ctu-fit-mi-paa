
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
                            const std::vector<std::pair<int,double>> & record) {
     
    assert(record.size() > 0);
    assert(record.size() == measurements.size());
    count += 1;
   
    for (uint i = 0; i < record.size(); i++) {
        int price = record[i].first;
        double time = record[i].second;
        double miss = relative_miss(ref_price, price);
        measurements[i].miss += miss;
        measurements[i].time += time;
        measurements[i].max_miss = std::max(measurements[i].max_miss, miss);
        measurements[i].max_time = std::max(measurements[i].max_time, time);
    }
    //std::cerr << heading << " progress: " << count << " / ?50?" << std::endl;
}


void RecordCollector::print_result(std::ostream & os) {
    os << heading << " ";
    
    for (uint i = 0; i < measurements.size(); i++) {
        double m = (measurements[i].miss / count);
        os << m << " "
           << (measurements[i].time / count) << " " 
           << measurements[i].max_miss << " " 
           << measurements[i].max_time << "   "; 
    }

    os << std::endl;
}

RecordCollector::RecordCollector(double head, int measurement_cnt)
                                                    : heading(head) {
    measurements.resize(measurement_cnt);
}

