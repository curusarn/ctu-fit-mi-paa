
files=src/main.cc src/task.cc src/record_collector.cc src/item_solution.cc
command=./main.out 4 10 15 20 22 25 27 30 32 35 37 40


O2:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && ${command}

valgrind:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && valgrind ${command} 

O3:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O3 -o main.out ${files} && ${command}

Ofast:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -Ofast -o main.out ${files} && ${command}

plot:
	gnuplot -c src/relative_miss.gp 
