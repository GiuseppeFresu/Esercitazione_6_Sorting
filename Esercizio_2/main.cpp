#include <iostream>
#include <vector>
//#include <string>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;

vector<int> generateRandomVector(size_t size)
{
    vector<int> vector(size);
    for (size_t i = 0; i < size; i++)
    {
        vector[i] = rand();
    }
    return vector;
}

void partialSortVector(vector<int>& vector, bool ascending, double percentage)
{
    int elementsToSort = static_cast<int>(vector.size() * percentage);

    if (ascending)
    {
        sort(vector.begin(), vector.begin() + elementsToSort);
    }
    else
    {
        sort(vector.begin(), vector.begin() + elementsToSort, greater<int>());
    }
}

double measureAverageSortTime(vector<int>& vec, void (*sortFunction)(vector<int>&), int numRuns)
{
    double totalTime = 0;

    for (int run = 0; run < numRuns; run++)
    {

        vector<int> vecCopy = vec;

        // Start time
        chrono::steady_clock::time_point startTime
                =chrono::steady_clock::now();

        // Call the sorting function
        sortFunction(vec);

        // End time
        chrono::steady_clock::time_point endTime
                =chrono::steady_clock::now();

        // Calculate the duration
        double timeElapsed =
                chrono::duration_cast<chrono::microseconds>
                (endTime-startTime).count();

        double timeElapsedMs = timeElapsed / 1000.0;

        totalTime += timeElapsedMs;
    }

    double averageTime = totalTime / numRuns;

    return averageTime;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <vector_size>" << endl;
        return 1;
    }

    size_t vectorSize = atoi(argv[1]);

    int numRuns = 10;

    vector<int> randVector = generateRandomVector(vectorSize);
    vector<int> bubbleSortVec = randVector;
    vector<int> mergeSortVec = randVector;

    cout << "Average time for Bubble Sort of a random vector: "
         << measureAverageSortTime(bubbleSortVec, BubbleSort<int>, numRuns) << " ms." << endl;
    cout << "Average time for Merge Sort of a random vector: "
         << measureAverageSortTime(mergeSortVec, MergeSort<int>, numRuns) << " ms." << endl;

    vector<int> partialAscendingVector = randVector;
    partialSortVector(partialAscendingVector, true, 0.3);
    vector<int> bubblePartialAscendingVector = partialAscendingVector;
    vector<int> mergePartialAscendingVector = partialAscendingVector;

    cout << "Average time for Bubble Sort of a partially ascending ordered random vector: "
         << measureAverageSortTime(bubblePartialAscendingVector, BubbleSort<int>, numRuns) << " ms." << endl;
    cout << "Average time for Merge Sort of a partially ascending ordered random vector: "
         << measureAverageSortTime(mergePartialAscendingVector, MergeSort<int>, numRuns) << " ms." << endl;

    vector<int> partialDescendingVector = randVector;
    partialSortVector(partialDescendingVector, false, 0.3);
    vector<int> bubblePartialDescendingVector = partialDescendingVector;
    vector<int> mergePartialDescendingVector = partialDescendingVector;

    cout << "Average time for Bubble Sort of a partially descending ordered random vector: "
         << measureAverageSortTime(bubblePartialDescendingVector, BubbleSort<int>, numRuns) << " ms." << endl;
    cout << "Average time for Merge Sort of a partially descending ordered random vector: "
         << measureAverageSortTime(mergePartialDescendingVector, MergeSort<int>, numRuns) << " ms." << endl;

    vector<int> descendingVector = randVector;
    partialSortVector(descendingVector, false, 1);
    vector<int> bubbleDescendingVector = descendingVector;
    vector<int> mergeDescendingVector = descendingVector;

    cout << "Average time for Bubble Sort of a descending ordered random vector: "
         << measureAverageSortTime(bubbleDescendingVector, BubbleSort<int>, numRuns) << " ms." << endl;
    cout << "Average time for Merge Sort of a descending ordered random vector: "
         << measureAverageSortTime(mergeDescendingVector, MergeSort<int>, numRuns) << " ms." << endl;

    return 0;
}
