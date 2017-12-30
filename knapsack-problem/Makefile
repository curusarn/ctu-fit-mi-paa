SHELL=/bin/bash

files=src/main.cc src/task.cc src/record_collector.cc src/item_solution.cc
files_fptas=src/main_fptas.cc src/task.cc src/record_collector.cc src/item_solution.cc
files_knapgen=src/main_knapgen.cc src/task.cc src/record_collector.cc src/item_solution.cc src/knapgen/knapcore.c
files_annealing=src/main_annealing.cc src/task.cc src/record_collector.cc src/item_solution.cc src/knapgen/knapcore.c
command=./main.out 4 10 15 20 22 25 27 30 32 35 37 40
command_knapgen=./main.out
command_annealing=./main.out


O2:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && ${command}

valgrind:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files} && valgrind ${command} 

O3:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O3 -o main.out ${files} && ${command}

Ofast:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -Ofast -o main.out ${files} && ${command}

fptas:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files_fptas} && ${command}

knapgen:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files_knapgen} && ${command_knapgen}

annealing:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files_annealing} && ${command_annealing} > /tmp/annealing.txt
	gnuplot -c src/plots_annealing.gp
	feh /tmp/annealing_plot.png &

annealing10:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files_annealing}
	for i in {1..10}; do make _annealing; done

_annealing:
	${command_annealing} > /tmp/annealing.txt
	gnuplot -c src/plots_annealing.gp
	feh /tmp/annealing_plot.png &

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

results_knapgen:
	cat results/knapgen.txt | tr -s ' ' > results/trim_knapgen.txt
	cat results/trim_knapgen.txt | head -n 42 | tail -n 41 > results/knapgen_max_weight.txt
	cat results/trim_knapgen.txt | head -n 84 | tail -n 41 > results/knapgen_max_price.txt
	cat results/trim_knapgen.txt | head -n 126 | tail -n 41 > results/knapgen_ratio.txt
	cat results/trim_knapgen.txt | head -n 168 | tail -n 41 > results/knapgen_granularity_small.txt
	cat results/trim_knapgen.txt | tail -n 41 > results/knapgen_granularity_big.txt

plot: results
	gnuplot -c src/plots.gp 

plot_knapgen: results_knapgen
	gnuplot -c src/plots_knapgen.gp 


pdf: plot
	grip README_br.md localhost:6420 --title="MI-PAA - Knapsack problem" &
	sleep 5 
	wkhtmltopdf http://localhost:6420 letsimon-fit-cvut-mi-paa-1_knap.pdf
	pkill grip

pdf_knapgen: plot_knapgen 
	grip REPORT_br.md localhost:6420 --title="MI-PAA - Knapsack problem" &
	sleep 5 
	wkhtmltopdf http://localhost:6420 letsimon-fit-cvut-mi-paa-2_knap.pdf
	pkill grip

tar:
	tar -zcvf letsimon-fit-cvut-mi-paa-2_knap.tar.gz src/* Makefile

deps:
	#Deps: gcc, gnuplot, tar, wkhtmltopdf, grip (from pip)

clean:
	-rm *.png *.pdf *.tar *.out

.PHONY: clean deps tar O2 valgrind O3 Ofast pdf plot results knapgen results_knapgen

.SILENT: _annealing annealing10 
