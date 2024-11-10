#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

const int ARRAY_SIZE = 365;
const int INITIAL_TEMP = 1000;  // Initial temperature
const double COOLING_RATE = 0.995;  // Rate at which temperature is reduced
const int ITERATIONS = 100;  // Number of iterations at each temperature

// Generate initial array from 1 to 365
vector<int> generateInitialArray() {
    vector<int> arr(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

// Fitness function for "best case" (ascending order)
int fitnessBest(const vector<int>& arr) {
    int score = 0;
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            score++;
        }
    }
    return score;  // Higher score means more elements in ascending order
}

// Fitness function for "worst case" (descending order)
int fitnessWorst(const vector<int>& arr) {
    int score = 0;
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            score++;
        }
    }
    return score;  // Higher score means more elements in descending order
}

// Fitness function for "average case" (random order)
int fitnessAverage(const vector<int>& arr) {
    int score = 0;
    for (int i = 1; i < ARRAY_SIZE - 1; i++) {
        if (abs(arr[i] - arr[i - 1]) > 1 && abs(arr[i] - arr[i + 1]) > 1) {
            score++;
        }
    }
    return score;  // Higher score means more randomness
}

// Simulated annealing function
vector<int> simulatedAnnealing(vector<int> initialArray, int (*fitnessFunc)(const vector<int>&)) {
    vector<int> currentArray = initialArray;
    int currentFitness = fitnessFunc(currentArray);
    int bestFitness = currentFitness;
    vector<int> bestArray = currentArray;

    double temperature = INITIAL_TEMP;
    srand(time(0));

    while (temperature > 1) {
        for (int i = 0; i < ITERATIONS; i++) {
            // Generate new neighbor by swapping two random elements
            vector<int> newArray = currentArray;
            int idx1 = rand() % ARRAY_SIZE;
            int idx2 = rand() % ARRAY_SIZE;
            swap(newArray[idx1], newArray[idx2]);

            // Calculate fitness of the new array
            int newFitness = fitnessFunc(newArray);

            // Accept new state with a probability based on the temperature
            if (newFitness > currentFitness || exp((newFitness - currentFitness) / temperature) > ((double) rand() / RAND_MAX)) {
                currentArray = newArray;
                currentFitness = newFitness;

                // Update best solution if new fitness is better
                if (currentFitness > bestFitness) {
                    bestArray = currentArray;
                    bestFitness = currentFitness;
                }
            }
        }
        // Cool down the temperature
        temperature *= COOLING_RATE;
    }
    return bestArray;
}

int main() {
    vector<int> initialArray = generateInitialArray();

    // Measure time for Best Case
    auto start = high_resolution_clock::now();
    vector<int> bestCase = simulatedAnnealing(initialArray, fitnessBest);
    auto end = high_resolution_clock::now();
    auto durationBest = duration_cast<milliseconds>(end - start);
    cout << "Best Case Fitness: " << fitnessBest(bestCase) << endl;
    cout << "Time taken for Best Case: " << durationBest.count() << "ms" << endl;

    // Measure time for Worst Case
    start = high_resolution_clock::now();
    vector<int> worstCase = simulatedAnnealing(initialArray, fitnessWorst);
    end = high_resolution_clock::now();
    auto durationWorst = duration_cast<milliseconds>(end - start);
    cout << "Worst Case Fitness: " << fitnessWorst(worstCase) << endl;
    cout << "Time taken for Worst Case: " << durationWorst.count() << "ms" << endl;

    // Measure time for Average Case
    start = high_resolution_clock::now();
    vector<int> avgCase = simulatedAnnealing(initialArray, fitnessAverage);
    end = high_resolution_clock::now();
    auto durationAverage = duration_cast<milliseconds>(end - start);
    cout << "Average Case Fitness: " << fitnessAverage(avgCase) << endl;
    cout << "Time taken for Average Case: " << durationAverage.count() << "ms" << endl;

    return 0;
}
