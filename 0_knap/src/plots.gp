#
# simple plotting
# set title "Relative mistake for knapsack problem"
# plot 'results.txt'                                # assumes col1=x, col2=y; shows '+' at data points
# plot '2col.dat' with lines                     # connect points with a line
# plot '2col.dat' with linespoints               # line and points
# plot '2col.dat' with points                    # just points (default)

# plot a subset of the data
# plot[1:5] '2col.dat' with linespoints          # plot the first 5 elements
# plot[3:7] '2col.dat' with linespoints          # plot only elements 3 thru 7

# add a title to your line
# plot '2col.dat' with lines title 'my curve'    # this is really the line-title in the legend

# map the columns to the x- and y-axes
# plot '2col.dat' using 1:2                      # 1=x, 2=y (this is the default)
# plot '2col.dat' using 2:1                      # 2=x, 1=y (reverse the graph)

# abbreviations

set terminal png size 800,600 enhanced font "Arial,16"
# set termoption ps 1
set key box 1
set grid

set output 'plots/miss_he.png'
set title "Relative mistake - heuristic"
set xlabel "Problem size"
set ylabel "Relative mistake"

plot\
    'results.txt' using 1:5 title 'maximal' pt 9 lc rgb 'red',\
    'results.txt' using 1:2 title 'average' pt 7 lc rgb 'blue'


set output 'plots/time_bf.png'
set title "CPU time - bruteforce"
set ylabel "Time [seconds]"
set logscale y
set key left top
plot\
    'results.txt' using 1:6 title 'maximal' pt 9 lc rgb 'red',\
    'results.txt' using 1:3 title 'average' pt 7 lc rgb 'blue'

set output 'plots/time_both.png'
set title "CPU time - comparison" 
plot\
    'results.txt' using 1:3 title 'bruteforce average' pt 7 lc rgb 'green',\
    'results.txt' using 1:4 title 'heuristic average' pt 7 lc rgb 'black'

unset logscale y
set output 'plots/time_he.png'
set title "CPU time - heuristic"
plot\
    'results.txt' using 1:7 title 'maximal' pt 9 lc rgb 'red',\
    'results.txt' using 1:4 title 'average' pt 7 lc rgb 'blue'

