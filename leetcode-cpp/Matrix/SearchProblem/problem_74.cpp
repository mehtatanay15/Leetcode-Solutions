// LeetCode 74: Search a 2D Matrix
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

Assumptions:
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
- This makes the algorithm efficient for sparse matrices

Example:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Explanation:
- Row 0: [1,3,5,7], 3 is in range [1,7] → Binary search finds 3 at index 1
- Return true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

Explanation:
- Row 0: [1,3,5,7], 13 not in range [1,7] → skip
- Row 1: [10,11,16,20], 13 in range [10,20] → Binary search doesn't find 13
- Row 2: [23,30,34,60], 13 not in range [23,60] → skip
- Return false

More Optimal Solution (O(log m + log n)):
Could treat the entire matrix as a 1D sorted array and use single binary search,
but this solution is more intuitive and still efficient.
*/
