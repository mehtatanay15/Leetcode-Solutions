// LeetCode 33: Search in Rotated Sorted Array
// Problem: Find a target value in a rotated sorted array
// Approach: Two-phase Binary Search (find pivot, then search)

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0;
        int r = n - 1;

        // Phase 1: Find pivot (smallest element position)
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] > nums[r]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }

        int pivot = l;

        // Phase 2: Decide which half to search
        if (target >= nums[pivot] && target <= nums[n - 1]) {
            l = pivot;
            r = n - 1;
        } else {
            l = 0;
            r = pivot - 1;
        }

        // Phase 3: Normal binary search on selected half
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return -1;
    }
};

/*
Time Complexity: O(log n)
- First binary search to find pivot: O(log n)
- Second binary search on half array: O(log n)
- Total: O(log n)

Space Complexity: O(1)
- Only using pointers (l, r, mid, pivot)

Algorithm (Two-Phase Binary Search):
1. Phase 1: Find pivot (rotation point)
   - Compare mid with right boundary
   - If nums[mid] > nums[r], smallest is in right half
   - Otherwise smallest is in left half or at mid
2. Phase 2: Determine search range
   - If target is in range [pivot, n-1], search right half
   - Otherwise search left half [0, pivot-1]
3. Phase 3: Standard binary search on the determined half

Key Insight:
- Even though array is rotated, one half is always sorted
- Use this property to eliminate half the search space each iteration
- Key observation: nums[pivot] is the minimum element

Example:
Input: nums = [4,5,6,7,0,1,2], target = 0

Phase 1 - Find pivot:
- l=0, r=6, mid=3: nums[3]=7 > nums[6]=2 → l=4
- l=4, r=6, mid=5: nums[5]=1 < nums[6]=2 → r=5
- l=4, r=5, mid=4: nums[4]=0 < nums[5]=1 → r=4
- l=4, r=4: pivot = 4 (nums[4]=0 is minimum)

Phase 2 - Decide range:
- target=0 is in range [0, 2]? No
- So target=0 is in range [4, 6]? Yes (0,1,2)
- Set l=4, r=6

Phase 3 - Binary search:
- l=4, r=6, mid=5: nums[5]=1 > target=0 → r=4
- l=4, r=4, mid=4: nums[4]=0 == target → return 4

Output: 4

Edge Cases:
- Array not rotated (nums[0] < nums[n-1]): pivot = 0
- Single element: pivot = 0
- All same values would fail (but problem guarantees unique values)
- Target at pivot position

*/