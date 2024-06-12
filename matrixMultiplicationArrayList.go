package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// ReadMatrixFromFile reads a matrix from a file
func ReadMatrixFromFile(filename string, rows, cols int) [][]int {
	matrix := make([][]int, rows)
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("File not found:", filename)
		panic(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for i := 0; i < rows; i++ {
		row := make([]int, cols)
		for j := 0; j < cols; j++ {
			if scanner.Scan() {
				num, err := strconv.Atoi(scanner.Text())
				if err != nil {
					panic("Not enough numbers in the file")
				}
				row[j] = num
			} else {
				panic("Not enough numbers in the file")
			}
		}
		matrix[i] = row
	}
	return matrix
}

// MatrixMultiply performs matrix multiplication
func MatrixMultiply(matrix1, matrix2 [][]int) [][]int {
	rows1 := len(matrix1)
	cols1 := len(matrix1[0])
	cols2 := len(matrix2[0])

	result := make([][]int, rows1)
	for i := 0; i < rows1; i++ {
		result[i] = make([]int, cols2)
		for j := 0; j < cols2; j++ {
			sum := 0
			for k := 0; k < cols1; k++ {
				sum += matrix1[i][k] * matrix2[k][j]
			}
			result[i][j] = sum
		}
	}
	return result
}

// Function to read a dataset from a file
func readDataFromFile(filename string, size int) []int {
    dataset := make([]int, size)

    file, err := os.Open(filename)
    if err != nil {
        fmt.Printf("File not found: %s\n", filename)
        return dataset
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    index := 0
    for scanner.Scan() {
        line := scanner.Text()
        numbers := strings.Fields(line)
        for _, number := range numbers {
            if index >= size {
                break
            }
            num, err := strconv.Atoi(number)
            if err != nil {
                panic("Invalid number in file")
            }
            dataset[index] = num
            index++
        }
        if index >= size {
            break
        }
    }
    return dataset
}
func main() {
	// Read datasets from files
	fullDataset := readDataFromFile("Full_Dataset.txt", 150000)
	squareDataset := readDataFromFile("Square_Matrix_Dataset.txt", 100000)
	lgSqDataset := readDataFromFile("Large_Square_Dataset.txt", 2000000)

	var matrix1, matrix2 [][]int

	matrix1 = make([][]int, 100)
	matrix2 = make([][]int, 100)

	var sqDuration int64
	// 80 reps with 5 different inputs
	rows := 100
	cols := 100

	// Zero the matrices
	for i := 0; i < rows; i++ {
		matrix1[i] = make([]int, cols)
		matrix2[i] = make([]int, cols)
	}

	for outer := 0; outer < 80; outer++ {
		index := 0
		for i := 0; i < 5; i++ {
			for j := 0; j < rows; j++ {
				for k := 0; k < cols; k++ {
					matrix1[j][k] = squareDataset[index]
					index++
				}
			}
			for j := 0; j < rows; j++ {
				for k := 0; k < cols; k++ {
					matrix2[j][k] = squareDataset[index]
					index++
				}
			}
			// Add timestamp
			startTime := time.Now()

			// Perform matrix multiplication
			MatrixMultiply(matrix1, matrix2)
			endTime := time.Now()

			sqDuration += endTime.Sub(startTime).Microseconds()
		}
	}

	// Dimensions for non-square matrices
	rowsA := 100
	colsA := 150
	rowsB := 150
	colsB := 100

	// Measure time for non-square matrix multiplication
	var fullDuration int64

	matrix1 = make([][]int, rowsA)
	matrix2 = make([][]int, rowsB)

	// Zero the matrices
	for i := 0; i < rowsA; i++ {
		matrix1[i] = make([]int, colsA)
	}
	for i := 0; i < rowsB; i++ {
		matrix2[i] = make([]int, colsB)
	}

	for outer := 0; outer < 80; outer++ {
		index := 0
		for inner := 0; inner < 5; inner++ {
			for i := 0; i < rowsA; i++ {
				for j := 0; j < colsA; j++ {
					matrix1[i][j] = fullDataset[index]
					index++
				}
			}
			for i := 0; i < rowsA; i++ {
				for j := 0; j < colsB; j++ {
					matrix2[i][j] = fullDataset[index]
					index++
				}
			}
			startTime := time.Now()
			MatrixMultiply(matrix1, matrix2)
			endTime := time.Now()
			fullDuration += endTime.Sub(startTime).Microseconds()
		}
	}

	rows = 1000
	cols = 1000

	var lgSqDuration int64

	matrix1 = make([][]int, rows)
	matrix2 = make([][]int, rows)

	// Zero the matrices
	for i := 0; i < rows; i++ {
		matrix1[i] = make([]int, cols)
		matrix2[i] = make([]int, cols)
	}

	index := 0

	for j := 0; j < rows; j++ {
		for k := 0; k < cols; k++ {
			matrix1[j][k] = lgSqDataset[index]
			index++
		}
	}
	for j := 0; j < rows; j++ {
		for k := 0; k < cols; k++ {
			matrix2[j][k] = lgSqDataset[index]
			index++
		}
	}
	// Add timestamp
	startTime := time.Now()

	// Perform matrix multiplication
	MatrixMultiply(matrix1, matrix2)
	endTime := time.Now()

	lgSqDuration = endTime.Sub(startTime).Microseconds()

	// Print the time taken
	fmt.Println("Time taken for 400:", sqDuration, "microseconds")
	fmt.Println("Time taken for 400:", fullDuration, "microseconds")
	fmt.Println("Time taken for 1000x1000:", lgSqDuration, "microseconds")
}
