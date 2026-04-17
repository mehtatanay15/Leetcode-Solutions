// LeetCode 240: Search a 2D Matrix II
// Problem: Search for a target value in a 2D matrix
// Approach: Filter rows by range check, then binary search within the row

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        for(int i = 0; i < m; i++) {
            // Check if target can be in this row
            // (target is between first and last element of the row)
            if(target >= matrix[i][0] && target <= matrix[i][n-1]) {
                int l = 0;
                int r = n - 1;

                // Binary search within this row
                while(l <= r) {
                    int mid = (l + r) / 2;

                    if(target == matrix[i][mid]) {
                        return true;
                    }
                    else if(target <= matrix[i][mid]) {
                        r = mid - 1;
                    }
                    else {
                        l = mid + 1;
                    }
                }
            }
        }

        return false;
    }
};

/*
SOLUTION 1: Binary Search + Range Check
Time Complexity: O(m * log n)
- m rows to check
- log n for binary search in each row (n columns)

Space Complexity: O(1) - only using constant extra space

Algorithm:
1. Iterate through each row
2. Check if target falls within the range [first, last] of current row
3. If yes, perform binary search on that row
4. Return true if found, else continue to next row
5. Return false if not found in any row

Optimization:
- Range check prevents binary search on rows where target cannot exist
- This makes the algorithm efficient for matrices

Example 1:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 13
Output: true

Example 3:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
*/

// SOLUTION 2: Two-Pointer Approach (More Optimized)
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int row = 0;
        int col = n - 1;

        // Start from top-right corner
        while(row < m && col >= 0) {
            if(matrix[row][col] == target)
                return true;
            else if(matrix[row][col] > target)
                col--;   // move left (decrease value)
            else
                row++;   // move down (increase value)
        }

        return false;
    }
};

/*
SOLUTION 2: Two-Pointer (Staircase Search)
Time Complexity: O(m + n)
- Worst case: traverse entire row and column (m + n moves)
- Each move eliminates one row or one column

Space Complexity: O(1) - only using constant extra space

Algorithm:
1. Start from top-right corner (row = 0, col = n-1)
   OR from bottom-left corner (row = m-1, col = 0)
2. Compare target with current element:
   - If equal, return true
   - If target > current, move down (row++) - need larger values
   - If target < current, move left (col--) - need smaller values
3. If we go out of bounds, return false

Why this works:
- Starting from top-right: elements to the left are smaller, elements below are larger
- Each comparison eliminates an entire row or column
- Much more efficient than checking each element individually

Advantages:
- Simpler to understand and implement
- Better time complexity: O(m + n) vs O(m * log n)
- Clean and elegant solution

Example:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 13

Step-by-step:
- Start: row=0, col=4, matrix[0][4]=15
  15 > 13, move left (col=3)
- row=0, col=3, matrix[0][3]=11
  11 < 13, move down (row=1)
- row=1, col=3, matrix[1][3]=12
  12 < 13, move down (row=2)
- row=2, col=3, matrix[2][3]=16
  16 > 13, move left (col=2)
- row=2, col=2, matrix[2][2]=9
  9 < 13, move down (row=3)
- row=3, col=2, matrix[3][2]=14
  14 > 13, move left (col=1)
- row=3, col=1, matrix[3][1]=13
  13 == 13, return true ✓

Recommendation: Use Solution2 (Two-Pointer) for better time complexity!
*/
