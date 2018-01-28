
# GENERAL SETTINGS

set terminal png size 1200,600 enhanced font "Arial,12"
# set termoption ps 1
set key box 1
set grid


# FIRST SUBMISSION

set output '/tmp/sat_plot.png'
set title "Simulated annealing"
set ylabel "fitness and temp"
set xlabel "steps"
#set logscale y

set key outside 

plot\
    '/tmp/sat.txt' using 1:6 title 'max price' pt 0 lc rgb 'green',\
    '/tmp/sat.txt' using 1:7 title 'max sat price' pt 0 lc rgb 'green',\
    '/tmp/sat.txt' using 1:8 title 'max weights price' pt 0 lc rgb 'green',\
    '/tmp/sat.txt' using 1:2 title 'price (BLUE)' pt 0 lc rgb 'blue',\
    '/tmp/sat.txt' using 1:3 title 'temp (RED)' pt 0 lc rgb 'red',\
    '/tmp/sat.txt' using 1:4 title 'sat price (BLACK)' pt 0 lc rgb 'black',\
    '/tmp/sat.txt' using 1:5 title 'weights price (ORANGE)' pt 0 lc rgb 'orange'

set terminal png size 900,600 enhanced font "Arial,12"
unset key
set output '/tmp/sat_plot_fitness.png'
set title "Fitness (part1 + part2)"
set ylabel "total fitness"

plot\
    '/tmp/sat.txt' using 1:6 notitle pt 7 ps 0.1 lc rgb 'cyan',\
    '/tmp/sat.txt' using 1:2 notitle pt 0 lc rgb "#4B0082"

set output '/tmp/sat_plot_fitnessNsat.png'
set title "Fitness part2 (number of satisfied clauses times coefficient)"
set ylabel "number of satisfied clauses times coefficient"

plot\
    '/tmp/sat.txt' using 1:7 notitle pt 7 ps 0.1 lc rgb 'cyan',\
    '/tmp/sat.txt' using 1:4 notitle pt 0 lc rgb "#B22222"

set output '/tmp/sat_plot_fitnessWsum.png'
set title "Fitness part1 (sum of weights)"
set ylabel "sum of weights"

plot\
    '/tmp/sat.txt' using 1:8 notitle pt 7 ps 0.1 lc rgb 'cyan',\
    '/tmp/sat.txt' using 1:5 notitle pt 0 lc rgb "#000080"

