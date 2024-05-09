#include <bits/stdc++.h>
using namespace std;

class NQueens
{
private:
    int n;

public:
    NQueens(int val)
    {
        n = val;
    }

    void bnb()
    {
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<int> remainingRows(n, 0);
        vector<int> upperDiagonal(2 * n - 1, 0);
        vector<int> lowerDiagonal(2 * n - 1, 0);

        return bnbSolver(0, remainingRows, upperDiagonal, lowerDiagonal, board);
    }

    void bnbSolver(int col, vector<int> &remainingRows, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, vector<vector<char>> &board)
    {
        if (col == n)
        {
            display(board);
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (remainingRows[row] == 0 && lowerDiagonal[col + row] == 0 && upperDiagonal[n - 1 - row + col] == 0)
            {
                board[row][col] = 'Q';
                remainingRows[row] = 1;
                lowerDiagonal[col + row] = 1;
                upperDiagonal[n - 1 - row + col] = 1;

                bnbSolver(col + 1, remainingRows, upperDiagonal, lowerDiagonal, board);

                board[row][col] = '.';
                remainingRows[row] = 0;
                lowerDiagonal[col + row] = 0;
                upperDiagonal[n - 1 - row + col] = 0;
            }
        }
    }

    vector<vector<vector<char>>> backTracking()
    {
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<vector<vector<char>>> ans;
        solveBackTracking(0, board, ans);

        return ans;
        // solveBackTracking(col, board);
    }

    bool isSafe(int row, int col, vector<vector<char>> &board)
    {
        int dupRow = row;
        int dupCol = col;

        // north-west diagonal
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

        // west
        while (col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
            col--;
        }

        row = dupRow;
        col = dupCol;

        // south-west diagonal
        while (row < n && col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
            row++;
            col--;
        }

        return true;
    }

    void solveBackTracking(int col, vector<vector<char>> &board, vector<vector<vector<char>>> &ans)
    {
        if (col == n)
        {
            display(board);
            ans.push_back(board);
            return;
        }
        for (int row = 0; row < n; row++)
        {
            if (isSafe(row, col, board))
            {
                board[row][col] = 'Q';
                solveBackTracking(col + 1, board, ans);
                board[row][col] = '.';
            }
        }
    }

    void display(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    NQueens obj(8);
    vector<vector<vector<char>>> ans;

    ans = obj.backTracking();
    cout << ans.size() << endl;

    return 0;
}