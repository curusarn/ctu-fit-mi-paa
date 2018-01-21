# MI-PAA - Boolean satisfiability problem
*Simon Let \<letsimon@fit.cvut.cz\>*

## Problem specification
The boolean satisfiability problem is the problem of determining if there exists an interpretation that satisfies a given Boolean formula.  REF ME
SAT is the first problem that was proven to be NP-complete. REF ME

Weighted SAT is variant of the problem where each variable has a given weight and you maximize sum of weight of variables that are true. FIX ME


Exact definition and instructions: https://edux.fit.cvut.cz/courses/MI-PAA/homeworks/05/start

## Possible solutions
- Bruteforce
- Simulated annealing
- Genetic algorithm
- Tabu search


## Solution overview
In this report, I will describe how I used **simulated annealing** to solve the **SAT problem**.


### Simulated annealing
Simulated annealing is a probabilistic technique for approximating the global optimum of a given function.<sup>[1]</sup>


“Annealing” refers to an analogy with thermodynamics, specifically with the way that metals cool and anneal. Simulated annealing uses the objective function of an optimization problem instead of the energy of a material.<sup>[2]</sup>

The algorithm is basically hill-climbing except instead of picking the best move, it picks a random move. If the selected move improves the solution, then it is always accepted. Otherwise, the algorithm makes the move anyway with some probability less than 1. The probability decreases exponentially with the “badness” of the move, which is the amount by which the solution is worsened (i.e., energy is increased.)<sup>[2]</sup> This probability decreases with time.

The algorithm is likely to accept "bad" solutions at first. But with time the algorithm is less and less likely to accept "bad" solutions. In the end, the algorithm accepts almost only better solutions.

## Algorithm description

### Simulated annealing


The algorithm consists of a predefined number of individual steps.  
Each step consists of following:

1. Getting a new candidate solution by inverting N bits from current solution.

1. Checking if the new candidate solution total weight is not greater than capacity.

1. Using the new candidate solution if either the new solution is better (greater total price) than the old one OR if a random number between 0 and 1 is greater than `exp( (new_price - old_price) / temperature)`.

After a certain amount of steps, the temperature is lowered. (equilibrium => cooling)   
If no candidate solution is accepted for many steps the algorithm terminates. (frozen)

## Performance measurements 

I have used supplied problem instance generator.
I have used two different parametrizations for the instance generator.


### Random generator parameter values
- **Problem size: 40** 
- Max weight: 100
- Max Price: 40 
- Capacity to total price ratio: 0.65
- Granularity: 0

#### Simulated annealing parameter values
- Max steps: 4000
- Starting temperature: 200
- Frozen constant: 50 (algorithm terminates after **50** steps without new state) 
- Equilibrium constant: 50 (cooling is performed every **50** steps)
- Cooling koeficient: 0.95
- Neighbour constant: 10 (each neighbour has between 1 and *item_count* / **10** flipped bits)

**Average relative mistake: 0.5%**  
Average CPU time: 0.0034 s

##### Plot of 10 runs (for better overview of price development)

![Simulated annealing](plots/annealing_plot_40items_10runs.png)

##### Plot of 100 runs (more statistically significant)

![Simulated annealing](plots/annealing_plot_40items_100runs.png)

### Random generator parameter values
- **Problem size: 100** 
- Max weight: 100
- Max Price: 40 
- Capacity to total price ratio: 0.65
- Granularity: 0

#### Simulated annealing parameter values
- Max steps: 6000
- Starting temperature: 60
- Frozen constant: 50 (algorithm terminates after **50** steps without new state) 
- Equilibrium constant: 50 (cooling is performed every **50** steps)
- Cooling koeficient: 0.99
- Neighbour constant: 20 (each neighbour has between 1 and *item_count* / **20** flipped bits)

**Average relative mistake: 2%**  
Average CPU time: 0.0054 s

##### Plot of 10 runs (for better overview of price development)

![Simulated annealing](plots/annealing_plot_100items_10runs.png)

##### Plot of 100 runs (more statistically significant)

![Simulated annealing](plots/annealing_plot_100items_100runs.png)



*Relative mistake was calculated in reference to dynamic programming solution.*  
*Measured using Intel Pentium G4560*

## Conclusion
In the following section, I will describe the parameter tunning process. I will evaluate the results and I will pinpoint some observations I have made.

### Parameter tunning process

I have generated 10 instances of the problem.  
Then for each instance, I have run the algorithm 100 times to reach at least *some* level of statistical significance.  
Using obtained data I have created 10 plots (one for each instance).  


After that, I have adjusted the algorithm parameters and repeated the process.


### Measurements evaluation

I have tuned the algorithm parameters to minimize the relative mistake of the algorithm.  
The plots of price development contain both intensification and diversification.


### Neighbour creation

At first, I have created neighbour solutions by flipping only one bit. Neighbouring solutions had a very big difference in price (one added or removed item). Because of that, there were many local maxima and the algorithm was more likely to get stuck in one. This has led to marginally worse solutions (about 10 times worse). 


I have changed the neighbour creation to flipping N bits. This meant that neighbour could have some items added and some removed which have led to a smaller difference in price. Another thing worth mentioning is that this way each solution has more neighbours. Which should help to reduce the likelihood of getting stuck in a suboptimal state.


## Source code
https://gitlab.fit.cvut.cz/letsimon/fit-ctu-mi-ppa/tree/v4.0/knapsack-problem


## References

[1]: https://en.wikipedia.org/wiki/Simulated_annealing
\[1\]: https://en.wikipedia.org/wiki/Simulated_annealing

[2]: http://www.cs.cmu.edu/afs/cs.cmu.edu/project/learn-43/lib/photoz/.g/web/glossary/anneal.html
\[2\]: http://www.cs.cmu.edu/afs/cs.cmu.edu/project/learn-43/lib/photoz/.g/web/glossary/anneal.html
