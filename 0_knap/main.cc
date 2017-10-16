#include <iostream>
#include <vector>
#include "task.h" 

#define uint unsigned int


//std::vector<std::string> get_tasks(std::string data_dir){
//    std::vector<std::string> tasks;
//    dir = opendir(data_dir);
//    while ((ent = readdir(dir)) != NULL) {
//        const std::string file_name = ent->d_name;
//        const std::string full_file_name = directory + "/" + file_name;
//
//        if (file_name[0] == '.')
//            continue;
//
//        const std::string &  = file_name.substr(file_name.length() - 4)
//
//         
//
//        
//        
//
//}



int main(int argc, char * argv[]){
    if (argc < 3) {
        std::cout << "ERR: Not enough arguments" << std::endl;
        return 1;
    }

    //std::cout << argv[1] << std::endl;
    
    std::ifstream infile(argv[1]);
    std::vector<Task> tasks = parse<Task>(infile);
    std::ifstream infile2(argv[2]);
    std::vector<Solution> solutions = parse<Solution>(infile2);
    tasks[0].print();
    //tasks[1].print();
    
    //test();

    auto solution0 = tasks[0].solve_bruteforce();
    //auto solution1 = tasks[1].solve_bruteforce();
    //solution0.print();
    solutions[0].print();

}
