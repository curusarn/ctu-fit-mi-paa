SHELL=/bin/bash

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

results:
	cat results/all.txt | tr -s ' ' > results/trim_all.txt
	cat results/trim_all.txt | cut -d' ' -f1,2-5 | grep -v -- '-42' > results/bf.txt
	cat results/trim_all.txt | cut -d' ' -f1,6-9 > results/bb.txt
	cat results/trim_all.txt | cut -d' ' -f1,10-13 > results/he.txt
	cat results/trim_all.txt | cut -d' ' -f1,14-17 > results/dp.txt
	cat results/trim_all.txt | cut -d' ' -f1,18-21 > results/fp_0.1.txt
	cat results/trim_all.txt | cut -d' ' -f1,22-25 > results/fp_0.3.txt
	cat results/trim_all.txt | cut -d' ' -f1,26-29 > results/fp_0.5.txt
	cat results/trim_all.txt | cut -d' ' -f1,30-34 > results/fp_0.01.txt

plot: results
	gnuplot -c src/plots.gp 

pdf: src/plots.gp
	grip README.md localhost:6420 --title="MI-PAA - Knapsack problem" &
	sleep 10
	wkhtmltopdf http://localhost:6420 letsimon-fit-cvut-mi-paa-0_knap.pdf
	pkill grip

tar:
	tar -zcvf letsimon-fit-cvut-mi-paa-0_knap.tar.gz src/* Makefile

deps:
	#Deps: gcc, gnuplot, tar, wkhtmltopdf, grip (from pip)

clean:
	-rm *.png *.pdf *.tar *.out

.PHONY: clean deps tar O2 valgrind O3 Ofast pdf plot results
