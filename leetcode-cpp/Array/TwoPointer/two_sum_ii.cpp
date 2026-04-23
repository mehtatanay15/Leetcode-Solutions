// LeetCode 167: Two Sum II - Input Array Is Sorted
// Problem: Find two numbers that add up to a target in a sorted array
// Approach: Two Pointer (One from start, one from end)

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        int l = 0;
        int r = n - 1;

        // Two pointer approach: start from both ends
        while(l < r) {   
            int sum = numbers[l] + numbers[r];
            if(sum == target) {
                return {l + 1, r + 1};  // Return 1-indexed positions
            }
            else if(sum < target) {
                l++;  // Need larger sum, move left pointer right
            }
            else {
                r--;  // Need smaller sum, move right pointer left
            }
        }
        return {};
    }
};

/*
Time Complexity: O(n)
- Single pass through array with two pointers
- Each element visited at most once

Space Complexity: O(1)
- Only using two pointers (l, r)
- Output array doesn't count as extra space

Algorithm (Two Pointer):
1. Initialize: l at start (index 0), r at end (index n-1)
2. While l < r:
   - Calculate sum = numbers[l] + numbers[r]
   - If sum == target: return indices (1-indexed)
   - If sum < target: increment l (need larger values)
   - If sum > target: decrement r (need smaller values)

Key Insight:
- Array is sorted, so two-pointer approach works perfectly
- If sum is too small, we need larger numbers (move left pointer)
- If sum is too large, we need smaller numbers (move right pointer)
- This guarantees we find the answer in one pass

Why Two Pointer Works:
- Since array is sorted: numbers[l] < numbers[l+1] < ... < numbers[r]
- When sum < target: numbers[l] is definitely not part of solution
  * Must pair with something larger than numbers[r]
  * So move l++
- When sum > target: numbers[r] is definitely not part of solution
  * Must pair with something smaller than numbers[l]
  * So move r--

Example:
Input: numbers = [2,7,11,15], target = 9

Initial: l=0, r=3
- sum = 2 + 15 = 17 > 9 → r--
- sum = 2 + 11 = 13 > 9 → r--
- sum = 2 + 7 = 9 == 9 → return [1, 2]

Output: [1, 2] (1-indexed positions of 2 and 7)

Another Example:
Input: numbers = [2,3,4], target = 6

Initial: l=0, r=2
- sum = 2 + 4 = 6 == 6 → return [1, 3]

Output: [1, 3]

Edge Cases:
- Smallest two numbers: l=0, r=1
- Largest two numbers: l=n-2, r=n-1
- Exactly two elements: loop runs once
- Duplicate numbers: handles correctly since we need indices

Note:
- Array is 0-indexed but solution returns 1-indexed
- Return statement uses l+1 and r+1
- Exactly one valid answer guaranteed
*/