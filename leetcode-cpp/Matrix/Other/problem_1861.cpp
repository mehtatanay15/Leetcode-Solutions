// LeetCode 1861: Rotate the Box
// Problem: A box has stones (#), obstacles (*), and empty spaces (.)
// First apply gravity (stones fall to bottom), then rotate the box 90 degrees clockwise
// Approach: Two-phase approach - Apply gravity to each row, then rotate the matrix

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size();      // number of rows
        int n = box[0].size();   // number of columns

        // Phase 1: Apply gravity to each row
        // Stones (#) fall to the right until they hit an obstacle (*) or another stone
        for (int i = 0; i < m; i++) {
            int empty = n - 1;  // Position to place next stone from right

            // Traverse row from right to left
            for (int j = n - 1; j >= 0; j--) {
                // If obstacle found, reset empty position to just before it
                if (box[i][j] == '*') {
                    empty = j - 1;
                }
                // If stone found, move it to the nearest empty position
                else if (box[i][j] == '#') {
                    swap(box[i][j], box[i][empty]);
                    empty--;
                }
                // If empty space, continue (no action needed)
            }
        }

        // Phase 2: Rotate 90 degrees clockwise
        // New matrix dimensions: columns become rows
        vector<vector<char>> ans(n, vector<char>(m));

        // For 90° clockwise rotation:
        // Element at [i][j] in original goes to [j][m-1-i] in rotated
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans[j][m - 1 - i] = box[i][j];
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(m * n) - Two passes through the matrix
  - Phase 1 (Gravity): O(m * n) - traverse each cell once
  - Phase 2 (Rotation): O(m * n) - traverse each cell once
  - Total: O(m * n)
Space Complexity: O(m * n) - Creating new rotated matrix (required for output)

Algorithm Explanation:

Phase 1 - Apply Gravity:
1. For each row, process from right to left
2. Maintain an 'empty' pointer that tracks where next stone should be placed
3. For each position:
   - If obstacle (*): reset empty to just before obstacle
   - If stone (#): swap with position at 'empty', move empty left
   - If empty (.): skip
4. This makes stones fall to the right (simulating gravity in rotated perspective)

Phase 2 - Rotate 90° Clockwise:
1. Create new matrix with swapped dimensions (n × m)
2. For element at [i][j]: place it at [j][m-1-i]
   - Row i becomes column j
   - Column j becomes row (m-1-i)

Coordinate Transformation for 90° Clockwise Rotation:
Original matrix (m×n):
  [0][0]  [0][1]  ...  [0][n-1]
  [1][0]  [1][1]  ...  [1][n-1]
  ...
  [m-1][0] [m-1][1] ... [m-1][n-1]

Rotated matrix (n×m):
  [0][m-1]  [1][m-1]  ...  [m-1][m-1]
  [0][m-2]  [1][m-2]  ...  [m-1][m-2]
  ...
  [0][0]    [1][0]    ...  [m-1][0]

Example:
Input:
box = [["#",".","#"]]
k = 3 (but we only rotate once)

Row dimensions: m=1, n=3

Step 1 - Gravity:
["#",".","#"] → [".","#","#"] (stones fall right)

Step 2 - Rotation (90° clockwise):
Original (1×3): [".","#","#"]

After rotation (3×1):
["."]
["#"]
["#"]

Output: [["."],["#"],["#"]]

Complex Example:
Input: box = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]

Step 1 - Gravity on each row:
Row 0: ["#","#","*",".","*","."] → ["#","#","*",".","*","."] (no change)
Row 1: ["#","#","#","*",".","."] → [".",".","#","#","*","#"]... wait that's not right
Row 1: ["#","#","#","*",".","."] → [".","#","#","#","*","."] (3 stones fall right, stopped by *)

Actually for gravity going RIGHT (simulating gravity before rotation):
- Stones move towards the end of row (right)
- Obstacles stop movement

Step 2 - Rotate 90° clockwise
The resulting rotated matrix has dimensions reversed.

Key Insights:
- Gravity is applied BEFORE rotation
- "Gravity" in the original matrix means stones fall RIGHT (to simulate falling DOWN after rotation)
- Obstacles act as barriers that prevent stones from falling further
- The rotation transforms the coordinate system
- Order matters: gravity first, then rotation

Edge Cases:
- All stones: they all fall right
- All obstacles: nothing changes in gravity phase
- Empty box: no change
- Single row/column: still rotates correctly
*/
