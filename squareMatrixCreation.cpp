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
    

    
    // Create a random number generator engine
    std::random_device rd;  // Seed engine from hardware entropy
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator

    // Define the distribution
    std::uniform_int_distribution<int> dist(1, 100); // Uniform distribution between 1 and 100
    
    
    //Initialize a 100000 size vector -> 10 distinct square matrices of 100x100
    std::vector<int> squareDataset(100000);
   
    //Populate dataset with random numbers
    for(int i = 0; i < 100000; i++){
        squareDataset[i] = dist(gen);
    }
    writeVectorsToFile(squareDataset, "Square_Matrix_Dataset.txt");
    

    std::vector<int> large_square_dataset(2000000);
    //Populate dataset with random numbers
    for(int i = 0; i < 2000000; i++){
        large_square_dataset[i] = dist(gen);
    }
    writeVectorsToFile(large_square_dataset, "Large_Square_Dataset.txt");

    return 0;
}