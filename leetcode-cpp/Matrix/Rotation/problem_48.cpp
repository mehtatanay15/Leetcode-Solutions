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
Time Complexity: O(n^2) - must visit every element once
Space Complexity: O(1) - in-place rotation, only using constant extra space

Algorithm Explanation:
1. Transpose: Convert [i][j] to [j][i]
   - Swaps elements across the main diagonal
2. Reverse each row: Reverse elements in each row

Example:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]

After Transpose:
[[1,4,7],[2,5,8],[3,6,9]]

After Reversing each row:
[[7,4,1],[8,5,2],[9,6,3]]

Output: [[7,4,1],[8,5,2],[9,6,3]]

Visual:
Original:        Transpose:       Reverse rows:
1 2 3            1 4 7            7 4 1
4 5 6    --->    2 5 8    --->    8 5 2
7 8 9            3 6 9            9 6 3

This represents a 90-degree clockwise rotation.
*/
