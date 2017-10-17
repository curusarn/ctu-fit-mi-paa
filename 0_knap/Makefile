
files=main.cc task.cc record_collector.cc item_solution.cc
command=./main.out 4 10 15 20 22 25 27 30 32 35 37 40

valgrind:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && valgrind ${command} 

O2:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && ${command}

O3:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O3 -o main.out ${files} && ${command}

Ofast:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -Ofast -o main.out ${files} && ${command}
