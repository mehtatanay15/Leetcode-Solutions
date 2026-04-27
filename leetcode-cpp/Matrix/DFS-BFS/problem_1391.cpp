// LeetCode 1391: Check if There is a Valid Path in a Grid
// Problem: Given a grid where each cell contains a street type with specific directions,
// find if there's a valid path from top-left (0,0) to bottom-right (m-1,n-1)
// A valid path requires streets to connect bidirectionally
// Approach: BFS with direction validation and bidirectional connectivity check

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Define street directions: {row_offset, col_offset}
        // Street 1: left, right (horizontal)
        // Street 2: up, down (vertical)
        // Street 3: left, down (L-shaped)
        // Street 4: right, down (L-shaped)
        // Street 5: left, up (L-shaped)
        // Street 6: right, up (L-shaped)
        vector<vector<pair<int, int>>> directions = {
            {}, // index 0 unused
            {{0, -1}, {0, 1}},  // 1: left, right
            {{-1, 0}, {1, 0}},  // 2: up, down
            {{0, -1}, {1, 0}},  // 3: left, down
            {{0, 1}, {1, 0}},   // 4: right, down
            {{0, -1}, {-1, 0}}, // 5: left, up
            {{0, 1}, {-1, 0}}   // 6: right, up
        };

        queue<pair<int, int>> q;
        q.push({0, 0});
        
        // Track visited cells to avoid revisiting
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[0][0] = true;

        // BFS traversal
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Check if we reached the destination
            if (r == m - 1 && c == n - 1) return true;

            // Get the street type at current cell
            int streetType = grid[r][c];
            
            // Explore all possible directions from current street
            for (auto& dir : directions[streetType]) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                // Check boundaries and if already visited
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    int nextStreet = grid[nr][nc];
                    bool canConnect = false;
                    
                    // Check if the next street has a pipe that points back to current cell
                    // This ensures bidirectional connectivity
                    for (auto& backDir : directions[nextStreet]) {
                        if (nr + backDir.first == r && nc + backDir.second == c) {
                            canConnect = true;
                            break;
                        }
                    }

                    // If streets connect bidirectionally, add to queue
                    if (canConnect) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return false;
    }
};

/*
Time Complexity: O(m * n) - Visit each cell at most once during BFS
Space Complexity: O(m * n) - visited array + queue (worst case O(m*n))

Algorithm:
1. Define street type directions:
   - Type 1: horizontal (left-right)
   - Type 2: vertical (up-down)
   - Type 3,4,5,6: L-shaped (different combinations)

2. Use BFS starting from (0, 0):
   - Mark current cell as visited
   - Get the current street type and its allowed directions
   - For each allowed direction:
     * Calculate next cell coordinates
     * Check if next cell is within bounds and unvisited
     * Validate bidirectional connectivity:
       - Current street points to next cell
       - Next street has a direction pointing back to current cell
     * If valid, mark visited and enqueue next cell

3. Return true if destination (m-1, n-1) is reached, false otherwise

Key Insight:
- Bidirectional connectivity check prevents dead paths
- Cannot move in a direction just because current street allows it
- The next street must also have a pipe pointing back
- This ensures a valid continuous path through the grid

Example:
Grid:
  [2,4,3]
  [6,5,2]

Streets: 2=up-down, 4=right-down, 3=left-down, 6=right-up, 5=left-up

Path: (0,0) → (1,0) → (1,1) → (1,2)
- (0,0) street 2 can go down to (1,0)
- (1,0) street 6 has right-up, pointing back to (0,0) ✓
- (1,0) can go right to (1,1)
- (1,1) street 5 has left-up, pointing back to (1,0) ✓
- And so on...
*/
