import time

def read_matrix_from_file(filename, rows, cols):
    matrix = []
    try:
        with open(filename, 'r') as file:
            for i in range(rows):
                row = []
                for j in range(cols):
                    line = file.readline().strip()
                    if line:
                        row.append(int(line))
                    else:
                        raise ValueError("Not enough numbers in the file")
                matrix.append(row)
    except FileNotFoundError:
        print(f"File not found: {filename}")
    return matrix

def matrix_multiply(matrix1, matrix2):
    rows1 = len(matrix1)
    cols1 = len(matrix1[0])
    cols2 = len(matrix2[0])

    result = [[0 for _ in range(cols2)] for _ in range(rows1)]
    for i in range(rows1):
        for j in range(cols2):
            sum = 0
            for k in range(cols1):
                sum += matrix1[i][k] * matrix2[k][j]
            result[i][j] = sum
    return result

def read_data_from_file(filename, size):
    dataset = []
    try:
        with open(filename, 'r') as file:
            for line in file:
                numbers = line.strip().split()
                for num in numbers:
                    if len(dataset) < size:
                        dataset.append(int(num))
                    else:
                        break
    except FileNotFoundError:
        print(f"File not found: {filename}")
    return dataset

def main():
    # Read datasets from files
    full_dataset = read_data_from_file("Full_Dataset.txt", 150000)
    square_dataset = read_data_from_file("Square_Matrix_Dataset.txt", 100000)
    lg_sq_dataset = read_data_from_file("Large_Square_Dataset.txt", 2000000)
    matrix1 = [[0] * 100 for _ in range(100)]
    matrix2 = [[0] * 100 for _ in range(100)]

    sq_duration = 0
    rows = 100
    cols = 100

    for outer in range(80):
        index = 0
        for i in range(5):
            for j in range(rows):
                for k in range(cols):
                    matrix1[j][k] = square_dataset[index]
                    index += 1
            for j in range(rows):
                for k in range(cols):
                    matrix2[j][k] = square_dataset[index]
                    index += 1
            start_time = time.time()
            matrix_multiply(matrix1, matrix2)
            end_time = time.time()
            sq_duration += (end_time - start_time) * 1_000_000  # convert to microseconds

    rows_a = 100
    cols_a = 150
    rows_b = 150
    cols_b = 100

    full_duration = 0
    matrix1 = [[0] * cols_a for _ in range(rows_a)]
    matrix2 = [[0] * cols_b for _ in range(rows_b)]

    for outer in range(80):
        index = 0
        for inner in range(5):
            for i in range(rows_a):
                for j in range(cols_a):
                    matrix1[i][j] = full_dataset[index]
                    index += 1
            for i in range(rows_b):
                for j in range(cols_b):
                    matrix2[i][j] = full_dataset[index]
                    index += 1
            start_time = time.time()
            matrix_multiply(matrix1, matrix2)
            end_time = time.time()
            full_duration += (end_time - start_time) * 1_000_000  # convert to microseconds

    rows = 1000
    cols = 1000

    lg_sq_duration = 0
    matrix1 = [[0] * cols for _ in range(rows)]
    matrix2 = [[0] * cols for _ in range(rows)]

    index = 0
    for j in range(rows):
        for k in range(cols):
            matrix1[j][k] = lg_sq_dataset[index]
            index += 1
    for j in range(rows):
        for k in range(cols):
            matrix2[j][k] = lg_sq_dataset[index]
            index += 1

    start_time = time.time()
    matrix_multiply(matrix1, matrix2)
    end_time = time.time()
    lg_sq_duration = (end_time - start_time) * 1_000_000  # convert to microseconds

    # Print the time taken
    print(f"Time taken for 400: {sq_duration} microseconds")
    print(f"Time taken for full dataset: {full_duration} microseconds")
    print(f"Time taken for 1000x1000: {lg_sq_duration} microseconds")

if __name__ == "__main__":
    main()
