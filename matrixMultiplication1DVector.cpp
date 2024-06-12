#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;


/// Function to multiply two matrices represented as 1D vectors
vector<int> multiplyMatrices(const vector<int>& matA, int rowsA, int colsA,
                             const vector<int>& matB, int rowsB, int colsB) {
    // The number of columns in matA must be equal to the number of rows in matB
    if (colsA != rowsB) {
        throw invalid_argument("Matrix dimensions do not match for multiplication");
    }

    // Initialize the result matrix with zeros
    vector<int> result(rowsA * colsB, 0);

    // Perform matrix multiplication
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i * colsB + j] += matA[i * colsA + k] * matB[k * colsB + j];
            }
        }
    }

    return result;
}
//Function to read datasets to large for stack
vector<int>readVectorFromFile(const string& filename, int size){
    ifstream file(filename);
    vector<int> dataset;
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);  
    }

    int number;
    for (int i = 0; i < size; ++i) {
        if (!(file >> number)) {
            cerr << "Error: Not enough numbers in the file" << endl;
            exit(1);  
        }
        dataset.push_back(number);
    }

    file.close();
    return dataset;
}
// Function to read data from a file into an array
void readDataFromFile(const string& filename, int size, int dataset[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < size; ++i) {
        if (!(file >> dataset[i])) {
            cerr << "Error: Not enough numbers in the file" << endl;
            exit(1);
        }
    }

    file.close();
}

int main() {

    

    const int squareDatasetSize = 100000;

    int squareDataset[squareDatasetSize];


    // Read full dataset from file
    readDataFromFile("Square_Matrix_Dataset.txt", squareDatasetSize, squareDataset);

    //Set dimensions for matrices
    int rowsA = 100;
    int colsA = 100;
    int rowsB = 100;
    int colsB = 100;


    // Calculate time taken for 400 repititions with 5 different inputs
    auto fullDuration = microseconds(0);
    
    vector <int> sqVector1(10000);
    vector <int> sqVector2(10000);

    vector <int> product(10000);


    for(int outer = 0; outer < 80; outer++){
    int index = 0;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10000; j++){
                sqVector1[j] = squareDataset[index];
                index++;
            }
            for(int j = 0; j < 10000; j++){
                sqVector2[j] = squareDataset[index];
                index++;
            }
            auto partialStartTime = high_resolution_clock::now();

            multiplyMatrices(sqVector1, rowsA, colsA, sqVector2, rowsB, colsB);

            auto partialEndTime = high_resolution_clock::now();

            fullDuration += duration_cast<microseconds>(partialEndTime - partialStartTime);
        }
    }
    sqVector1.clear();
    sqVector2.clear();
    cout << "Time taken for Square Matrix: " << fullDuration.count() << " microseconds\n";

    // Define the dimensions of the matrices
    rowsA = 100;
    colsA = 150;
    rowsB = 150;
    colsB = 100;

    const int fullDatasetSize = 150000;

    int fullDataset[fullDatasetSize];


    // Read full dataset from file
    readDataFromFile("Full_Dataset.txt", fullDatasetSize, fullDataset);

   

    // Calculate time taken for 400 repititions with 5 different inputs
    auto fullDuration2 = microseconds(0);
    
    vector <int> fullVector1(15000);
    vector <int> fullVector2(15000);

    vector <int> result(10000);

    //Loop tests with 5 different inputs 80 times for a total of 400 attempts
    for(int outer = 0; outer < 80; outer++){
        int index2 = 0;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 15000; j++){
                fullVector1[j] = fullDataset[index2];
                index2++;
            }
            for(int j = 0; j < 15000; j++){
                fullVector2[j] = fullDataset[index2];
                index2++;
            }
            auto partialStartTime = high_resolution_clock::now();
            multiplyMatrices(fullVector1, rowsA, colsA, fullVector2, rowsB, colsB);
            
            auto partialEndTime = high_resolution_clock::now();

            fullDuration2 += duration_cast<microseconds>(partialEndTime - partialStartTime);
        }
    }
    cout << "Time taken for Full Dataset: " << fullDuration2.count() << " microseconds\n";

    auto lgSqDuration = microseconds(0);
    vector <int> lgSqVector1(1000000);
    vector <int> lgSqVector2(1000000);

    const int lgDatasetSize = 2000000;

    vector <int> lgDataset = readVectorFromFile("Large_Square_Dataset.txt", lgDatasetSize);

    // Define the dimensions of the matrices
    rowsA = 1000;
    colsA = 1000;
    rowsB = 1000;
    colsB = 1000;

    auto partialStartTimeF = high_resolution_clock::now();

    multiplyMatrices(lgSqVector1, rowsA, colsA, lgSqVector2, rowsB, colsB);
            
    auto partialEndTimeF = high_resolution_clock::now();

    auto fullDuration3 = duration_cast<microseconds>(partialEndTimeF - partialStartTimeF);

    cout << "Time taken for Full Dataset: " << fullDuration3.count() << " microseconds\n";

    for(int i = 0; i < lgSqVector1.size() - 1; i++){
        int* address1 = &lgSqVector1[i];
        int* address2 = &lgSqVector1[i+1];

        if(address2 - address1 != 1){
            cout << "Break in memory at index: " << i << endl;
        }

    }
    cout << "Address of vector[0] is " << &lgSqVector1[0] << std::endl;
    cout << "Address of vector[999999]" << &lgSqVector1[999999] << std::endl;

    return 0;
}
