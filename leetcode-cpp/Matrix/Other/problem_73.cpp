// LeetCode 73: Set Matrix Zeroes
// Problem: Set entire row and column to 0 if an element is 0
// Approach: Use sets to track rows and columns that need to be zeroed, then update matrix

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        set<int> rows;
        set<int> cols;
         
        // Step 1: Find all rows and columns that need to be zeroed
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        }

        // Step 2: Set elements to 0 if their row or column is marked
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(rows.count(i) || cols.count(j)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

/*
Time Complexity: O(m*n) - two passes through the matrix
Space Complexity: O(m + n) - for storing rows and columns indices in sets

Algorithm:
1. First pass: Store indices of rows and columns that contain 0
2. Second pass: Set all elements in marked rows/columns to 0

Example:
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Explanation:
- Found 0 at position (1,1)
- Mark row 1 and column 1 for zeroing
- Update all elements in row 1 and column 1 to 0

Alternative O(1) space solutions:
- Use first row/column as marker
- Use a single variable for first row/column flag
But this solution is cleaner and more intuitive with O(m+n) space.
*/
