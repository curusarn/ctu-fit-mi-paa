
#include <cassert>
#include <iostream>
#include "record_collector.h"

double RecordCollector::relative_miss(double optimal, double approx) {
    return (optimal - approx) / optimal;
}


void RecordCollector::add_record(int ref_price,
                            const std::vector<std::pair<int,double>> & record) {
     
    assert(record.size() > 0);
    assert(ref_price == record[0].first);
    assert(record.size() == methods.size());
    count += 1;
   
    for (uint i = 0; i < record.size(); i++) {
        int price = record[i].first;
        double time = record[i].second;
        double miss = relative_miss(ref_price, price);
        methods[i].miss += miss;
        methods[i].time += time;
        methods[i].max_miss = std::max(methods[i].max_miss, miss);
        methods[i].max_time = std::max(methods[i].max_time, time);
    }
    //std::cerr << problem_category << " progress: " << count << " / ?50?" << std::endl;
}

void RecordCollector::print_result(std::ostream & os) {
    os << problem_category << " ";
    
    for (uint i = 0; i < methods.size(); i++) {
        os << (methods[i].miss / count) << " "
           << (methods[i].time / count) << " " 
           << methods[i].max_miss << " " 
           << methods[i].max_time << "   "; 
    }

    os << std::endl;
}

RecordCollector::RecordCollector(int pr_cat, int method_cnt)
                                                : problem_category(pr_cat) {
    methods.resize(method_cnt);
}

