// LeetCode 2033: Minimum Operations to Make a Grid Equal
// Problem: Given a 2D grid and an integer x, find the minimum operations to make
// all grid elements equal. Each operation changes an element by exactly x.
// If it's impossible, return -1. Otherwise, return minimum operations needed.
// Approach: Greedy - Target the median value, check divisibility constraint

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        // Flatten the 2D grid into a 1D array
        vector<int> nums;
        for (auto& row : grid) {
            for (int val : row) nums.push_back(val);
        }

        // Sort the array
        sort(nums.begin(), nums.end());

        // Greedy choice: use median as the target value
        int median = nums[nums.size() / 2];

        int operations = 0;

        // Calculate operations needed to transform all elements to median
        for (int val : nums) {
            int diff = abs(median - val);
            
            // Check if difference is divisible by x (necessary condition)
            if (diff % x != 0) return -1;
            
            // Add the number of operations needed to close this gap
            operations += diff / x;
        }

        return operations;
    }
};

/*
Time Complexity: O(n log n) - Dominated by sorting where n is total elements (m*n)
Space Complexity: O(n) - Storing flattened array

Algorithm:
1. Flatten the 2D grid into a 1D array
2. Sort the array in ascending order
3. Choose the median as the target value (greedy choice)
4. For each element:
   - Calculate the absolute difference from the median
   - Check if difference is divisible by x (returns -1 if not)
   - Add operations needed: diff/x
5. Return total operations

Key Insight:
- The median is the optimal target to minimize operations
- Proof: For any sorted array, median minimizes sum of absolute deviations
- Each operation changes an element by exactly x
- If any element can't reach the target (diff not divisible by x), impossible

Why Median Works:
- Median minimizes the sum of absolute differences in any array
- For example, if we have [1, 5, 9]:
  - Target 5: |1-5| + |5-5| + |9-5| = 4 + 0 + 4 = 8
  - Target 6: |1-6| + |5-6| + |9-6| = 5 + 1 + 3 = 9 (worse)
  - Target 4: |1-4| + |5-4| + |9-4| = 3 + 1 + 5 = 9 (worse)

Divisibility Constraint:
- Each operation changes value by exactly x
- So (target - current) must be divisible by x
- All elements must have (median - value) % x == 0
- If not, it's impossible to make all equal

Example:
Grid:
  [2, 4]
  [6, 8]

x = 2
Flattened: [2, 4, 6, 8]
Median: 4 (at index 2)

Operations:
- 2 → 4: diff = 2, ops = 2/2 = 1
- 4 → 4: diff = 0, ops = 0/2 = 0
- 6 → 4: diff = 2, ops = 2/2 = 1
- 8 → 4: diff = 4, ops = 4/2 = 2

Total: 1 + 0 + 1 + 2 = 4 operations
*/
