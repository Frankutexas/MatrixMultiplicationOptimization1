# MatrixMultiplicationOptimization1
Matrix Multiplication using 1D dynamic arrays comparison with 2D dynamic arrays

In a previous article, I compared the performance of Golang, C/C++, Java, and Python by observing the runtime of a simple matrix multiplication algorithm using 2D arrays. This approach employed an O(N*M*L) algorithm, where N is the row length of the first matrix, M is the column length of the first matrix, and L is the column length of the second matrix. I tested using 2D arrays because it provided the most simple and intuitive implementation of matrix multiplication. Additionally, statically allocated arrays are much more efficient than resizable arrays such as ArrayLists in Java, vectors in C/C++, or slices in Golang. The conclusion was that for 2D matrix multiplication C/C++ was indeed the fastest, with Java being second, Golang third, and Python last.

However, while using statically allocated arrays is more efficient, it requires the user to have prior knowledge of the dimensions of the matrices involved, which may not always be the case in industry. For this reason, I decided to test the performance again, using the same algorithm but this time with resizable arrays instead of statically allocated arrays. For this test, I wanted to use square matrices instead as these matrices are very commonly used in machine learning and singular value decomposition. I kept the dataset for 5 different inputs repeated 80 times that I did for the previous test for a reference point and also added 5 new unique inputs for square matrices of row and column length 100. These were the results:

Table 1. Two Dimensional Dynamic Array Approach
| Trial | C/C++ | Go | Java | Python |
|-------------------------------------------------|--------|---------|---------|-----------|
| 400 repetitions with 100x100 square matrices | 606 ms | 1,061 ms | 1,861 ms | 49,834 ms |
| 400 repetitions with 100x150 & 150x100 matrices | 570 ms | 1,346 ms | 2,398 ms | 73,245 ms |

In this test, it can be seen that C/C++ had the fastest performance yet again. However, this time, Golang outperformed Java with a little more than half the runtime of Java’s. Python as usual was the slowest, which is understandable as it is the only interpreted language.

Table 2. Static vs Dynamic for 100x150 and 150x100 Matrices
| Approach | C/C++ | Go | Java | Python |
|----------|--------|----------|---------|-----------|
| Dynamic | 606 ms | 1,061 ms | 1,861 ms | 49,834 ms |
| Static | 228 ms | 1,118 ms | 625 ms | \* |

In this test, it can be seen that C/C++ and Java both performed noticeably slower when using dynamically allocated arrays as opposed to statically allocated arrays. Interestingly, Go did not perform faster when using a static array and performed about the same with a static array.

Dynamic arrays are less efficient than static arrays in three important areas:

Memory Allocation Overhead - Every time an array needs to be resized it will need to allocate a larger block of memory. Because the size of the array is unknown, more memory than needed will usually be assigned whenever the array needs to grow.
Cache Performance - Due to frequent resizing, dynamic arrays are often not friendly to locality of memory and can very often have non-contiguous memory which can slow down performance.
Access Speed - Accessing memory in a dynamic array may require an extra layer of access, usually in the form of pointers or references, both of which add a slight increase to overhead.

One way to increase performance and reduce the runtime when using dynamic arrays for matrix multiplication is to let a one dimensional array represent the matrix as opposed to using a two dimensional array. There are two important reasons why a one dimensional approach should be more efficient than a two dimensional array. First, unlike a 2D dynamic array, 1D dynamic arrays are stored in contiguous memory, which reduces access overhead and optimizes cache locality. Second, instead of needing two separate lookups, an element in the matrix can be found by a single lookup.

In order to use a one dimensional approach, the matrix multiplication method needs to be adjusted to use row major form like so.

Using the above algorithm, the row and column of any element can be identified using a simple calculation without the need of pointers or references.

I ran the test again using the same two datasets; this time using the 1D approach. The results were mixed.

Table 3. One Dimensional Dynamic Array Approach
| Trial | C/C++ | Go | Java | Python |
|-------------------------------------------------|---------|----------|----------|-----------|
| 400 repetitions with 100x100 square matrices | 334 ms | 1,520 ms | 2,037 ms | 105,236 ms |
| 400 repetitions with 100x150 & 150x100 matrices | 489 ms | 1,826 ms | 3,632 ms | 156,461 ms |

For C/C++ no matter how many times the tests were run, the 1D approach was always faster than the 2D approach by a significant amount. However, for Go and Java, the results were inconclusive. Sometimes the 1D approach would come out on top but most of the time the 2D approach was actually faster and the times would vary significantly every run. I figured that it was possible the matrix sizes were not large enough to fully show the advantage of data locality. I decided that the best way to determine the efficacy of the 1D approach was to increase the size of the matrices.

I ran the test again. This time, instead of using 100x100 and 150x100 matrices, I would use 1000x1000 matrices. This way, the overhead created by memory allocation and cache optimization should be much more clear. These were the results:

Table 4. 1D vs 2D approach using a 1000x1000 matrix
| Approach | C/C++ | Go | Java | Python |
|----------|--------|---------|---------|----------|
| 1D | 1,915 ms | 15,948 ms | 4,937 ms | 299,273 ms |
| 2D | 2,601 ms | 13,848 ms | 30,364 ms | 148,678 ms |

The 2D approach for C/C++ was slower than the 1D approach by about 1.37 times which was significant. For Go, the difference was much smaller but still definitely in favor of the 2D approach. For Java, the 2D approach was six times slower than the 1D approach. Python was the reverse, the 1D approach was twice as slow as the 2D approach.

Below is a table showing the performance improvement when using 1D over 2D. For each entry I have the 2D time, the 1D time, then the “improvement” as a percentage with the 2D time as the baseline. For reference the performance improvement is calculated as followed:
(2D-1D)/2D \* 100%.

Table 5. 1D vs 2D Performance Comparison
| Language | 100x100 | 150x100 | 1000x1000 |
|----------|---------|---------|-----------|
| C/C++ | 334 ms (1D)<br>606 ms (2D)<br>44.9% | 489 ms (1D)<br>570 ms (2D)<br>14.2% | 1,915 ms (1D)<br>2,601 ms (2D)<br>26.4% |
| Go | 1,520 ms (1D)<br>1,061 ms (2D)<br>-43.3% | 1,826 ms (1D)<br>1,346 ms (2D)<br>-35.7% | 15,948 ms (1D)<br>13,848 ms (2D)<br>-15.2% |
| Java | 2,037 ms (1D)<br>1,861 ms (2D)<br>-9.0% | 3,632 ms (1D)<br>2,398 ms (2D)<br>-51.5% | 4,937 ms (1D)<br>30,364 ms (2D)<br>83.7% |
| Python | 105,236 ms (1D)<br>49,834 ms (2D)<br>-111.1% | 156,461 ms (1D)<br>73,245 ms (2D)<br>-113.6% | 299,273 ms (1D)<br>148,678 ms (2D)<br>-101.3% |

In conclusion, while the C/C++ results were as expected, the rest were definitely surprising.

C/C++ - In every trial and every matrix size, the 1D approach was consistently faster than the 2D approach by a factor of about 1.37 times.
Golang - For the 100x100 and 150x100 matrices, the results varied, but over repeated trials the 2D slightly outperformed the 1D approach overall. For the 1000x1000 matrix, the 2D approach outperformed the 1D approach but by a small margin of 13.2%.
Java - For the smaller matrices the 1D approach actually outperformed the 2D approach by 1.26 times for the 100x100 matrices and 1.66 times for the 100x150 matrices. However, for the 1000x1000 matrix, the 1D approach was vastly superior to the 2D with a performance that was 6 times as fast
Python - For every trial the 2D approach outperformed the 1D approach by a factor of 2.

In addition, this test has confirmed, similar to the first test with 2D static arrays, that C/C++ is the fastest, Java is the second, Golang was third, and Python was the fourth.
