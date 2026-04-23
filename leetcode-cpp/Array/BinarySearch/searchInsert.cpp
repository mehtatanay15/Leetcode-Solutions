// LeetCode 35: Search Insert Position
// Problem: Find index of target in sorted array, or position where it would be inserted
// Approach: Binary Search

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while(l <= r) {
            int mid = (l + r) / 2;

            if(nums[mid] == target) {
                return mid;  // Found target
            }
            else if(nums[mid] < target) {
                l = mid + 1;  // Target is in right half
            }
            else {
                r = mid - 1;  // Target is in left half
            }
        }

        // Return insertion position (l points to correct position)
        return l;
    }
};

/*
Time Complexity: O(log n)
- Each iteration eliminates half of remaining elements
- Maximum iterations: log₂(n)

Space Complexity: O(1)
- Only using pointers (l, r, mid)

Algorithm (Binary Search):
1. Initialize: l = 0, r = n-1
2. While l <= r:
   a. Find middle: mid = (l + r) / 2
   b. If nums[mid] == target: return mid
   c. If nums[mid] < target: search right (l = mid + 1)
   d. If nums[mid] > target: search left (r = mid - 1)
3. If target not found, return l (insertion position)

Key Insight:
- When loop ends, l > r
- l is exactly where target should be inserted
- All elements before l are < target
- All elements at l and after are >= target

Why l is the answer:
- If target found: return its index immediately
- If not found: when l > r:
  * r is last element < target
  * l is first position >= target
  * So l is correct insertion position

Example 1:
Input: nums = [1,3,5,6], target = 5

l=0, r=3, mid=1: nums[1]=3 < 5 → l=2
l=2, r=3, mid=2: nums[2]=5 == 5 → return 2

Output: 2 (5 is at index 2)

Example 2:
Input: nums = [1,3,5,6], target = 5

l=0, r=3, mid=1: nums[1]=3 < 7 → l=2
l=2, r=3, mid=2: nums[2]=5 < 7 → l=3
l=3, r=3, mid=3: nums[3]=6 < 7 → l=4
l=4, r=3: loop ends, return l=4

Output: 4 (insert at position 4, after all elements)

Example 3:
Input: nums = [1,3,5,6], target = 2

l=0, r=3, mid=1: nums[1]=3 > 2 → r=0
l=0, r=0, mid=0: nums[0]=1 < 2 → l=1
l=1, r=0: loop ends, return l=1

Output: 1 (insert at position 1, between 1 and 3)

Edge Cases:
- Empty array: l=0, return 0
- Target smaller than all: return 0
- Target larger than all: return n
- Target equals first element: return 0
- Target equals last element: return n-1

Boundary Conditions:
- Loop condition: l <= r (inclusive)
- When l > r: l is insertion position
- l always moves right (l = mid + 1)
- r always moves left (r = mid - 1)
*/