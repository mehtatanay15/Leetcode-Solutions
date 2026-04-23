// LeetCode 540: Single Element in a Sorted Array
// Problem: Find single non-duplicate element in sorted array where every other element appears twice
// Approach: Binary Search with paired index checking

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while(l < r) {
            int mid = (l + r) / 2;

            // Make mid even (so mid and mid+1 form a pair)
            if(mid % 2 == 1) mid--;

            // Check if mid and mid+1 are a pair
            if(nums[mid] == nums[mid + 1]) {
                // Pair is in left half before single element
                // Single element is in right half
                l = mid + 2;
            } else {
                // Pair is broken, single element is in left half (at mid or before)
                r = mid;
            }
        }

        return nums[l];
    }
};

/*
Time Complexity: O(log n)
- Binary search eliminating half elements each iteration
- Maximum iterations: log₂(n)

Space Complexity: O(1)
- Only using pointers (l, r, mid)

Algorithm (Binary Search with Pair Checking):
1. Initialize l=0, r=n-1
2. While l < r:
   a. Calculate mid = (l + r) / 2
   b. Normalize mid to even index: if(mid % 2 == 1) mid--
   c. Check if nums[mid] == nums[mid+1]:
      - If yes: pair exists, single element is in right half
        * Move l = mid + 2 (skip the pair)
      - If no: pair is broken, single element is in left half
        * Move r = mid (keep mid in search range)
3. Return nums[l] when l == r

Key Insight - Pair Checking:
- Before single element: all elements form complete pairs
- Pairs are at indices (0,1), (2,3), (4,5), etc.
- After single element: pairing is shifted by 1
- At index before single: even index has pair with next
- At index after single: even index does NOT have pair with next

Why Normalize to Even:
- Easier to check if mid forms a pair with mid+1
- nums[even] == nums[even+1] means pair at (even, even+1)
- If mid is odd, make it even to check the pair properly

Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Single element: 2

Initial: l=0, r=8
mid=4: nums[4]=3
- Even already (4 % 2 == 0)
- nums[4]==nums[5]? 3==4? No
- Pair is broken, single is in left
- r=4

l=0, r=4
mid=2: nums[2]=2
- Even already (2 % 2 == 0)
- nums[2]==nums[3]? 2==3? No
- Pair is broken, single is at mid
- r=2

l=0, r=2
mid=1: nums[1]=1
- Odd (1 % 2 == 1), make even: mid=0
- nums[0]==nums[1]? 1==1? Yes
- Pair exists, single is in right
- l=0+2=2

l=2, r=2: loop ends
return nums[2] = 2

Output: 2 ✓

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Single element: 10

Initial: l=0, r=6
mid=3: nums[3]=7
- Odd, make even: mid=2
- nums[2]==nums[3]? 7==7? Yes
- Pair exists, single in right
- l=2+2=4

l=4, r=6
mid=5: nums[5]=11
- Odd, make even: mid=4
- nums[4]==nums[5]? 10==11? No
- Pair broken, single in left
- r=4

l=4, r=4: loop ends
return nums[4] = 10

Output: 10 ✓

Pairing Pattern Explanation:
- Before single (indices 0,2,4,...):
  * nums[0]==nums[1] (pair)
  * nums[2]==nums[3] (pair)
  * nums[4]==nums[5] (pair)
- After single (indices shifted):
  * nums[5]!=nums[6] (broken)
  * nums[7]==nums[8] (new pairing)

Why This Breaks Down After Single:
- Original pairs: (0,1), (2,3), (4,5), (6,7)...
- Insert single at position x
- Everything after shifts by 1
- New pairing: (0,1), (2,3)..., (x), (x+1, x+2), (x+3, x+4)...

Edge Cases:
- Single at start: l=0, return nums[0]
- Single at end: eventually r points to it
- Array length 1: return nums[0]
- Array length 3: two cases to handle

Boundary Conditions:
- l < r: ensures we stop when single is found
- l == r: when loop ends, l points to single element
- l always increases by at least 2 (skips pair)
- r always decreases or stays same

Why l+2 vs l+1:
- l+1 would put us in the middle of a pair
- l+2 puts us at start of next potential pair
- Ensures we skip complete pairs
*/