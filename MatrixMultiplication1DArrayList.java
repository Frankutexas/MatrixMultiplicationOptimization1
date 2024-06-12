import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.TimeUnit;

public class MatrixMultiplication1DArrayList {

    public static void main(String[] args) {

        //Small test matrices to verify functionality
        List<Integer> smTestVector1 = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8,9,10,11,12));
        List<Integer> smTestVector2 = new ArrayList<>(Arrays.asList(2,8,3,7,4,1,9,4,6,8,5,6,9,10,3,11,2,7,6,9));

        int rowsTestA = 3, colsTestA = 4, rowsTestB = 4, colsTestB = 5;

        List<Integer> testResult = multiplyMatrices(smTestVector1, rowsTestA, colsTestA, smTestVector2, rowsTestB, colsTestB);
        int counter = 0;
        for(int i = 0; i < rowsTestA; i++){
            for(int j=0; j<colsTestB; j++){
                System.out.print(testResult.get(counter) + " ");
                counter++;
            }
            System.out.println();
        }
        
        // Read datasets from files
        List<Integer> fullDataset = readDataFromFile("Full_Dataset.txt", 150000);
        List<Integer> squareDataset = readDataFromFile("Square_Matrix_Dataset.txt", 100000);


        // Dimensions for square matrices
        int rowsA = 100, colsA = 100, rowsB = 100, colsB = 100;

        // Measure time for square matrix
        long sqDuration = 0;

        List<Integer> vector1 = new ArrayList<>(Collections.nCopies(10000, 0));
        List<Integer> vector2 = new ArrayList<>(Collections.nCopies(10000, 0));

        for (int outer = 0; outer < 80; outer++) {
            int index = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 10000; j++) {
                    vector1.set(j, squareDataset.get(index++));
                    
                }
                for (int j = 0; j < 10000; j++) {
                    vector2.set(j, squareDataset.get(index++));
                }

                long startTime = System.nanoTime();
                multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB);
                long endTime = System.nanoTime();

                sqDuration += TimeUnit.NANOSECONDS.toMicros(endTime - startTime);
            }
        }

        System.out.println("Time taken for Square Matrix: " + sqDuration + " microseconds");

        // Dimensions for non-square matrices
        rowsA = 100; colsA = 150; rowsB = 150; colsB = 100;

        // Measure time for non-square matrix multiplication
        // Measure time for square matrix
        long fullDuration = 0;

        vector1 = new ArrayList<>(Collections.nCopies(15000, 0));
        vector2 = new ArrayList<>(Collections.nCopies(15000, 0));

        for (int outer = 0; outer < 80; outer++) {
            int index = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 15000; j++) {
                    vector1.set(j, fullDataset.get(index++));
                    
                }
                for (int j = 0; j < 15000; j++) {
                    vector2.set(j, fullDataset.get(index++));
                }

                long startTime = System.nanoTime();
                multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB);
                long endTime = System.nanoTime();

                fullDuration += TimeUnit.NANOSECONDS.toMicros(endTime - startTime);
            }
        }
        System.out.println("Time taken for Full Dataset: " + fullDuration + " microseconds");

        rowsA = 1000; colsA = 1000; rowsB = 1000; colsB = 1000;
        vector1 = new ArrayList<>(Collections.nCopies(1000000, 0));
        vector2 = new ArrayList<>(Collections.nCopies(1000000, 0));

        List <Integer> lgSqVector;
        int lgSqVectorSize = 2000000;
        lgSqVector = readDataFromFile("Large_Square_Dataset.txt", lgSqVectorSize);

        int index = 0;
        for(int i = 0; i < 1000000; i++){
            vector1.set(i, lgSqVector.get(index++));
        }
        for(int i = 0; i < 1000000; i++){
            vector2.set(i, lgSqVector.get(index++));
        }

        long startTime = System.nanoTime();
        multiplyMatrices(vector1, rowsA, colsA, vector2, rowsB, colsB);
        long endTime = System.nanoTime();

        fullDuration = TimeUnit.NANOSECONDS.toMicros(endTime - startTime);

        System.out.println("Time taken for Full Dataset: " + fullDuration + " microseconds");
    }

    // Reads the large dataset into an array
    public static List<Integer> readDataFromFile(String filename, int size) {
        List <Integer> dataset = new ArrayList<>(size);
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            for (int i = 0; i < size; i++) {
                if (scanner.hasNextInt()) {
                    dataset.add(scanner.nextInt());
                } else {
                    throw new IllegalArgumentException("Not enough numbers in the file");
                }
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + filename);
            e.printStackTrace();
        }
        return dataset;
    }
    
    // Function to multiply two matrices represented as ArrayLists
    public static List<Integer> multiplyMatrices(List<Integer> matA, int rowsA, int colsA, List<Integer> matB, int rowsB, int colsB) {
        if (colsA != rowsB) {
            throw new IllegalArgumentException("Matrix dimensions do not match for multiplication");
        }

        List<Integer> result = new ArrayList<>(Collections.nCopies(rowsA * colsB, 0));
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                int index = i * colsB + j;
                int sum = 0;
                for (int k = 0; k < colsA; k++) {
                    sum += matA.get(i * colsA + k) * matB.get(k * colsB + j);
                }
                result.set(index, sum);
            }
        }
        return result;
    }
}
