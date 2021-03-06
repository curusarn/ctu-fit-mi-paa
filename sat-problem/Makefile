SHELL=/bin/bash

files=src/main.cc src/task.cc src/record_collector.cc
command=./main.out

run: compile _run

compile:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main.out ${files}

run10: compile
	for i in {1..10}; do make _run; done

run_debug: compile 
	${command}

run_noplot: compile 
	${command} > /dev/null

_run:
	${command} > /tmp/sat.txt
	gnuplot -c src/plots.gp
	feh /tmp/sat_plot_fitness.png &

report:
	grip REPORT.md localhost:6420 --title="MI-PAA - SAT problem"

pdf:
	grip REPORT_br.md localhost:6420 --title="MI-PAA - SAT problem" &
	sleep 5 
	wkhtmltopdf http://localhost:6420 letsimon-fit-cvut-mi-paa-sat.pdf
	pkill grip

pdf_knapgen: plot_knapgen pdf

tar:
	tar -zcvf letsimon-fit-cvut-mi-paa-sat.tar.gz src/* Makefile

deps:
	#Deps: gcc, gnuplot, tar, wkhtmltopdf, grip (from pip)

clean:
	-rm *.png *.pdf *.tar *.out

.PHONY: clean deps tar O2 valgrind O3 Ofast pdf plot results knapgen results_knapgen

.SILENT: _annealing annealing10 
