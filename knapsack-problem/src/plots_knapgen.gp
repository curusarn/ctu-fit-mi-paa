
set terminal png size 800,600 enhanced font "Arial,12"
# set termoption ps 1
set key box 1
set key vert
set grid

# all files have following format:
# parameter  avg_miss avg_time  max_miss max_time
# 1          2        3         4        5
# 1          6        7         8        9
# 1          10       11        12       13
# 1          14       15        16       17

# time

set output 'plots/time_knapgen_max_weight.png'
set title "CPU time comparison (relative to maximal weight)"
set xlabel "Maximal item weight"
set ylabel "Time [seconds]"
set logscale y
set key at graph 0.42,0.85

plot\
    'results/knapgen_max_weight.txt' using 1:3 title 'Bruteforce' pt 7, \
    'results/knapgen_max_weight.txt' using 1:7 title 'Branch and bound' pt 7, \
    'results/knapgen_max_weight.txt' using 1:11 title 'Dynamic programming' pt 7, \
    'results/knapgen_max_weight.txt' using 1:15 title 'Heuristic' pt 7


set output 'plots/time_knapgen_max_price.png'
set title "CPU time comparison (relative to maximal price)"
set xlabel "Maximal item price"
set ylabel "Time [seconds]"
set logscale y

plot\
    'results/knapgen_max_price.txt' using 1:3 title 'Bruteforce' pt 7, \
    'results/knapgen_max_price.txt' using 1:7 title 'Branch and bound' pt 7, \
    'results/knapgen_max_price.txt' using 1:11 title 'Dynamic programming' pt 7, \
    'results/knapgen_max_price.txt' using 1:15 title 'Heuristic' pt 7


set output 'plots/time_knapgen_ratio.png'
set title "CPU time comparison (relative to capacity to total weight ratio)"
set xlabel "Capacity : total weight "
set ylabel "Time [seconds]"
set logscale y
set logscale x 2

plot\
    'results/knapgen_ratio.txt' using 1:3 title 'Bruteforce' pt 7, \
    'results/knapgen_ratio.txt' using 1:7 title 'Branch and bound' pt 7, \
    'results/knapgen_ratio.txt' using 1:11 title 'Dynamic programming' pt 7, \
    'results/knapgen_ratio.txt' using 1:15 title 'Heuristic' pt 7


set output 'plots/time_knapgen_granularity_small.png'
set title "CPU time comparison - more SMALL items (relative to granularity exponent)"
set xlabel "Granularity exponent"
set ylabel "Time [seconds]"
set logscale y
unset logscale x

plot\
    'results/knapgen_granularity_small.txt' using 1:3 title 'Bruteforce' pt 7, \
    'results/knapgen_granularity_small.txt' using 1:7 title 'Branch and bound' pt 7, \
    'results/knapgen_granularity_small.txt' using 1:11 title 'Dynamic programming' pt 7, \
    'results/knapgen_granularity_small.txt' using 1:15 title 'Heuristic' pt 7


set output 'plots/time_knapgen_granularity_big.png'
set title "CPU time comparison - more BIG items (relative to granularity exponent)"
set xlabel "Granularity exponent"
set ylabel "Time [seconds]"
set logscale y

plot\
    'results/knapgen_granularity_big.txt' using 1:3 title 'Bruteforce' pt 7, \
    'results/knapgen_granularity_big.txt' using 1:7 title 'Branch and bound' pt 7, \
    'results/knapgen_granularity_big.txt' using 1:11 title 'Dynamic programming' pt 7, \
    'results/knapgen_granularity_big.txt' using 1:15 title 'Heuristic' pt 7




set key default
set key box 1
set key vert
set key right top
# miss

set output 'plots/miss_knapgen_max_weight.png'
set title "Heuristic relative mistake (relative to maximal weight)"
set xlabel "Maximal item weight"
set ylabel "Relative mistake"
unset logscale x
unset logscale y

plot\
    'results/knapgen_max_weight.txt' using 1:14 title 'average' pt 7 lc rgb 'blue', \
    'results/knapgen_max_weight.txt' using 1:16 title 'maximal' pt 9 lc rgb 'red'


set output 'plots/miss_knapgen_max_price.png'
set title "Heuristic relative mistake (relative to maximal price)"
set xlabel "Maximal item price"
set ylabel "Relative mistake"

plot\
    'results/knapgen_max_price.txt' using 1:14 title 'average' pt 7  lc rgb 'blue', \
    'results/knapgen_max_price.txt' using 1:16 title 'maximal' pt 9  lc rgb 'red'


set output 'plots/miss_knapgen_ratio.png'
set title "Heuristic relative mistake (relative to capacity to total weight ratio)"
set xlabel "Capacity : total weight "
set ylabel "Relative mistake"
set logscale x 2

plot\
    'results/knapgen_ratio.txt' using 1:14 title 'average' pt 7 lc rgb 'blue', \
    'results/knapgen_ratio.txt' using 1:16 title 'maximal' pt 9 lc rgb 'red'


set output 'plots/miss_knapgen_granularity_small.png'
set title "Heuristic relative mistake - more SMALL items (relative to granularity exponent)"
set xlabel "Granularity exponent"
set ylabel "Relative mistake"
unset logscale x 
unset logscale y 

plot\
    'results/knapgen_granularity_small.txt' using 1:14 title 'average' pt 7 lc rgb 'blue', \
    'results/knapgen_granularity_small.txt' using 1:16 title 'maximal' pt 9 lc rgb 'red'


set output 'plots/miss_knapgen_granularity_big.png'
set title "Heuristic relative mistake - more BIG items (relative to granularity exponent)"
set xlabel "Granularity exponent"
set ylabel "Relative mistake"

plot\
    'results/knapgen_granularity_big.txt' using 1:14 title 'average' pt 7 lc rgb 'blue', \
    'results/knapgen_granularity_big.txt' using 1:16 title 'maximal' pt 9 lc rgb 'red'



#results/knapgen_granularity_big.txt
#results/knapgen_granularity_small.txt
#results/knapgen_max_price.txt
#results/knapgen_max_weight.txt
#results/knapgen_ratio.txt
