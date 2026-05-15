// LeetCode 153: Find Minimum in Rotated Sorted Array
// Problem: Find the minimum element in a rotated sorted array (no duplicates)
// Approach: Binary search - compare mid with right to determine which half contains minimum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        // Binary search to find minimum in rotated sorted array
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = (right + left) / 2;

            // If mid element is greater than right element,
            // minimum must be in the right half (rotation point is to the right)
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // If mid element is less than or equal to right element,
            // minimum is at mid or in the left half (rotation point is at or to the left)
            else {
                // The minimum is at mid or in the left part
                right = mid;
            }
        }
        
        return nums[left];
    }
};

/*
Time Complexity: O(log n)
  - Binary search narrows search space by half each iteration
  - Guaranteed logarithmic since no duplicates exist

Space Complexity: O(1)
  - Only using constant extra space for pointers

Algorithm Explanation:

Problem Overview:
Given a rotated sorted array with distinct elements, find the minimum element.
Examples: [3,4,5,1,2], [2,1], [1,2,3,4,5]

Key Insight - Rotation Property:
- Original array: [1,2,3,4,5] is sorted
- After rotation by k positions: [4,5,1,2,3]
- The array consists of two sorted subarrays
- The rotation point is where the minimum element is
- Left part (after rotation point moves to end): [4,5]
- Right part (before rotation point): [1,2,3]

Binary Search Strategy:
Compare nums[mid] with nums[right] to identify which half contains the rotation:

1. If nums[mid] > nums[right]:
   - Mid is in the left sorted part
   - Right part contains the rotation point
   - Minimum is to the right: left = mid + 1

2. If nums[mid] <= nums[right]:
   - Mid is in the right sorted part (or could be minimum)
   - Left part might contain rotation, or minimum is at mid
   - Minimum is at mid or to the left: right = mid

Why This Works:
- In any rotation, one half is always sorted
- If nums[mid] > nums[right]: mid is definitely not in the sorted right half, so go right
- If nums[mid] <= nums[right]: right half is sorted from mid to right, minimum is in left half or at mid

Example 1: [3, 4, 5, 1, 2]
Initial: left=0, right=4, array=[3,4,5,1,2]
- mid=2, nums[mid]=5, nums[right]=2
- 5 > 2 → left = 3 (go right)

Iteration 2: left=3, right=4
- mid=3, nums[mid]=1, nums[right]=2
- 1 <= 2 → right = 3 (go left/stay)

Iteration 3: left=3, right=3
- Loop exits
- Return nums[3] = 1 ✓

Example 2: [2, 1]
Initial: left=0, right=1
- mid=0, nums[mid]=2, nums[right]=1
- 2 > 1 → left = 1

Iteration 2: left=1, right=1
- Loop exits
- Return nums[1] = 1 ✓

Example 3: [1, 2, 3, 4, 5] (no rotation)
Initial: left=0, right=4
- mid=2, nums[mid]=3, nums[right]=5
- 3 <= 5 → right = 2

Iteration 2: left=0, right=2
- mid=1, nums[mid]=2, nums[right]=3
- 2 <= 3 → right = 1

Iteration 3: left=0, right=1
- mid=0, nums[mid]=1, nums[right]=2
- 1 <= 2 → right = 0

Iteration 4: left=0, right=0
- Loop exits
- Return nums[0] = 1 ✓

Example 4: [4, 5, 6, 7, 0, 1, 2]
Initial: left=0, right=6
- mid=3, nums[mid]=7, nums[right]=2
- 7 > 2 → left = 4

Iteration 2: left=4, right=6
- mid=5, nums[mid]=1, nums[right]=2
- 1 <= 2 → right = 5

Iteration 3: left=4, right=5
- mid=4, nums[mid]=0, nums[right]=1
- 0 <= 1 → right = 4

Iteration 4: left=4, right=4
- Loop exits
- Return nums[4] = 0 ✓

Edge Cases:
1. Single element: [1] → returns 1
2. Two elements: [2,1] or [1,2] → returns minimum
3. No rotation (sorted): [1,2,3,4,5] → returns 1
4. Rotation at end: [2,3,4,5,1] → returns 1
5. Rotation at start: [5,1,2,3,4] → returns 1

Why No Duplicates Matter:
- With duplicates: [1,3,1] and comparing mid with right becomes ambiguous
- When nums[mid] == nums[right], cannot determine which half has minimum
- Would need additional logic (e.g., shrink right) → degrades to O(n)
- Without duplicates: comparison is always definitive → guaranteed O(log n)

Comparison Strategy Variants:
1. Compare with right (used here): Works well when minimum expected on right side
2. Compare with left: Works well when minimum expected on left side
3. Compare left and right with mid: More complex but clearer logic

This solution uses compare-with-right, which is standard for this problem.
*/
