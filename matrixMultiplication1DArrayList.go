package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	// Small test matrices to verify functionality
	smTestVector1 := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	smTestVector2 := []int{2, 8, 3, 7, 4, 1, 9, 4, 6, 8, 5, 6, 9, 10, 3, 11, 2, 7, 6, 9}

	rowsTestA, colsTestA, rowsTestB, colsTestB := 3, 4, 4, 5

	testResult := multiplyMatrices(smTestVector1, rowsTestA, colsTestA, smTestVector2, rowsTestB, colsTestB)
	counter := 0
	for i := 0; i < rowsTestA; i++ {
		for j := 0; j < colsTestB; j++ {
			fmt.Printf("%d ", testResult[counter])
			counter++
		}
		fmt.Println()
	}

	// Read datasets from files
	fullDataset := readDataFromFile("Full_Dataset.txt", 150000)
	squareDataset := readDataFromFile("Square_Matrix_Dataset.txt", 100000)

	// Dimensions for square matrices
	rowsA, colsA, rowsB, colsB := 100, 100, 100, 100

	// Measure time for square matrix
	var sqDuration int64

	vector1 := make([]int, 10000)
	vector2 := make([]int, 10000)

	for outer := 0; outer < 80; outer++ {
		index := 0
		for i := 0; i < 5; i++ {
			for j := 0; j < 10000; j++ {
				vector1[j] = squareDataset[index]
				index++
			}
			for j := 0; j < 10000; j++ {
				vector2[j] = squareDataset[index]
				index++
			}

			startTime := time.Now()
			_ = multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB)
			endTime := time.Now()

			sqDuration += endTime.Sub(startTime).Microseconds()
		}
	}

	fmt.Println("Time taken for Square Matrix:", sqDuration, "microseconds")

	// Dimensions for non-square matrices
	rowsA, colsA, rowsB, colsB = 100, 150, 150, 100

	// Measure time for non-square matrix multiplication
	var fullDuration int64

	vector1 = make([]int, 15000)
	vector2 = make([]int, 15000)

	for outer := 0; outer < 80; outer++ {
		index := 0
		for i := 0; i < 5; i++ {
			for j := 0; j < 15000; j++ {
				vector1[j] = fullDataset[index]
				index++
			}
			for j := 0; j < 15000; j++ {
				vector2[j] = fullDataset[index]
				index++
			}

			startTime := time.Now()
			_ = multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB)
			endTime := time.Now()

			fullDuration += endTime.Sub(startTime).Microseconds()
		}
	}
	fmt.Println("Time taken for Full Dataset:", fullDuration, "microseconds")

	rowsA, colsA, rowsB, colsB = 1000, 1000, 1000, 1000
	vector1 = make([]int, 1000000)
	vector2 = make([]int, 1000000)

	lgSqVector := readDataFromFile("Large_Square_Dataset.txt", 2000000)

	index := 0
	for i := 0; i < 1000000; i++ {
		vector1[i] = lgSqVector[index]
		index++
	}
	for i := 0; i < 1000000; i++ {
		vector2[i] = lgSqVector[index]
		index++
	}

	startTime := time.Now()
	_ = multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB)
	endTime := time.Now()

	fullDuration = endTime.Sub(startTime).Microseconds()

	fmt.Println("Time taken for Full Dataset:", fullDuration, "microseconds")
}

// Reads the large dataset into an array
func readDataFromFile(filename string, size int) []int {
	dataset := make([]int, size)
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error:", err)
		return dataset
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	index := 0
	for scanner.Scan() && index < size {
		num, _ := strconv.Atoi(scanner.Text())
		dataset[index] = num
		index++
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error:", err)
	}
	return dataset
}

// Function to multiply two matrices represented as slices
func multiplyMatrices(matA []int, rowsA, colsA int, matB []int, rowsB, colsB int) []int {
	if colsA != rowsB {
		panic("Matrix dimensions do not match for multiplication")
	}

	result := make([]int, rowsA*colsB)
	for i := 0; i < rowsA; i++ {
		for j := 0; j < colsB; j++ {
			index := i*colsB + j
			sum := 0
			for k := 0; k < colsA; k++ {
				sum += matA[i*colsA+k] * matB[k*colsB+j]
			}
			result[index] = sum
		}
	}
	return result
}
