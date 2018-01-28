
#include <vector>
#include <ostream>
#include <string>


class RecordCollector {

    double miss = 0;
    double time = 0;
    double max_miss = 0;
    double max_time = 0;

    long int count = 0;
    
    static double relative_miss(double optimal, double approx);

public:
    RecordCollector() = default;
    void add_record(int ref_price, const std::pair<int,double> & rec);
    void print_result(std::ostream & os);
};
