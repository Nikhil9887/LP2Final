#include <bits/stdc++.h>
using namespace std;

class NQueen
{
    int n;

public:
    NQueen(int val) { n = val; }

    bool backtracking()
    {
        vector<vector<char>> board(n, vector<char>(n, '.'));

        return solveBackTracking(0, board);
    }

    void display(vector<vector<char>> &board)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool isSafe(int row, int col, vector<vector<char>> &board)
    {
        int dupRow = row;
        int dupCol = col;
        while (row >= 0 && col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
            row--;
            col--;
        }

        row = dupRow;
        col = dupCol;

        while (row < n && col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
            row++;
            col--;
        }
        row = dupRow;
        col = dupCol;

        while (col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
            col--;
        }
        return true;
    }

    bool solveBackTracking(int col, vector<vector<char>> &board)
    {
        if (col == n)
        {
            display(board);
        }
        for (int row = 0; row < n; row++)
        {
            if (isSafe(row, col, board))
            {
                board[row][col] = 'Q';
                if (solveBackTracking(col + 1, board))
                {
                    return true;
                }
                board[row][col] = '.';
            }
        }

        return false;
    }

    void bnb()
    {
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<int> remainingRows(n, 0);
        vector<int> upperDiagonal(2 * n - 1, 0);
        vector<int> lowerDiagonal(2 * n - 1, 0);
        return bnbSolver(0, remainingRows, lowerDiagonal, upperDiagonal, board);
    }

    void bnbSolver(int col, vector<int> &remainingRows, vector<int> lowerDiagonal, vector<int> upperDiagonal, vector<vector<char>> &board)
    {
        if (col == n)
        {
            display(board);
            return;
        }
        for (int row = 0; row < n; row++)
        {
            if (remainingRows[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 - row + col] == 0)
            {
                board[row][col] = 'Q';
                remainingRows[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                bnbSolver(col + 1, remainingRows, lowerDiagonal, upperDiagonal, board);
                board[row][col] = '.';
                remainingRows[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }
};

int main()
{
    cout << "Enter the number of queens : ";
    int n;
    cin >> n;
    NQueen obj(n);
    // obj.backtracking();
    obj.bnb();
    return 0;
}