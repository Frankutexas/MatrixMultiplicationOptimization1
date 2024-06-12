#include <iostream>
#include <fstream>
#include <vector>
#include <random>

//Writing numbers to file function
void writeNumbersToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write numbers to the file
    for (const auto& row : matrix) {
        for (int num : row) {
            outputFile << num << " ";
        }
        outputFile << std::endl; // Write newline after each row
    }

    outputFile.close();
}
//Writing Vectors to file function
void writeVectorsToFile(const std::vector<int>& vector1, const std::string& filename){
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }
    for(int num: vector1){
        outputFile << num << " ";
    }
    outputFile.close();
}

int main() {
    // Example matrix
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Write matrix to file
    writeNumbersToFile(matrix, "output.txt");
    // Create a random number generator engine
    std::random_device rd;  // Seed engine from hardware entropy
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator

    // Define the distribution
    std::uniform_int_distribution<int> dist(1, 100); // Uniform distribution between 1 and 100

    
   //Initialize a 100x150 matrix and 150x100 matrix
    std::vector<std::vector<int>> largeMatrix1(100, std::vector<int>(150));
    std::vector<std::vector<int>> largeMatrix2(150, std::vector<int>(100));
    
    //Initialize a 150000 size vector
    std::vector<int> fullDataset(150000);
   
    //Fill with random numbers between 1-100
    for(int i = 0; i <100; i++){
        for(int j =0; j<150; j++){
             largeMatrix1[i][j] = dist(gen);
        }
       
    }

    for(int i = 0; i <150; i++){
        for(int j =0; j<100; j++){
              largeMatrix2[i][j] = dist(gen);
        }
       
    }

    writeNumbersToFile(largeMatrix1, "testMatrix3.txt");
    writeNumbersToFile(largeMatrix2, "testMatrix4.txt");

    for(int i = 0; i <150; i++){
        for(int j =0; j<100; j++){
              largeMatrix2[i][j] = dist(gen);
        }
       
    }
    for(int i = 0; i < 150000; i++){
        fullDataset[i] = dist(gen);
    }
    writeVectorsToFile(fullDataset, "Full_Dataset.txt");


    return 0;
}