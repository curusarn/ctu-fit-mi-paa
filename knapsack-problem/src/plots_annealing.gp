
# GENERAL SETTINGS

set terminal png size 800,600 enhanced font "Arial,12"
# set termoption ps 1
set key box 1
set grid


# FIRST SUBMISSION

set output '/tmp/annealing_plot.png'
set title "Simulated annealing"
set ylabel "price and temp"
set xlabel "steps"
#set logscale y

set key left top

plot\
    '/tmp/annealing.txt' using 1:2 title 'price (BLUE)' pt 0 lc rgb 'blue',\
    '/tmp/annealing.txt' using 1:3 title 'temp (RED)' pt 0 lc rgb 'red'

set output '/tmp/annealing_plot_price_only.png'
set ylabel "price"

plot\
    '/tmp/annealing.txt' using 1:2 notitle pt 0 lc rgb 'blue',\
