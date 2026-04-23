// LeetCode 15: 3Sum
// Problem: Find all unique triplets in array that sum to zero
// Approach: Sorting + Two Pointer (reduce to 2Sum problem)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        
        // Sort the array first
        sort(nums.begin(), nums.end());

        // Fix one element and use two-pointer for remaining two
        for (int i = 0; i < n; i++) {
            // Skip duplicate elements for first position
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            // If current element is positive, no solution (array sorted)
            if (nums[i] > 0) break;

            // Two pointer approach for remaining two elements
            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum < 0) {
                    j++;  // Need larger sum
                }
                else if (sum > 0) {
                    k--;  // Need smaller sum
                }
                else {
                    // Found a valid triplet
                    ans.push_back({nums[i], nums[j], nums[k]});
                    j++;
                    k--;

                    // Skip duplicate elements for second position
                    while (j < k && nums[j] == nums[j - 1]) j++;
                    // Skip duplicate elements for third position
                    while (j < k && nums[k] == nums[k + 1]) k--;
                }
            }
        }
        return ans;
    }
};

/*
Time Complexity: O(n^2)
- Sorting: O(n log n)
- Outer loop: O(n)
- Inner two-pointer loop: O(n)
- Total: O(n log n) + O(n^2) = O(n^2)

Space Complexity: O(1) or O(n)
- O(1) if not counting output
- O(n) if counting space for sorting (depending on sort implementation)

Algorithm (Sorting + Two Pointer):
1. Sort the array in ascending order
2. For each element i (as first element of triplet):
   - Skip if it's a duplicate
   - Skip if positive (no solution possible)
   - Use two-pointer approach on remaining array:
     * j starts at i+1, k starts at n-1
     * Calculate sum = nums[i] + nums[j] + nums[k]
     * If sum < 0: move j++ (need larger)
     * If sum > 0: move k-- (need smaller)
     * If sum == 0: found triplet, add to result, skip duplicates

Key Insights:
- Sorting enables two-pointer approach
- Skip duplicates to ensure unique triplets
- Early break for positive values (no solution if first element positive)
- Two-pointer exploits sorted property

Why Skip Duplicates:
- We want unique triplets (no duplicate triplets in result)
- After finding one triplet, skip same values at same positions
- Ensures each unique combination appears only once

Example 1:
Input: nums = [-1, 0, 1, 2, -1, -4]

After sorting: [-4, -1, -1, 0, 1, 2]

i=0 (nums[0]=-4):
- j=1, k=5: sum = -4 + (-1) + 2 = -3 < 0 → j++
- j=2, k=5: sum = -4 + (-1) + 2 = -3 < 0 → j++
- j=3, k=5: sum = -4 + 0 + 2 = -2 < 0 → j++
- j=4, k=5: sum = -4 + 1 + 2 = -1 < 0 → j++
- j=5, k=5: j > k, exit

i=1 (nums[1]=-1):
- j=2, k=5: sum = -1 + (-1) + 2 = 0 → found! Add [-1, -1, 2]
  - j++, k--, skip duplicates
  - j=3, k=4: sum = -1 + 0 + 1 = 0 → found! Add [-1, 0, 1]
  - j++, k--, j > k exit

i=2 (nums[2]=-1): skip (duplicate of i=1)

i=3 (nums[3]=0): > -i=3 (nums[3]=0):
- j=4, k=5: sum = 0 + 1 + 2 = 3 > 0 → k--
- j=4, k=4: j > k exit

i=4 (nums[4]=1): > 0, break

Output: [[-1, -1, 2], [-1, 0, 1]]

Example 2:
Input: nums = [0, 0, 0, 0]

After sorting: [0, 0, 0, 0]

i=0 (nums[0]=0):
- j=1, k=3: sum = 0 + 0 + 0 = 0 → found! Add [0, 0, 0]
  - j++, k--, j=2, k=2: j > k exit

i=1 (nums[1]=0): skip (duplicate)
i=2 (nums[2]=0): skip (duplicate)
i=3 (nums[3]=0): j=4, k impossible

Output: [[0, 0, 0]]

Edge Cases:
- All zeros: one triplet [0, 0, 0]
- Fewer than 3 elements: no triplet possible
- All negative: at most one triplet
- All positive: no triplet (sum > 0)
- Empty array: no triplet

Why Two-Pointer Works After Sorting:
- Array is sorted: can efficiently move pointers
- Moving j right increases sum (next element is larger)
- Moving k left decreases sum (previous element is smaller)
- Guarantees we find all solutions in this range

Important Optimization:
- Early break when nums[i] > 0
- Since array is sorted and we need sum = 0
- If first element is positive, no solution possible
- Saves unnecessary iterations

Duplicate Handling:
- Skip duplicate first elements: ensures unique outer loop values
- Skip duplicate middle/last: avoids duplicate triplets
- Pattern: if we just found solution with (i, j, k)
  - Skip nums[j] == nums[j-1] and nums[k] == nums[k+1]
  - Moves to next different values

*/