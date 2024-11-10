There are three files that have an arary for 1-365. 
To test which algo is most optimized we use Genetic Algo and Simulated Annealing Algo.
Then we create a hybrid of these two algos.

  **GENETIC ALGORITHM**

**Pros of Genetic Algo:**  
  GAs are excellent at exploring large, complex, and multi-modal search spaces.
  GAs can be applied to a wide range of problems, including those with complex and poorly understood fitness landscapes.     They are versatile and can be used for both combinatorial optimization problems
  GAs can adapt to changes in the problem space.
  GAs work with a population of solutions, the evaluations of different solutions can be done in parallel.
  Unlike many optimization methods (such as gradient descent), GAs do not require derivative information or a predefined     model of the problem.

**Cons of Genetic Algo:**
  GAs can be computationally expensive because they evaluate a large population of candidate solutions over many             generations.
  While GAs are good at exploring the search space, they often converge slowly to an optimal solution.
  GAs require careful selection of parameters (e.g., population size, crossover rate, mutation rate, and number of           generations).
  GAs can suffer from premature convergence, where the population becomes too homogeneous, and the algorithm stops           exploring new areas of the search space.
  GAs do not guarantee that they will find the optimal solution, only a good approximation.

   **SIMULATED ANNEALING ALGORITHM**

**Pros of Simulated Annealing Algo**
  SA is good at avoiding local optima and can explore the entire solution space, similar to genetic algorithms.
  The concept of SA is simple to understand and easy to implement. It uses a probabilistic approach based on temperature     and energy to simulate the annealing process in metallurgy
  SA is a general-purpose algorithm that can be used for a wide variety of optimization problems, including combinatorial    problems, continuous optimization, and problems with complex constraints.
  By allowing worse solutions with a certain probability (based on temperature), SA can escape local minima, making it       less likely to get stuck in suboptimal solutions

  **Cons of Simulated Annealing Algo**
    SA can converge very slowly, especially if the cooling schedule is not carefully designed.
    SA performance is highly dependent on the choice of parameters
    If the temperature is reduced too quickly, SA may fail to explore the search space sufficiently and may get stuck in       suboptimal solutions
    While SA has the potential to find a global optimum, it does not guarantee finding it.
    SA can be computationally expensive, particularly when dealing with large-scale problems or when a large number of         iterations are required to achieve convergence. 
