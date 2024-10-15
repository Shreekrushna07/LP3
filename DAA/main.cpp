#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

// Function for standard matrix multiplication
vector<vector<int>> matrixMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B, int n) {
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function for multithreading (one thread per row)
void multiplyRow(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &result, int row, int n) {
    for (int j = 0; j < n; ++j) {
        result[row][j] = 0;
        for (int k = 0; k < n; ++k) {
            result[row][j] += A[row][k] * B[k][j];
        }
    }
}

void matrixMultiplyThreadPerRow(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &result, int n) {
    vector<thread> threads;
    for (int i = 0; i < n; ++i) {
        threads.push_back(thread(multiplyRow, cref(A), cref(B), ref(result), i, n));
    }
    for (auto &t : threads) {
        t.join();
    }
}

// Function for multithreading (one thread per cell)
void multiplyCell(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &result, int row, int col, int n) {
    result[row][col] = 0;
    for (int k = 0; k < n; ++k) {
        result[row][col] += A[row][k] * B[k][col];
    }
}

void matrixMultiplyThreadPerCell(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &result, int n) {
    vector<thread> threads;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            threads.push_back(thread(multiplyCell, cref(A), cref(B), ref(result), i, j, n));
        }
    }
    for (auto &t : threads) {
        t.join();
    }
}

void inputMatrix(vector<vector<int>> &matrix, int n, const string &name) {
    cout << "Enter elements of matrix " << name << " (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(const vector<vector<int>> &matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of matrices (n x n): ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> result(n, vector<int>(n, 0));

    // Input matrices
    inputMatrix(A, n, "A");
    inputMatrix(B, n, "B");

    int choice;
    cout << "Select matrix multiplication method:\n";
    cout << "1. Standard Multiplication\n";
    cout << "2. Multithreading (One Thread Per Row)\n";
    cout << "3. Multithreading (One Thread Per Cell)\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;

    auto start = high_resolution_clock::now();
    switch (choice) {
        case 1:
            // Standard multiplication
            result = matrixMultiply(A, B, n);
            break;
        case 2:
            // Multithreading (One Thread Per Row)
            matrixMultiplyThreadPerRow(A, B, result, n);
            break;
        case 3:
            // Multithreading (One Thread Per Cell)
            matrixMultiplyThreadPerCell(A, B, result, n);
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    // Show the result
    cout << "\nResult Matrix:\n";
    printMatrix(result, n);

    cout << "\nMatrix multiplication completed in " << duration << " ms.\n";

    return 0;
}