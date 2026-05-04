// LeetCode 48: Rotate Image
// Problem: Rotate a 2D matrix 90 degrees clockwise in-place
// Approach: Transpose + Reverse each row

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Step 1: Transpose the matrix
        // Swap matrix[i][j] with matrix[j][i]
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for(int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

/*
Time Complexity: O(n²) - Visit every element exactly once for operations
Space Complexity: O(1) - In-place rotation, only constant extra space needed

Algorithm Explanation:
The key insight is that a 90-degree clockwise rotation equals:
1. Transpose the matrix (flip along main diagonal)
2. Reverse each row

Step 1 - Transpose (Convert [i][j] to [j][i]):
- Swap elements across the main diagonal
- This makes rows become columns

Step 2 - Reverse each row:
- Flip the order of elements in each row
- This completes the 90-degree clockwise rotation

Mathematical Insight:
- Transpose operation: (i, j) → (j, i)
- Reverse operation: (j, i) → (i, n-1-j)
- Combined: (i, j) → (j, n-1-i) which is exactly 90° clockwise rotation

Example:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]

After Transpose (swap [i][j] with [j][i]):
[[1,4,7],[2,5,8],[3,6,9]]

After Reversing each row:
[[7,4,1],[8,5,2],[9,6,3]]

Output: [[7,4,1],[8,5,2],[9,6,3]]

Visual Transformation:
Original:        Transpose:       Reverse rows:
1 2 3            1 4 7            7 4 1
4 5 6    --->    2 5 8    --->    8 5 2
7 8 9            3 6 9            9 6 3

Rotation Direction Verification:
- Original top-left (1) should go to top-right (1) → moved to [0][2] ✓
- Original top-middle (2) should go to middle-right (2) → moved to [1][2] ✓
- Original left-middle (4) should go to top-middle (4) → moved to [0][1] ✓

Alternative Approaches:
- Layer-by-layer rotation: O(n²) time, O(1) space (more complex code)
- Rotate 4 corners at a time: O(n²) time, O(1) space (harder to implement)
- Current approach (Transpose + Reverse): Best code simplicity with optimal complexity
*/
