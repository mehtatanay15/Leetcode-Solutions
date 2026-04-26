// LeetCode 1559: Detect Cycle in 2D Grid
// Problem: Given a 2D grid of characters, detect if there's a cycle of the same character
// A cycle is formed when a cell can reach itself through adjacent cells with the same character
// Approach: DFS with parent tracking to detect cycles in connected components

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        // 2D array to store visited positions
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        // Try DFS from every unvisited cell
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // If not visited, start a DFS from this cell
                if (!visited[i][j]) {
                    if (dfs(grid, visited, i, j, -1, -1, grid[i][j])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, 
             int r, int c, int pr, int pc, char target) {
        visited[r][c] = true;

        // Directions: Right, Down, Left, Up
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // 1. Check boundaries
            // 2. Check if the character is the same
            if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] == target) {
                
                // If the next cell is visited and is NOT the cell we just came from (parent)
                // then we have found a cycle.
                if (visited[nr][nc] && (nr != pr || nc != pc)) {
                    return true;
                }
                
                // If not visited, continue the path
                if (!visited[nr][nc]) {
                    if (dfs(grid, visited, nr, nc, r, c, target)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

/*
Time Complexity: O(m * n) - Visit each cell at most once
Space Complexity: O(m * n) - visited array + recursion stack (worst case O(m*n))

Algorithm:
1. Create a visited array to track cells that have been explored
2. Iterate through each cell in the grid
3. For unvisited cells, perform DFS:
   - Mark current cell as visited
   - Explore all 4 adjacent neighbors (up, down, left, right)
   - For each neighbor that has the same character:
     * If visited AND not the parent cell → CYCLE FOUND
     * If not visited → recursively explore
4. Return true if any cycle is detected, false otherwise

Key Insight:
- Track parent (pr, pc) to avoid false positive cycle detection
- A cycle requires reaching a visited cell that is NOT the parent
- This prevents marking the immediate previous cell as a cycle
- Each connected component of same character is checked independently

Example:
Grid:
  a b a
  b a b
  a b a

Starting from (0,0) 'a':
- Explore (0,2) 'a', (2,0) 'a', (2,2) 'a'
- From (2,2) can reach (2,0) through (2,1) → Cycle detected!

Cycle: (0,0) → (0,2) → (2,2) → (2,0) → back to (0,0) via other paths
*/
