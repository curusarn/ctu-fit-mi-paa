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
set output 'relative_miss.png'
plot 'results.txt' u 1:2:5 title 'Mistake'      # 'u' - using, 'w l' - with lines

set output 'time.png'
plot 'results.txt' u 1:3 title 'Time'      # 'u' - using, 'w l' - with lines
# Example of using histogram modes
#
