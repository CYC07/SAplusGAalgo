#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

const int POPULATION_SIZE = 100;
const int GENERATIONS = 1000;
const int ARRAY_SIZE = 365;
const float MUTATION_RATE = 0.05;

// Generate initial array from 1 to 365
vector<int> generateInitialArray() {
    vector<int> arr(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

// Calculate fitness score for a "best case" (ascending order)
int fitnessBest(const vector<int>& arr) {
    int score = 0;
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            score++;
        }
    }
    return score;
}

// Calculate fitness score for a "worst case" (descending order)
int fitnessWorst(const vector<int>& arr) {
    int score = 0;
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            score++;
        }
    }
    return score;
}

// Calculate fitness score for an "average case" (random order)
int fitnessAverage(const vector<int>& arr) {
    int score = 0;
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        if (abs(arr[i] - arr[i + 1]) > 1) {
            score++;
        }
    }
    return score;
}

// Generate a random individual (randomly shuffle array)
vector<int> generateIndividual() {
    vector<int> individual = generateInitialArray();
    random_shuffle(individual.begin(), individual.end());
    return individual;
}

// Select parents using tournament selection
vector<int> tournamentSelection(const vector<pair<vector<int>, int>>& population, bool best) {
    int bestFitness = best ? -1 : ARRAY_SIZE + 1;
    vector<int> parent;
    for (int i = 0; i < 5; i++) {
        int randomIndex = rand() % POPULATION_SIZE;
        int fitness = population[randomIndex].second;
        if ((best && fitness > bestFitness) || (!best && fitness < bestFitness)) {
            bestFitness = fitness;
            parent = population[randomIndex].first;
        }
    }
    return parent;
}

// Perform crossover (single point crossover)
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    vector<int> child = parent1;
    int crossoverPoint = rand() % ARRAY_SIZE;
    for (int i = crossoverPoint; i < ARRAY_SIZE; i++) {
        child[i] = parent2[i];
    }
    return child;
}

// Mutate individual by swapping two elements
void mutate(vector<int>& individual) {
    if (static_cast<float>(rand()) / RAND_MAX < MUTATION_RATE) {
        int index1 = rand() % ARRAY_SIZE;
        int index2 = rand() % ARRAY_SIZE;
        swap(individual[index1], individual[index2]);
    }
}

// Main genetic algorithm function
vector<int> geneticAlgorithm(int (*fitnessFunc)(const vector<int>&)) {
    vector<pair<vector<int>, int>> population;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        vector<int> individual = generateIndividual();
        int fitness = fitnessFunc(individual);
        population.push_back({individual, fitness});
    }

    for (int gen = 0; gen < GENERATIONS; gen++) {
        vector<pair<vector<int>, int>> newPopulation;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            vector<int> parent1 = tournamentSelection(population, fitnessFunc == fitnessBest);
            vector<int> parent2 = tournamentSelection(population, fitnessFunc == fitnessBest);
            vector<int> child = crossover(parent1, parent2);
            mutate(child);
            int fitness = fitnessFunc(child);
            newPopulation.push_back({child, fitness});
        }
        population = newPopulation;
    }

    sort(population.begin(), population.end(), [&](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
        return a.second > b.second;  // Sort by fitness score
    });

    return population[0].first;
}

int main() {
    srand(time(0));

    // Best Case
    auto start = chrono::high_resolution_clock::now();
    vector<int> bestCaseArray = geneticAlgorithm(fitnessBest);
    auto end = chrono::high_resolution_clock::now();
    auto durationBest = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Best Case Fitness: " << fitnessBest(bestCaseArray) << endl;
    cout << "Time taken for Best Case: " << durationBest.count() << "ms" << endl;

    // Average Case
    start = chrono::high_resolution_clock::now();
    vector<int> averageCaseArray = geneticAlgorithm(fitnessAverage);
    end = chrono::high_resolution_clock::now();
    auto durationAverage = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Average Case Fitness: " << fitnessAverage(averageCaseArray) << endl;
    cout << "Time taken for Average Case: " << durationAverage.count() << "ms" << endl;

    // Worst Case
    start = chrono::high_resolution_clock::now();
    vector<int> worstCaseArray = geneticAlgorithm(fitnessWorst);
    end = chrono::high_resolution_clock::now();
    auto durationWorst = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Worst Case Fitness: " << fitnessWorst(worstCaseArray) << endl;
    cout << "Time taken for Worst Case: " << durationWorst.count() << "ms" << endl;

    return 0;
}
