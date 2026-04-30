// LeetCode 3742: Maximize the Total Height of Unique Buildings (or similar grid path problem)
// Problem: Find the maximum path score in a grid where each cell has a cost and value
// Cost is 1 if grid[r][c] != 0, else 0. Limited by total moves k.
// Can only move right or down. Must reach bottom-right corner within k moves.
// Approach: 3D Dynamic Programming with Memoization (Top-Down)

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int m, n;
    // 3D vector to store memoized states: memo[r][c][rem_k]
    // Represents: maximum score starting from (r,c) with rem_k moves remaining
    vector<vector<vector<int>>> memo;

    int solve(int r, int c, int rem_k, const vector<vector<int>>& grid) {
        // Out of bounds check
        if (r >= m || c >= n) return -1e9;

        // Calculate cost and score for current cell
        int cost = (grid[r][c] == 0) ? 0 : 1;
        int score = grid[r][c];

        // Pruning: if not enough moves remaining, impossible
        if (rem_k < cost) return -1e9;

        // Base case: reached destination
        if (r == m - 1 && c == n - 1) {
            return score;
        }

        // Return memoized result if already computed
        if (memo[r][c][rem_k] != -1) {
            return memo[r][c][rem_k];
        }

        // Explore both possible moves
        int right = solve(r, c + 1, rem_k - cost, grid);
        int down = solve(r + 1, c, rem_k - cost, grid);

        // Take the maximum score from future paths
        int max_future_score = max(right, down);

        // If both paths are impossible, return impossible
        if (max_future_score <= -1e8) {
            return memo[r][c][rem_k] = -1e9;
        }

        // Return current score + best future score
        return memo[r][c][rem_k] = score + max_future_score;
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();
        
        // Optimization: minimum moves needed is m + n - 1 (manhattan distance)
        // No need to consider k larger than this
        k = min(k, m + n - 1);
        
        // Initialize 3D memoization table
        memo.assign(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));

        // Solve from top-left corner with k moves available
        int result = solve(0, 0, k, grid);

        // Return -1 if impossible, otherwise return the score
        return result < 0 ? -1 : result;
    }
};

/*
Time Complexity: O(m * n * k) - Each state (r, c, rem_k) is computed once
  - m rows, n columns, k possible remaining moves
  - Each state computation is O(1)
Space Complexity: O(m * n * k) - Memoization table + recursion stack O(m+n)

Algorithm:
1. Use 3D DP where memo[r][c][rem_k] = max score from (r,c) with rem_k moves left
2. From each cell, recursively explore right and down moves
3. Calculate cost: 1 if grid[r][c] != 0, else 0
4. Prune impossible branches:
   - Out of bounds → return -1e9
   - Not enough moves → return -1e9
   - Both child paths impossible → return -1e9
5. Memoize to avoid recomputation
6. Return max score or -1 if unreachable

Key Insights:
- 3D memoization needed because same cell can be visited with different k values
- Optimization: k never needs to exceed m+n-1 (minimum manhattan distance)
- Each non-zero cell costs 1 move, zero cells cost 0
- Must reach bottom-right corner within k moves
- Greedy doesn't work; need DP to explore all possibilities

Example:
Grid:    k = 5
[1, 2]
[3, 0]

Paths:
- (0,0) → (0,1) → (1,1): cost=1+1+0=2, score=1+2+0=3 ✓
- (0,0) → (1,0) → (1,1): cost=1+1+0=2, score=1+3+0=4 ✓
- Best: score = 4

State Pruning:
- If rem_k < cost: can't even visit current cell
- If max(right, down) <= -1e8: both children are unreachable
- These pruning strategies significantly reduce computation
*/
