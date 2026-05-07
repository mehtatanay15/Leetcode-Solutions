// LeetCode 3660: Find Maximum Value
// Problem: Partition array into components and return maximum value for each component
// A component can be separated when max(left part) <= min(right part)
// Approach: Prefix-Suffix preprocessing - Use prefixMax and suffixMin arrays

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Build prefixMax array
        // prefixMax[i] = maximum element from index 0 to i
        vector<int> prefixMax(n);
        prefixMax[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
        }

        // Step 2: Build suffixMin array
        // suffixMin[i] = minimum element from index i to n-1
        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        }

        // Step 3: Partition array and compute max for each component
        vector<int> ans(n);
        int start = 0;
        int currMax = nums[0];

        // Iterate through potential separation points
        for (int i = 0; i < n - 1; i++) {
            currMax = max(currMax, nums[i]);

            // Check if we can separate at position i
            // Component [start...i] can be separated if max(left) <= min(right)
            if (prefixMax[i] <= suffixMin[i + 1]) {
                // Assign current max to all elements in this component
                for (int j = start; j <= i; j++) {
                    ans[j] = currMax;
                }

                // Start new component
                start = i + 1;
                currMax = nums[start];
            }
        }

        // Handle last element and remaining component
        currMax = max(currMax, nums[n - 1]);
        for (int j = start; j < n; j++) {
            ans[j] = currMax;
        }

        return ans;
    }
};

/*
Time Complexity: O(n) - Three linear passes through the array
  - Building prefixMax: O(n)
  - Building suffixMin: O(n)
  - Computing result: O(n)
  - Total: O(n)
Space Complexity: O(n) - Storage for prefixMax, suffixMin, and result arrays

Algorithm Explanation:

Key Concept: Component Separation
- An array can be split into two components at position i if max(left part) <= min(right part)
- This ensures no element in left part interferes with right part

Step 1 - Build prefixMax:
- prefixMax[i] = max(nums[0], nums[1], ..., nums[i])
- Allows O(1) query of maximum in any left prefix

Step 2 - Build suffixMin:
- suffixMin[i] = min(nums[i], nums[i+1], ..., nums[n-1])
- Allows O(1) query of minimum in any right suffix

Step 3 - Partition and Assign:
- For each position i from 0 to n-2:
  - If prefixMax[i] <= suffixMin[i+1]: valid separation point
  - Assign currMax to all elements in current component [start...i]
  - Move to next component starting at i+1
- Handle remaining elements in final component

Example:
nums = [3,2,1,5,6,7]

PrefixMax:  [3,3,3,5,6,7]
SuffixMin:  [1,1,1,5,6,7]

Checking separation points:
i=0: prefixMax[0]=3, suffixMin[1]=1 → 3 > 1 ✗
i=1: prefixMax[1]=3, suffixMin[2]=1 → 3 > 1 ✗
i=2: prefixMax[2]=3, suffixMin[3]=5 → 3 <= 5 ✓ (can separate)
  Component [0..2]: [3,2,1], max = 3
  ans[0] = ans[1] = ans[2] = 3
  
i=3: prefixMax[3]=5, suffixMin[4]=6 → 5 <= 6 ✓ (can separate)
  Component [3..3]: [5], max = 5
  ans[3] = 5
  
i=4: prefixMax[4]=6, suffixMin[5]=7 → 6 <= 7 ✓ (can separate)
  Component [4..4]: [6], max = 6
  ans[4] = 6
  
Final component [5..5]: [7], max = 7
  ans[5] = 7

Result: [3,3,3,5,6,7]

Another Example:
nums = [5,1,2,3,4]

PrefixMax:  [5,5,5,5,5]
SuffixMin:  [1,1,2,3,4]

Checking separation points:
i=0: prefixMax[0]=5, suffixMin[1]=1 → 5 > 1 ✗
i=1: prefixMax[1]=5, suffixMin[2]=2 → 5 > 2 ✗
i=2: prefixMax[2]=5, suffixMin[3]=3 → 5 > 3 ✗
i=3: prefixMax[3]=5, suffixMin[4]=4 → 5 > 4 ✗

No separation possible. Entire array is one component:
Component [0..4]: [5,1,2,3,4], max = 5
Result: [5,5,5,5,5]

Key Insights:
- Prefix-suffix preprocessing enables O(n) solution
- Separation is optimal when prefixMax[i] <= suffixMin[i+1]
- Each component gets assigned the maximum value of that component
- No element crosses component boundaries

Edge Cases:
- Single element: returns [nums[0]]
- Already sorted ascending: many separation points possible
- Already sorted descending: likely no separation (one component)
- All equal elements: separates at every point
*/
