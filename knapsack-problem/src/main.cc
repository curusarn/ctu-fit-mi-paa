
#include <iostream>
#include <vector>
#include <cassert>
#include "task.h" 
#include "record_collector.h" 


#define uint unsigned int

const char* DATA_PATH = "data/";
const int BF_LIMIT = 24;

std::string instance_path(uint problem_category) {
    return std::string(DATA_PATH) + "knap_" +
           std::to_string(problem_category) + ".inst.dat";
}

std::string solution_path(uint problem_category) {
    return std::string(DATA_PATH) + "knap_" +
           std::to_string(problem_category) + ".sol.dat";
}

int main(int argc, char * argv[]){
    if (argc < 2) {
        std::cout << "ERR: Not enough arguments" << std::endl;
        return 1;
    }

    std::cout << "problem_category he_relative_miss avg_bf_time avg_he_time"
        " max_he_relative_miss max_bf_time max_he_time" << std::endl;
    for (int i = 1; i < argc; i++) {
        int problem_category = std::stoi(argv[i]);

        std::ifstream infile_inst(instance_path(problem_category));
        std::vector<Task> tasks = parse<Task>(infile_inst);
        std::ifstream infile_sol(solution_path(problem_category));
        std::vector<Solution> solutions = parse<Solution>(infile_sol);
        
        assert(tasks.size() == solutions.size());

        RecordCollector collector(problem_category);

        for (uint j = 0; j < tasks.size(); j++) {
            double ref = solutions[j].get_total_price();

            auto he = tasks[j].time_heuristic();
            std::pair<int, double> bf 
                = (problem_category < BF_LIMIT) 
                ? tasks[j].time_bruteforce() 
                : std::pair<int, double>(ref, -0.9);
            
            collector.add_record(ref, bf.first, bf.second, he.first, he.second);
        }

        collector.print_result(std::cout);
    }

    return 0;
}
