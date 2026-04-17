// LeetCode 1901: Find a Peak Element II
// Problem: Find a peak element in a 2D matrix (greater than all adjacent elements)
// Approach: Binary Search on Columns + Find Max Row in Column

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxRow(vector<vector<int>>& mat, int col) {
        int maxRow = 0;
        int m = mat.size();

        // Find the row with maximum element in the given column
        for(int i = 0; i < m; i++) {
            if(mat[i][col] > mat[maxRow][col]) {
                maxRow = i;
            }
        }
        return maxRow;
    }

    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int l = 0;
        int r = n - 1;

        // Binary search on columns
        while(l <= r) {
            int mid = (l + r) / 2;

            // Find row with maximum element in column mid
            int maxRow = findMaxRow(mat, mid);

            // Check left and right neighbors
            int left = (mid - 1 >= 0) ? mat[maxRow][mid - 1] : -1;
            int right = (mid + 1 < n) ? mat[maxRow][mid + 1] : -1;

            // If current element is greater than left and right, it's a peak
            if(mat[maxRow][mid] > left && mat[maxRow][mid] > right) {
                return {maxRow, mid};
            }
            // If left neighbor is larger, peak must be on the left
            else if(left > mat[maxRow][mid]) {
                r = mid - 1;
            }
            // Otherwise, peak must be on the right
            else {
                l = mid + 1;
            }
        }

        return {-1, -1};
    }
};

/*
Time Complexity: O(n * log m) where n = columns, m = rows
- Binary search on columns: O(log n)
- For each column, find max row: O(m)
- Total: O(m * log n)

Space Complexity: O(1) - only using constant extra space

Key Insight:
- A peak is an element greater than all 4 adjacent elements
- If we find the max element in a column, it's automatically greater than top/bottom
- We only need to check left and right neighbors
- Use binary search to find the column containing the peak

Algorithm:
1. Binary search on columns (l = 0, r = n-1)
2. For middle column, find row with maximum element
3. Check if this element is greater than left and right neighbors
4. If yes, return it as peak (guaranteed to be greater than top/bottom)
5. If left neighbor is larger, search left half (peak must be there)
6. If right neighbor is larger, search right half (peak must be there)

Why it works:
- At each step, we narrow down the column range containing the peak
- Since we pick the max in each column, the peak must exist in the direction
  of the larger neighbor
- The element that is the max in its column is also a local maximum vertically

Example:
Input: mat = [[1,4],[3,2]]
Output: [0,1]

Explanation:
- mat[0][1] = 4 is the peak
- 4 > 1 (left), 4 > 2 (right), 4 > 3 (below), and nothing above
- Peak found at (0, 1)

Example 2:
Input: mat = [[10,12,13],[14,11,15]]
Output: [1,2]

Explanation:
- mat[1][2] = 15 is the peak
- 15 > 13 (top), 15 > 11 (left)
- Peak found at (1, 2)
*/
