// LeetCode 1752: Check if Array is Sorted and Rotated
// Problem: Determine if an array is a rotated version of a sorted array
// A rotated sorted array has at most one position where nums[i] > nums[i+1]
// Approach: Count decreasing positions - should be at most 1 for rotated sorted array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        int count = 0;
        int n = nums.size();

        // Count how many positions have nums[i] > nums[i+1]
        // Use modulo to handle circular array wraparound
        for (int i = 0; i < n; i++) {
            // Check if current element > next element (wraps around with modulo)
            if (nums[i] > nums[(i + 1) % n]) {
                count++;
            }

            // If more than 1 break point found, array cannot be rotated sorted
            if (count > 1) {
                return false;
            }
        }

        return true;
    }
};

/*
Time Complexity: O(n) where n is the length of the array
  - Single pass through all elements
  - Each comparison and increment is O(1)
  - Early exit when count > 1

Space Complexity: O(1)
  - Only using constant extra space (count variable, loop index)
  - No additional data structures needed

Algorithm Explanation:

Problem Overview:
Given an array, determine if it's either:
1. A sorted array (non-decreasing): [1, 2, 3, 4, 5]
2. A rotated sorted array: [3, 4, 5, 1, 2] or [4, 5, 1, 2, 3]

Key Insight - Counting Break Points:
- In a strictly sorted array: no element is greater than the next
- In a rotated sorted array: exactly ONE position where nums[i] > nums[i+1]
  * This position is the rotation point (where the larger part meets smaller part)
- Example: [3, 4, 5, 1, 2] has break at index 2 (5 > 1)
- If more than 1 break point: array cannot be a valid rotation

Why Modulo Arithmetic:
- We use (i + 1) % n to handle the circular nature
- At the last element (i = n-1), (i+1) % n = 0 (wraps to first element)
- This checks if nums[n-1] > nums[0], which is important for detecting rotation
- Example: [3,4,5,1,2] → at i=4: nums[4]=2, nums[0]=3 → 2 > 3? No ✓

Example 1: nums = [3, 4, 5, 1, 2]
Count break points:
- i=0: nums[0]=3, nums[1]=4 → 3 > 4? No
- i=1: nums[1]=4, nums[2]=5 → 4 > 5? No
- i=2: nums[2]=5, nums[3]=1 → 5 > 1? Yes, count=1
- i=3: nums[3]=1, nums[4]=2 → 1 > 2? No
- i=4: nums[4]=2, nums[0]=3 → 2 > 3? No
count = 1 → return true ✓

Example 2: nums = [2, 1, 3, 4]
Count break points:
- i=0: nums[0]=2, nums[1]=1 → 2 > 1? Yes, count=1
- i=1: nums[1]=1, nums[2]=3 → 1 > 3? No
- i=2: nums[2]=3, nums[3]=4 → 3 > 4? No
- i=3: nums[3]=4, nums[0]=2 → 4 > 2? Yes, count=2
count = 2 > 1 → return false ✓ (not rotated sorted)

Example 3: nums = [1, 2, 3, 4, 5]
Count break points:
- i=0: 1 > 2? No
- i=1: 2 > 3? No
- i=2: 3 > 4? No
- i=3: 4 > 5? No
- i=4: 5 > 1? Yes, count=1
count = 1 → return true ✓ (sorted array, rotation by 0)

Example 4: nums = [1, 3, 2]
Count break points:
- i=0: 1 > 3? No
- i=1: 3 > 2? Yes, count=1
- i=2: 2 > 1? Yes, count=2
count = 2 > 1 → return false ✓

Example 5: nums = [5, 7, 1, 2, 3]
Count break points:
- i=0: 5 > 7? No
- i=1: 7 > 1? Yes, count=1
- i=2: 1 > 2? No
- i=3: 2 > 3? No
- i=4: 3 > 5? No
count = 1 → return true ✓

Edge Cases:
1. Single element [x]: always return true (technically sorted and rotated)
2. Two elements [1, 2]: return true (sorted)
3. Two elements [2, 1]: count=1 at i=0, then 1>2? No, total=1, return true ✓
4. All equal [5, 5, 5, 5]: all 5>5? No, count=0, return true ✓
5. Empty array []: n=0, loop doesn't run, return true

Special Case - Why count=1 is Valid:
When an array is rotated, one rotation point exists where the largest element
is followed by the smallest element. This creates exactly one break point.
A non-rotated sorted array has no breaks, but we allow count=1 for rotations.
Actually, wait - let me reconsider:

For a sorted array [1,2,3,4,5]:
- When i=4: nums[4]=5 > nums[0]=1? Yes, this gives count=1
- So a purely sorted array also has count=1 due to the wraparound!
- This is why we allow count ≤ 1

For a twice-rotated or improperly rotated array:
- It will have multiple break points (count > 1)

Algorithm Correctness Proof:
Claim: Array is rotated sorted iff it has at most 1 break point (including wraparound)

Proof:
1. Original sorted array: no breaks within itself, but wraparound creates 1 break
2. Rotated once: creates 1 break at rotation point, wraparound may create another
   - If rotated properly, wraparound won't create a second break
   - If rotated improperly, wraparound creates additional break
3. Rotated multiple times: creates multiple breaks
4. Any non-sorted arrangement has multiple breaks

Comparison with Other Approaches:

1. Current Approach (Count Breaks):
   - Time: O(n)
   - Space: O(1)
   - Simple and elegant
   - Handles edge cases naturally

2. Binary Search Approach:
   - Time: O(log n)
   - Space: O(1)
   - More complex logic
   - Works but unnecessary for this problem

3. Find Rotation Index Approach:
   - Time: O(n)
   - Space: O(1)
   - Finds where rotation occurred
   - Overkill if we only need to verify

Why Count Breaks is Best:
- Linear scan once through array
- Clear logic: sorted has ≤1 break when considering wraparound
- No edge case surprises
- Easy to understand and verify

Important Note on Duplicates:
- Original problem has no duplicates specified
- Algorithm assumes distinct elements for correctness
- With duplicates, might need additional validation
- Example: [1,3,3] has 1 break at position 1 (3>3? No), but wraparound is 3>1? Yes
- So count=1, return true - still works!

Optimization Notes:
- Early return when count > 1 saves iterations
- No extra array allocations
- Minimal variable declarations
- Cache-friendly linear scan

Problem Variant:
- Check if rotated with duplicates: same approach works
- Find rotation amount: track break position
- Find both sorted parts: track positions of breaks and values
- Reverse rotated array: use rotation point information
*/
