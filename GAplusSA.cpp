#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate initial population
vector<int> generatePopulation(int n) {
    vector<int> population;
    for (int i = 1; i <= n; i++) {
        population.push_back(i);
    }
    return population;
}

// Function to create best, average, and worst-case scenarios
void createScenarios(vector<int>& bestCase, vector<int>& averageCase, vector<int>& worstCase, int n) {
    bestCase = generatePopulation(n);
    averageCase = bestCase;
    worstCase = bestCase;
    
    // Shuffle for average case
    shuffle(averageCase.begin(), averageCase.end(), default_random_engine(time(0)));
    
    // Reverse for worst case
    reverse(worstCase.begin(), worstCase.end());
}

// Fitness function to calculate "fitness" of a solution
int fitness(const vector<int>& arr) {
    int fitnessScore = 0;
    for (size_t i = 1; i < arr.size(); i++) {
        fitnessScore += abs(arr[i] - arr[i - 1]);
    }
    return fitnessScore;
}

// Genetic Algorithm functions
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    vector<int> child;
    size_t n = parent1.size();
    for (size_t i = 0; i < n; i++) {
        if (i % 2 == 0) {
            child.push_back(parent1[i]);
        } else {
            child.push_back(parent2[i]);
        }
    }
    return child;
}

void mutate(vector<int>& child) {
    int idx1 = rand() % child.size();
    int idx2 = rand() % child.size();
    swap(child[idx1], child[idx2]);
}

// Simulated Annealing function for local optimization
void simulatedAnnealing(vector<int>& solution, double initialTemp, double coolingRate) {
    double temp = initialTemp;
    int currentFitness = fitness(solution);
    
    while (temp > 1) {
        vector<int> newSolution = solution;
        mutate(newSolution);  // Small mutation for new solution
        int newFitness = fitness(newSolution);
        
        // Accept new solution if it improves or with probability based on temperature
        if (newFitness < currentFitness || exp((currentFitness - newFitness) / temp) > (double)rand() / RAND_MAX) {
            solution = newSolution;
            currentFitness = newFitness;
        }
        
        // Cool down the temperature
        temp *= coolingRate;
    }
}

// Main hybrid optimization function
vector<int> hybridOptimization(int n, int generations, double initialTemp, double coolingRate) {
    vector<int> bestSolution = generatePopulation(n);
    int bestFitness = fitness(bestSolution);

    for (int gen = 0; gen < generations; gen++) {
        vector<int> parent1 = bestSolution;
        vector<int> parent2 = generatePopulation(n);
        shuffle(parent2.begin(), parent2.end(), default_random_engine(rand()));
        
        vector<int> child = crossover(parent1, parent2);
        mutate(child);
        
        // Apply simulated annealing for local optimization on child
        simulatedAnnealing(child, initialTemp, coolingRate);
        
        int childFitness = fitness(child);
        if (childFitness < bestFitness) {
            bestSolution = child;
            bestFitness = childFitness;
        }
    }

    return bestSolution;
}

int main() {
    srand(time(0));
    int n = 365;  // Array size
    int generations = 1000;
    double initialTemp = 1000;
    double coolingRate = 0.99;

    vector<int> bestCase, averageCase, worstCase;
    createScenarios(bestCase, averageCase, worstCase, n);

    // Time and test best-case scenario
    auto startBest = high_resolution_clock::now();
    vector<int> optimizedBest = hybridOptimization(n, generations, initialTemp, coolingRate);
    auto endBest = high_resolution_clock::now();
    auto durationBest = duration_cast<milliseconds>(endBest - startBest);
    cout << "Best-case scenario fitness: " << fitness(optimizedBest) << endl;
    cout << "Best-case scenario time: " << durationBest.count() << " ms" << endl;

    // Time and test average-case scenario
    auto startAverage = high_resolution_clock::now();
    vector<int> optimizedAverage = hybridOptimization(n, generations, initialTemp, coolingRate);
    auto endAverage = high_resolution_clock::now();
    auto durationAverage = duration_cast<milliseconds>(endAverage - startAverage);
    cout << "Average-case scenario fitness: " << fitness(optimizedAverage) << endl;
    cout << "Average-case scenario time: " << durationAverage.count() << " ms" << endl;

    // Time and test worst-case scenario
    auto startWorst = high_resolution_clock::now();
    vector<int> optimizedWorst = hybridOptimization(n, generations, initialTemp, coolingRate);
    auto endWorst = high_resolution_clock::now();
    auto durationWorst = duration_cast<milliseconds>(endWorst - startWorst);
    cout << "Worst-case scenario fitness: " << fitness(optimizedWorst) << endl;
    cout << "Worst-case scenario time: " << durationWorst.count() << " ms" << endl;

    return 0;
}
