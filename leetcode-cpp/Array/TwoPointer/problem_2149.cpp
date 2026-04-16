// LeetCode 2149: Rearrange Array Elements by Sign
// Problem: Rearrange array so positive numbers are at even indices, negatives at odd indices
// Approach: Two Pointers (one for even positions, one for odd positions)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        int pos = 0; // even index for positive numbers
        int neg = 1; // odd index for negative numbers

        for(int i = 0; i < n; i++) {
            if(nums[i] > 0) {
                ans[pos] = nums[i];
                pos += 2;
            } else {
                ans[neg] = nums[i];
                neg += 2;
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n) - single pass through the array
Space Complexity: O(n) - for the result array (excluding output)

Constraints:
- The array is guaranteed to have equal number of positive and negative integers
- No zeros in the array

Example:
Input: nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]

Explanation:
- Positive numbers [3,1,2] go to indices [0,2,4]
- Negative numbers [-2,-5,-4] go to indices [1,3,5]
Result: [3,-2,1,-5,2,-4]

Approach:
1. Use two pointers: pos for even indices, neg for odd indices
2. Iterate through the array once
3. Place positive numbers at even indices (pos), increment by 2
4. Place negative numbers at odd indices (neg), increment by 2
5. Return the rearranged array
*/
