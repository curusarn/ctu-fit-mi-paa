
#include <vector>
#include <ostream>
#include <string>

class RecordCollector {

    struct Method {
        double miss = 0;
        double time = 0;
        double max_miss = 0;
        double max_time = 0;
    };

    const int problem_category;
    double bruteforce_time = 0;
    std::vector<Method> methods;

    double max_bruteforce_time = 0;
    int count = 0;
    
    static double relative_miss(double optimal, double approx);

public:
    RecordCollector(int pr_cat, int method_cnt);
    void add_record(int ref_price, const std::vector<std::pair<int,double>> & rec);
    void print_result(std::ostream & os);
};
