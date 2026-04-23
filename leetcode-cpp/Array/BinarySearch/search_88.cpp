// LeetCode 81: Search in Rotated Sorted Array II (with duplicates)
// Problem: Search in rotated sorted array that may contain duplicates
// Approach: Binary Search with duplicate handling

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (nums[mid] == target) return true;

            // Handle duplicates - shrink boundaries when all three are equal
            if (nums[l] == nums[mid] && nums[mid] == nums[r]) {
                l++;
                r--;
            }
            // Left half is sorted
            else if (nums[l] <= nums[mid]) {
                // Target is in the sorted left half
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            // Right half is sorted
            else {
                // Target is in the sorted right half
                if (nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }

        return false;
    }
};

/*
Time Complexity: O(n) worst case
- Average: O(log n) for binary search
- Worst case: O(n) when many duplicates (e.g., [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1])

Space Complexity: O(1)
- Only using pointers (l, r, mid)

Algorithm (Binary Search with Duplicate Handling):
1. While l <= r:
   a. Calculate mid = (l + r) / 2
   b. If nums[mid] == target: return true
   c. Handle duplicates:
      - If nums[l] == nums[mid] == nums[r]: shrink by l++ and r--
      - Can't determine which half is sorted, so skip duplicates
   d. Determine which half is sorted:
      - If left half is sorted: check if target is in that range
      - If right half is sorted: check if target is in that range
   e. Update l or r based on target location
2. Return false if not found

Key Differences from Problem 33 (without duplicates):
- Problem 33: one half is always sorted
- Problem 81: duplicates break the sortedness guarantee
- Need extra handling when nums[l] == nums[mid] == nums[r]

Why Duplicate Handling Matters:
Example: [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]
- nums[0]=1, nums[mid]=1, nums[18]=1 all equal
- Can't determine which half is sorted
- Must shrink boundaries: l++, r--

Example 1:
Input: nums = [1,3], target = 3

l=0, r=1, mid=0: nums[0]=1 < 3
- Left half sorted: nums[0]=1 <= nums[0]=1
- Target 3 not in [1, 1), so l = mid + 1 = 1
l=1, r=1, mid=1: nums[1]=3 == 3
- Return true

Output: true

Example 2:
Input: nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1], target = 2

Many iterations of shrinking boundaries due to duplicates,
eventually finds the 2.

Output: true

Example 3:
Input: nums = [1,3], target = 3

Same as Example 1, returns true.

Edge Cases:
- All elements same: O(n) to determine not present
- Single element: checked immediately
- Target at boundaries: correctly identified
- All duplicates: must shrink to find answer

Complexity Analysis:
- When no duplicates: O(log n) as in problem 33
- When duplicates at boundaries: O(n) worst case
- This is unavoidable due to ambiguity with duplicates

Sorted Half Detection:
- nums[l] <= nums[mid]: left half is sorted
- Otherwise: right half is sorted
- Use this to determine where target could be
*/