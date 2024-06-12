import time

def read_data_from_file(filename, size):
    dataset = []
    with open(filename, 'r') as file:
        for line in file:
            numbers = line.strip().split()
            for num in numbers:
                if len(dataset) < size:
                    dataset.append(int(num))
                else:
                    break
    return dataset

def multiply_matrices(matA, rowsA, colsA, matB, rowsB, colsB):
    if colsA != rowsB:
        raise ValueError("Matrix dimensions do not match for multiplication")

    result = [0] * (rowsA * colsB)
    for i in range(rowsA):
        for j in range(colsB):
            index = i * colsB + j
            sum = 0
            for k in range(colsA):
                sum += matA[i * colsA + k] * matB[k * colsB + j]
            result[index] = sum
    return result

def main():
    # Small test matrices to verify functionality
    sm_test_vector1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    sm_test_vector2 = [2, 8, 3, 7, 4, 1, 9, 4, 6, 8, 5, 6, 9, 10, 3, 11, 2, 7, 6, 9]
    rows_test_a, cols_test_a, rows_test_b, cols_test_b = 3, 4, 4, 5

    test_result = multiply_matrices(sm_test_vector1, rows_test_a, cols_test_a, sm_test_vector2, rows_test_b, cols_test_b)
    counter = 0
    for i in range(rows_test_a):
        for j in range(cols_test_b):
            print(test_result[counter], end=' ')
            counter += 1
        print()

    # Read datasets from files
    full_dataset = read_data_from_file("Full_Dataset.txt", 150000)
    square_dataset = read_data_from_file("Square_Matrix_Dataset.txt", 100000)
    lg_sq_dataset = read_data_from_file("Large_Square_Dataset.txt", 2000000)

    # Dimensions for square matrices
    rows_a, cols_a, rows_b, cols_b = 100, 100, 100, 100

    # Measure time for square matrix
    sq_duration = 0
    for outer in range(80):
        index = 0
        vector1 = square_dataset[index:index+10000]
        vector2 = square_dataset[index+10000:index+20000]
        for _ in range(5):
            start_time = time.time()
            multiply_matrices(vector1, rows_a, cols_a, vector2, rows_b, cols_b)
            end_time = time.time()
            sq_duration += (end_time - start_time) * 1_000_000  # convert to microseconds
            index += 20000

    print("Time taken for Square Matrix:", sq_duration, "microseconds")

    # Dimensions for non-square matrices
    rows_a, cols_a, rows_b, cols_b = 100, 150, 150, 100

    # Measure time for non-square matrix multiplication
    full_duration = 0
    for outer in range(80):
        index = 0
        vector1 = full_dataset[index:index+15000]
        vector2 = full_dataset[index+15000:index+30000]
        for _ in range(5):
            start_time = time.time()
            multiply_matrices(vector1, rows_a, cols_a, vector2, rows_b, cols_b)
            end_time = time.time()
            full_duration += (end_time - start_time) * 1_000_000  # convert to microseconds
            index += 30000
    print("Time taken for Full Dataset:", full_duration, "microseconds")

    rows_a, cols_a, rows_b, cols_b = 1000, 1000, 1000, 1000
    vector1 = lg_sq_dataset[:1000000]
    vector2 = lg_sq_dataset[1000000:]

    start_time = time.time()
    multiply_matrices(vector1, rows_a, cols_a, vector2, rows_b, cols_b)
    end_time = time.time()
    full_duration = (end_time - start_time) * 1_000_000  # convert to microseconds

    print("Time taken for Full Dataset:", full_duration, "microseconds")

if __name__ == "__main__":
    main()
