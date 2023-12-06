#include <bits/stdc++.h>
#define N 4
using namespace std;
 
// A utility function to print solution
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
           if(board[i][j])
            cout << "Q ";
           else cout<<". ";
        printf("\n");
    }
}
 
// A utility function to check if a queen can
// be placed on board[row][col]. Note that this
// function is called when "col" queens are
// already placed in columns from 0 to col -1.
// So we need to check only left side for
// attacking queens
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
 
    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;
 
    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
 
    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;
 
    return true;
}
 
// A recursive utility function to solve N
// Queen problem
bool solveNQUtil(int board[N][N], int col)
{
    // base case: If all queens are placed
    // then return true
    if (col >= N)
        return true;
 
    // Consider this column and try placing
    // this queen in all rows one by one
    for (int i = 0; i < N; i++) {
         
        // Check if the queen can be placed on
        // board[i][col]
        if (isSafe(board, i, col)) {
             
            // Place this queen in board[i][col]
            board[i][col] = 1;
 
            // recur to place rest of the queens
            if (solveNQUtil(board, col + 1))
                return true;
 
            // If placing queen in board[i][col]
            // doesn't lead to a solution, then
            // remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }
 
    // If the queen cannot be placed in any row in
    // this column col  then return false
    return false;
}
 
// This function solves the N Queen problem using
// Backtracking. It mainly uses solveNQUtil() to
// solve the problem. It returns false if queens
// cannot be placed, otherwise, return true and
// prints placement of queens in the form of 1s.
// Please note that there may be more than one
// solutions, this function prints one  of the
// feasible solutions.
bool solveNQ()
{
    int board[N][N] = { { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 } };
 
    if (solveNQUtil(board, 0) == false) {
        cout << "Solution does not exist";
        return false;
    }
 
    printSolution(board);
    return true;
}
 
// Driver program to test above function
int main()
{
    solveNQ();
    return 0;
}

output:
. . Q .
Q . . .
. . . Q
. Q . .
...........................................................................................................

#include <iostream>

#define N 8 // Define the size of the chessboard

// Function to print the chessboard
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << (board[i][j] ? 'Q' : '.') << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    // Check the column on the left
    for (int i = 0; i < row; i++) {
        if (board[i][col])
            return false;
    }

    // Check upper diagonal on the left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    // Check lower diagonal on the left
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j])
            return false;
    }

    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueensUtil(int board[N][N], int row) {
    if (row == N) {
        // All queens are placed successfully
        printBoard(board);
        return true; // Return true to find the first solution
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place the queen

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, row + 1))
                return true; // Stop recursion after finding the first solution

            board[row][col] = 0; // Backtrack if placing a queen doesn't lead to a solution
        }
    }

    return false;
}

// Main function to solve the N-Queens problem
void solveNQueens() {
    int board[N][N] = {{0}};

    if (!solveNQueensUtil(board, 0)) {
        std::cout << "Solution does not exist for " << N << " queens." << std::endl;
    }
}

// Driver program
int main() {
    solveNQueens();
    return 0;
}
output: 
Q . . . . . . .
. . . . Q . . .
. . . . . . . Q
. . . . . Q . .
. . Q . . . . .
. . . . . . Q .
. Q . . . . . .
. . . Q . . . .