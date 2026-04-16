// LeetCode 3488: Minimum Circular Distance Between Elements With Same Value
// Problem: Find minimum circular distance between query indices and other indices with same values
// Approach: HashMap + Binary Search + Circular Distance

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = queries.size();
        vector<int> ans(n, -1);
        int m = nums.size();

        unordered_map<int, vector<int>> mpp;

        // Step 1: store indices for each value
        for(int i = 0; i < m; i++) {
            mpp[nums[i]].push_back(i);
        }

        // Step 2: process each query
        for(int j = 0; j < n; j++) {
            int idx = queries[j];
            int target = nums[idx];

            vector<int>& temp = mpp[target]; // reference (important)

            int cap = temp.size();

            // if only one occurrence → no answer
            if(cap == 1) {
                ans[j] = -1;
                continue;
            }

            // Step 3: binary search to find position of idx in temp array
            auto it = lower_bound(temp.begin(), temp.end(), idx);
            int pos = it - temp.begin();

            // Step 4: get neighbors in circular manner
            int left = (pos - 1 + cap) % cap;
            int right = (pos + 1) % cap;

            // Step 5: compute distances
            int d1 = abs(temp[left] - idx);
            int d2 = abs(temp[right] - idx);

            // Handle circular distances
            d1 = min(d1, m - d1);
            d2 = min(d2, m - d2);

            ans[j] = min(d1, d2);
        }

        return ans;
    }
};

/*
Time Complexity: O(m log m + n log m)
- m: building the map and sorting = O(m)
- n: for each query, binary search = O(n log m)

Space Complexity: O(m) for the hash map

Example:
Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
Output: [2,-1,3]

Explanation:
Query 0: nums[0] = 1. Other indices with 1: [2, 4]
  - Distance to 2: min(2, 7-2) = 2
  - Distance to 4: min(4, 7-4) = 3
  - Answer: 2

Query 1: nums[3] = 4. No other index with 4
  - Answer: -1

Query 2: nums[5] = 3. Other indices with 3: [1]
  - Circular distance: min(|5-1|, 7-|5-1|) = min(4, 3) = 3
  - Answer: 3
*/
