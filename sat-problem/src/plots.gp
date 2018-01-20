
# GENERAL SETTINGS

set terminal png size 1200,600 enhanced font "Arial,12"
# set termoption ps 1
set key box 1
set grid


# FIRST SUBMISSION

set output '/tmp/sat_plot.png'
set title "Simulated annealing"
set ylabel "price and temp"
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

set output '/tmp/sat_plot_price_only.png'
set ylabel "price"

plot\
    '/tmp/sat.txt' using 1:2 notitle pt 0 lc rgb 'blue',\
