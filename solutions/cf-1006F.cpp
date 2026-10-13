#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

using int64 = long long;
using XorCount = unordered_map<int64, int64>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, columns;
    int64 target_xor;
    cin >> rows >> columns >> target_xor;

    vector<vector<int64>> grid(rows, vector<int64>(columns));
    for (auto &row : grid) {
        for (int64 &value : row) cin >> value;
    }

    // Every valid path uses this fixed number of moves.  We stop the forward
    // search after half of them, so every partial path lands on one common
    // anti-diagonal.  A backward path with the remaining moves lands there too.
    const int total_moves = rows + columns - 2;
    const int forward_moves = total_moves / 2;
    const int backward_moves = total_moves - forward_moves;

    // forward_xors[r][c][x] counts forward partial paths that reach (r,c)
    // and whose XOR, including both endpoints, is x.
    vector<vector<XorCount>> forward_xors(
        rows, vector<XorCount>(columns));

    auto enumerate_forward = [&](auto &&self, int row, int column,
                                 int moves_used, int64 path_xor) -> void {
        if (moves_used == forward_moves) {
            ++forward_xors[row][column][path_xor];
            return;
        }

        // Moving only down or right means every generated route is a valid
        // monotone prefix; boundary checks discard impossible branches.
        if (row + 1 < rows) {
            self(self, row + 1, column, moves_used + 1,
                 path_xor ^ grid[row + 1][column]);
        }
        if (column + 1 < columns) {
            self(self, row, column + 1, moves_used + 1,
                 path_xor ^ grid[row][column + 1]);
        }
    };

    enumerate_forward(enumerate_forward, 0, 0, 0, grid[0][0]);

    int64 answer = 0;
    auto enumerate_backward = [&](auto &&self, int row, int column,
                                  int moves_used, int64 path_xor) -> void {
        if (moves_used == backward_moves) {
            // Both half-XORs include the meeting cell.  XORing the two halves
            // therefore cancels that value; xor it once more to include it in
            // the complete path exactly once.
            const int64 needed_forward =
                target_xor ^ path_xor ^ grid[row][column];
            auto found = forward_xors[row][column].find(needed_forward);
            if (found != forward_xors[row][column].end()) {
                answer += found->second;
            }
            return;
        }

        // Reverse the legal moves: from the finish we may go up or left.
        if (row > 0) {
            self(self, row - 1, column, moves_used + 1,
                 path_xor ^ grid[row - 1][column]);
        }
        if (column > 0) {
            self(self, row, column - 1, moves_used + 1,
                 path_xor ^ grid[row][column - 1]);
        }
    };

    enumerate_backward(enumerate_backward, rows - 1, columns - 1, 0,
                       grid[rows - 1][columns - 1]);

    cout << answer << '\n';
    return 0;
}
