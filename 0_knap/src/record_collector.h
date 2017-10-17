
#include <vector>
#include <ostream>
#include <string>

class RecordCollector {

    const int problem_category;
    double bruteforce_time = 0;
    double heuristic_time = 0;
    double heuristic_miss = 0;
    int count = 0;
    
    static double relative_miss(double optimal, double approx);

public:
    RecordCollector(int pr_cat) : problem_category(pr_cat) {};
    void add_record(int ref_price,
                    int bf_price, double bf_time,
                    int he_price, double he_time);
    void print_result(std::ostream & os);
};
