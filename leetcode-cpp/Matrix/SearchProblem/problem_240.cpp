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
Time Complexity: O(m * log n)
- m rows to check
- log n for binary search in each row (n columns)

Space Complexity: O(1) - only using constant extra space

Constraints:
- Integers in each row are sorted from left to right
- Integers in each column are sorted from top to bottom

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

Alternative O(m + n) Solution:
Start from top-right or bottom-left corner:
- If target > current element, move down/left
- If target < current element, move left/up
- If equal, return true
This eliminates one dimension per comparison.
*/
