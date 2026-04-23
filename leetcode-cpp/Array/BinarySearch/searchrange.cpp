// LeetCode 34: Find First and Last Position of Element in Sorted Array
// Problem: Find first and last positions of target in sorted array
// Approach: Two Binary Searches (one for first, one for last position)

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1, last = -1;
        int l = 0, r = nums.size() - 1;

        // Binary search for first occurrence
        while(l <= r) {
            int mid = (l + r) / 2;

            if(nums[mid] == target) {
                first = mid;
                r = mid - 1;  // Continue searching in left half
            }
            else if(nums[mid] < target) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        l = 0; r = nums.size() - 1;

        // Binary search for last occurrence
        while(l <= r) {
            int mid = (l + r) / 2;

            if(nums[mid] == target) {
                last = mid;
                l = mid + 1;  // Continue searching in right half
            }
            else if(nums[mid] < target) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        return {first, last};
    }
};

/*
Time Complexity: O(log n)
- Two binary searches: 2 * O(log n) = O(log n)

Space Complexity: O(1)
- Only using pointers (l, r, mid, first, last)

Algorithm (Two Binary Searches):
1. First pass - find leftmost (first) occurrence:
   - Standard binary search but when found, move left (r = mid - 1)
   - Keep searching left to find earliest occurrence
   - Record position in 'first' variable
2. Second pass - find rightmost (last) occurrence:
   - Standard binary search but when found, move right (l = mid + 1)
   - Keep searching right to find latest occurrence
   - Record position in 'last' variable
3. Return {first, last}

Key Insight:
- When target is found, don't return immediately
- Continue searching in the appropriate direction
- First search: go left to find leftmost
- Last search: go right to find rightmost
- If target not found, both remain -1

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8

First Pass (find leftmost 8):
l=0, r=5, mid=2: nums[2]=7 < 8 → l=3
l=3, r=5, mid=4: nums[4]=8 == 8 → first=4, r=3
l=3, r=3, mid=3: nums[3]=8 == 8 → first=3, r=2
l=3, r=2: end, first=3

Second Pass (find rightmost 8):
l=0, r=5, mid=2: nums[2]=7 < 8 → l=3
l=3, r=5, mid=4: nums[4]=8 == 8 → last=4, l=5
l=5, r=5, mid=5: nums[5]=10 > 8 → r=4
l=5, r=4: end, last=4

Output: [3, 4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6

First Pass:
l=0, r=5, mid=2: nums[2]=7 > 6 → r=1
l=0, r=1, mid=0: nums[0]=5 < 6 → l=1
l=1, r=1, mid=1: nums[1]=7 > 6 → r=0
l=1, r=0: end, first=-1

Second Pass:
l=0, r=5, mid=2: nums[2]=7 > 6 → r=1
l=0, r=1, mid=0: nums[0]=5 < 6 → l=1
l=1, r=1, mid=1: nums[1]=7 > 6 → r=0
l=1, r=0: end, last=-1

Output: [-1, -1]

Edge Cases:
- Target not in array: [-1, -1]
- Single element equal to target: [0, 0]
- Entire array is target: [0, n-1]
- Target at boundaries: correctly identifies first and last

Why Two Searches:
- First search finds leftmost position by always moving left when found
- Second search finds rightmost position by always moving right when found
- Combines efficiency of binary search with finding range
- Total time: O(log n) instead of O(n) for linear scan

Comparison:
- Linear scan: O(n) time - scan left to right to find first and last
- Two binary searches: O(log n) time - efficient for large sorted arrays
- This approach is optimal for sorted arrays
*/