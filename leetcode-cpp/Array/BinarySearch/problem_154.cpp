// LeetCode 154: Find Minimum in Rotated Sorted Array II
// Problem: Find the minimum element in a rotated sorted array with duplicates
// Approach: Binary search with duplicate handling - shrink right when equal to mid

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = (left + right) / 2;

            // If mid is greater than right, minimum is in right half
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            }
            // If mid is less than right, minimum is at mid or in left half
            else if (nums[mid] < nums[right]) {
                right = mid;
            }
            // If mid equals right, we have duplicates - cannot determine direction
            // Safely shrink right pointer to eliminate duplicate
            else if (nums[mid] == nums[right]) {
                right--;
            }
        }

        return nums[left];
    }
};

/*
Time Complexity: O(log n) average case, O(n) worst case
  - Average case: With typical duplicates, binary search narrows space logarithmically
  - Worst case: When array is like [1,1,1,0,1,1,1], shrinking right degrades to O(n)

Space Complexity: O(1)
  - Only using constant extra space for pointers

Algorithm Explanation:

Problem Overview:
Given a rotated sorted array with duplicate elements, find the minimum element.
Examples: [3,4,5,1,2], [2,1], [1,3,1,1,1], [1,1,1,0,1,1,1]

Key Difference from Problem 153:
- Problem 153: Distinct elements → guaranteed O(log n)
- Problem 154: With duplicates → worst case O(n)

Why Duplicates Make It Harder:
When nums[mid] == nums[right], we cannot determine which half contains the minimum:
- [1, 3, 1]: mid=3, right=1, equal? No, 3 > 1
- [1, 1, 1]: mid=1, right=1, equal? Yes, but where is minimum?
  * Could be in left half: [1, 1, minimum]
  * Or could be at current position

Binary Search Strategy:

1. If nums[mid] > nums[right]:
   - Mid is definitely not the minimum
   - Right half contains the rotation point
   - Minimum is to the right: left = mid + 1

2. If nums[mid] < nums[right]:
   - Right half is sorted from mid onwards
   - Minimum is at mid or in left half
   - Move right: right = mid

3. If nums[mid] == nums[right]:
   - Ambiguous situation with duplicates
   - Cannot safely determine direction
   - Strategy: Shrink right pointer: right--
   - This eliminates duplicates but loses binary search guarantee
   - In worst case, becomes linear search

Why right-- is Safe:
- When nums[mid] == nums[right], we know nums[right] is either:
  * The minimum (but so might be other copies to the left)
  * Not the minimum (minimum is somewhere else)
- Decrementing right removes the duplicate at right boundary
- We don't lose any potential minimum values (they exist elsewhere if needed)
- If nums[right] is the only copy of minimum, we'll find it via mid eventually

Example 1: [1, 3, 1, 1, 1]
Initial: left=0, right=4
- mid=2, nums[mid]=1, nums[right]=1
- 1 == 1 → right = 3

Iteration 2: left=0, right=3
- mid=1, nums[mid]=3, nums[right]=1
- 3 > 1 → left = 2

Iteration 3: left=2, right=3
- mid=2, nums[mid]=1, nums[right]=1
- 1 == 1 → right = 2

Iteration 4: left=2, right=2
- Loop exits
- Return nums[2] = 1 ✓

Example 2: [3, 1, 1]
Initial: left=0, right=2
- mid=1, nums[mid]=1, nums[right]=1
- 1 == 1 → right = 1

Iteration 2: left=0, right=1
- mid=0, nums[mid]=3, nums[right]=1
- 3 > 1 → left = 1

Iteration 3: left=1, right=1
- Loop exits
- Return nums[1] = 1 ✓

Example 3: [1, 1, 1, 0, 1, 1, 1] (worst case)
Initial: left=0, right=6
- mid=3, nums[mid]=0, nums[right]=1
- 0 < 1 → right = 3

Iteration 2: left=0, right=3
- mid=1, nums[mid]=1, nums[right]=0
- 1 > 0 → left = 2

Iteration 3: left=2, right=3
- mid=2, nums[mid]=1, nums[right]=0
- 1 > 0 → left = 3

Iteration 4: left=3, right=3
- Loop exits
- Return nums[3] = 0 ✓

Example 4: [1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1] (worst case)
Initial: left=0, right=14
- mid=7, nums[mid]=1, nums[right]=1
- 1 == 1 → right = 13

... (continues with right--)
This case triggers O(n) behavior as we keep decrementing right

Edge Cases:
1. Single element: [1] → returns 1
2. Two elements: [2,1] or [1,2] or [1,1]
3. All same: [1,1,1,1,1] → returns 1
4. Duplicates at rotation point: [3,1,1] or [1,1,3]
5. Mixed duplicates: [1,3,1,1,1]

Worst Case Analysis:
- Scenario: [1, 1, 1, ..., 1, 0, 1, 1, ..., 1]
  * Nearly all 1's with single 0 near end
  * Each comparison of mid and right might be 1 == 1
  * Forces right-- on every iteration
  * Results in O(n) time complexity

Best Case:
- No duplicates (acts like problem 153): O(log n)
- Duplicates far from rotation point: O(log n)

Average Case:
- Most practical inputs: O(log n)
- Duplicates manageable by right--

Why Not Shrink Left Instead?
- Could do left++ when nums[left] == nums[mid] == nums[right]
- But shrinking right is more standard
- Both approaches have same worst-case complexity

Alternative Approach (More Complex):
- Find first distinct element from left/right
- Use that for comparison instead of immediate right
- More code but potentially better performance on some inputs
- Not commonly used in competitive programming

Comparison with Problem 153:
| Aspect | Problem 153 | Problem 154 |
|--------|------------|------------|
| Duplicates | No | Yes |
| Time Best | O(log n) | O(log n) |
| Time Average | O(log n) | O(log n) |
| Time Worst | O(log n) | O(n) |
| Space | O(1) | O(1) |
| Complexity | Easier | Trickier |

Key Takeaway:
Duplicates in rotated arrays make binary search less effective because
the equality condition (nums[mid] == nums[right]) becomes ambiguous about
the location of the rotation point. The right-- strategy handles this by
eliminating duplicates until a clear direction emerges.
*/
