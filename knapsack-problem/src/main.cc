
#include <iostream>
#include <vector>
#include <cassert>
#include "task.h" 
#include "record_collector.h" 


#define uint unsigned int


const char* DATA_PATH = "data/";
const int BF_LIMIT = 26;

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

    std::cout << "problem_category (miss time max_miss max_time) "
              << " * (bruteforce branchbound heuristic)" << std::endl;
    for (int i = 1; i < argc; i++) {
        int problem_category = std::stoi(argv[i]);

        std::ifstream infile_inst(instance_path(problem_category));
        std::vector<Task> tasks = parse<Task>(infile_inst);
        std::ifstream infile_sol(solution_path(problem_category));
        std::vector<Solution> solutions = parse<Solution>(infile_sol);
        
        assert(tasks.size() == solutions.size());

        RecordCollector collector(problem_category, 3);

        for (uint j = 0; j < tasks.size(); j++) {
            std::vector<std::pair<int,double>> record;

            int ref = solutions[j].get_total_price();

            record.emplace_back((problem_category < BF_LIMIT) 
                                ? tasks[j].time_bruteforce() 
                                : std::pair<int, double>(ref, -42));

            record.emplace_back((problem_category < BF_LIMIT) 
                                ? tasks[j].time_branch_and_bound() 
                                : std::pair<int, double>(ref, -42));

            record.emplace_back(tasks[j].time_heuristic());
            
            collector.add_record(ref, record);
        }

        collector.print_result(std::cout);
    }

    return 0;
}
