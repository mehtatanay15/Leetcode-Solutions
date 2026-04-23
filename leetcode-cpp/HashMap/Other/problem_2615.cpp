// LeetCode 2615: Sum of Distances
// Problem: Calculate sum of distances for each element to all other elements with same value
// Approach: HashMap Grouping + Prefix Sum Mathematics

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<long long>> mpp;

        // Step 1: Group indices by their values
        for(int i = 0; i < nums.size(); i++) {
            mpp[nums[i]].push_back(i);
        }
        
        vector<long long> ans(nums.size(), 0);
        
        // Step 2: For each value group, calculate distances
        for(auto& [val, indices] : mpp) {
            // Calculate total sum of all indices in this group
            long long summ = 0;
            for(long long idx : indices) summ += idx;

            long long leftsum = 0;
            int k = indices.size();

            // Step 3: For each index, calculate left and right distances
            for(int i = 0; i < k; i++) {
                long long target_idx = indices[i];

                // Distance to all elements on the left
                // Formula: target_idx * i - leftsum
                // (i elements to the left, each contributes (target_idx - their_position))
                long long left_part = (target_idx * i) - leftsum;
                
                // Distance to all elements on the right
                // Number of elements to the right
                long long right_elements_count = k - 1 - i;
                // Sum of all indices to the right
                long long right_sum = (summ - leftsum - target_idx);
                // Formula: (their_position - target_idx) for each right element
                long long right_part = right_sum - (target_idx * right_elements_count);
                
                // Total distance for current element
                ans[target_idx] = left_part + right_part;

                // Update leftsum for next iteration
                leftsum += target_idx;
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n)
- Single pass to group indices: O(n)
- For each unique value, process all occurrences: O(n) total
- Overall: O(n)

Space Complexity: O(n)
- HashMap to store indices by value
- Output array

Algorithm:
1. Group all indices by their values using HashMap
2. For each value group:
   - Calculate total sum of indices: summ
   - For each index position i in sorted group:
     * Left part: sum of distances to all left elements
       - Each of i left elements contributes (target_idx - left_idx)
       - Formula: i * target_idx - leftsum
     * Right part: sum of distances to all right elements
       - Each of (k-1-i) right elements contributes (right_idx - target_idx)
       - Formula: (summ - leftsum - target_idx) - (k-1-i) * target_idx
     * Update leftsum for next iteration

Key Insights:
- Only elements with same value contribute to distance
- Grouped indices are naturally sorted
- Use mathematical formula instead of nested loops for efficiency
- leftsum keeps running total of processed indices

Example:
Input: nums = [1,3,1,1,2]
Index:       [0,1,2,3,4]

Group by value:
- 1: indices [0, 2, 3]
- 2: indices [4]
- 3: indices [1]

For value 1 with indices [0, 2, 3]:
summ = 0 + 2 + 3 = 5

i=0, idx=0:
- left_part = 0*0 - 0 = 0
- right_elements = 2, right_sum = 5 - 0 = 5
- right_part = 5 - 0*2 = 5
- ans[0] = 5

i=1, idx=2:
- left_part = 2*1 - 0 = 2
- right_elements = 1, right_sum = 5 - 0 - 2 = 3
- right_part = 3 - 2*1 = 1
- ans[2] = 3

i=2, idx=3:
- left_part = 3*2 - 2 = 4
- right_elements = 0, right_sum = 5 - 2 - 3 = 0
- right_part = 0 - 0 = 0
- ans[3] = 4

Output: [5, 0, 3, 4, 0]
*/
