#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;


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
//Function for matrix multiplication using two vectors
void matrixMultiplicationWithVectors(int rows1, int cols1, int cols2, int matrix1[], int matrix2[], int result[]){
    // Perform matrix multiplication
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                for (int k = 0; k < cols1; k++) {
                    result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
                }
            }
        }
}

int main() {

    // Define the dimensions of the matrices
    int rowsA = 100;
    int colsA = 100;
    int rowsB = 100;
    int colsB = 100;

    const int squareDatasetSize = 100000;

    int squareDataset[squareDatasetSize];


    // Read full dataset from file
    readDataFromFile("Square_Matrix_Dataset.txt", squareDatasetSize, squareDataset);

   

    // Calculate time taken for 400 repititions with 5 different inputs
    auto fullDuration = microseconds(0);
    
    int sqVector1[10000];
    int sqVector2[10000];

    int product[10000];

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
            matrixMultiplicationWithVectors(rowsA, colsA, colsB, sqVector1, sqVector2, product);
            
            auto partialEndTime = high_resolution_clock::now();

            fullDuration += duration_cast<microseconds>(partialEndTime - partialStartTime);
        }
    }
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
    
    int fullVector1[15000];
    int fullVector2[15000];

    int result[10000];

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
            matrixMultiplicationWithVectors(rowsA, colsA, colsB, fullVector1, fullVector2, result);
            
            auto partialEndTime = high_resolution_clock::now();

            fullDuration2 += duration_cast<microseconds>(partialEndTime - partialStartTime);
        }
    }
    cout << "Time taken for Full Dataset: " << fullDuration2.count() << " microseconds\n";

    // Define the dimensions of the matrices
    rowsA = 1000;
    colsA = 1000;
    rowsB = 1000;
    colsB = 1000;

    const int lgSqDatasetSize = 2000000;

    int lgSqDataset[lgSqDatasetSize];


    // Read large matrix from file
    readDataFromFile("Large_Square_Dataset.txt", lgSqDatasetSize, lgSqDataset);


    
    int largeSqMatrix1[1000000];
    int largeSqMatrix2[1000000];

    int lgResult[1000000];
    int large_index = 0;

    for(int i = 0; i < 1000000; i++){
        largeSqMatrix1[i] = lgSqDataset[large_index];
        large_index++;
    }
    for(int i = 0; i < 1000000; i++){
        largeSqMatrix2[i] = lgSqDataset[large_index];
        large_index++;
    }
    //Test the time for 1000x1000 matrix
    auto lgStartTime = high_resolution_clock::now();
    matrixMultiplicationWithVectors(rowsA, colsA, colsB, largeSqMatrix1, largeSqMatrix2, lgResult);
    auto lgEndTime = high_resolution_clock::now();
    auto largeSqDuration = lgEndTime - lgStartTime;
    return 0;
}
