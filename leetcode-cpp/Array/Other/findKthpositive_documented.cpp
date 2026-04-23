// LeetCode 1539: Kth Missing Positive Number
// Problem: Find the kth missing positive integer in a sorted array
// Approach: Binary Search on array with missing count calculation

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        // Binary search to find the right position
        int low = 0, high = arr.size() - 1;

        while(low <= high)
        {
            int mid = (low + high) / 2;

            // Count missing positive integers up to arr[mid]
            // If arr[mid] appears at position (mid+1) (1-indexed),
            // then arr[mid] - (mid+1) numbers are missing before it
            int missing = arr[mid] - (mid + 1);

            if(missing < k)
            {
                // Need to find further, go right
                low = mid + 1;
            }
            else
            {
                // Can find in left part, go left
                high = mid - 1;
            }
        }

        // After binary search:
        // 'low' is where the kth missing number would be inserted
        // Answer = low (0-indexed position in search space) + k
        return low + k;
    }
};

/*
Time Complexity: O(log n)
- Binary search on array of size n

Space Complexity: O(1)
- Only constant extra space

Algorithm (Binary Search with Missing Count):
1. Binary search on array positions
2. For each mid position, calculate missing count:
   - missing = arr[mid] - (mid + 1)
   - Explanation: at position mid (0-indexed), we expect value mid+1
   - If arr[mid] is at position mid, then arr[mid] - (mid+1) values are missing
3. If missing < k: the kth missing is beyond arr[mid], search right
4. If missing >= k: the kth missing is at or before arr[mid], search left
5. After binary search, return low + k

Key Insight - Missing Count Formula:
- Array is sorted, all elements are distinct positive integers
- At position i (0-indexed), if array was complete, value would be i+1
- If arr[i] > i+1, some numbers are missing
- missing = arr[i] - (i+1) tells how many before arr[i]

Example 1:
Input: arr = [2,3,4,7,11], k = 5

Positive integers: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
Array:            _, 2, 3, 4, _, 7, _, _, _, _, 11
Missing:          1, _, _, _, 5, _, 6, 8, 9, 10, _

Count missing: 1(one), 5(two), 6(three), 8(four), 9(five)
Answer: 9

Binary search:
low=0, high=4

mid=2: arr[2]=4
missing = 4 - 3 = 1
1 < 5? Yes, low=3

mid=3: arr[3]=7
missing = 7 - 4 = 3
3 < 5? Yes, low=4

mid=4: arr[4]=11
missing = 11 - 5 = 6
6 < 5? No, high=3

low > high, return low+k = 4+5 = 9 ✓

Example 2:
Input: arr = [1,2,3,4], k = 2

Missing positive: 5, 6, 7, ...
We need the 2nd one = 6

Binary search:
low=0, high=3

mid=1: arr[1]=2
missing = 2 - 2 = 0
0 < 2? Yes, low=2

mid=2: arr[2]=3
missing = 3 - 3 = 0
0 < 2? Yes, low=3

mid=3: arr[3]=4
missing = 4 - 4 = 0
0 < 2? Yes, low=4

low > high, return low+k = 4+2 = 6 ✓

Example 3:
Input: arr = [1,2,3,4,5], k = 1

Missing: 6, 7, 8, ...
We need 1st missing = 6

All elements present, arr[i] = i+1 for all i
missing at arr[4] = 5 - 5 = 0
So kth missing must be after the entire array

Binary search will eventually set low = 5 (beyond array)
Answer = 5 + 1 = 6 ✓

Edge Cases:
- k = 1, arr = [2,3,4]: missing count = 1, answer = 1
- k = 1, arr = [1,3,5]: missing count = 1 at position 1, answer = 2
- Array has no missing: answer = arr.size() + k
- k = 1, arr = [1,2,3]: answer = 4

Missing Count at Each Position:
Position 0: arr[0] - 1 = missing before arr[0]
Position 1: arr[1] - 2 = missing before arr[1]
Position i: arr[i] - (i+1) = missing before arr[i]

Why This Formula Works:
- Positive integers: 1, 2, 3, 4, 5, 6, ...
- Position 0 should have 1 (if no missing)
- Position 1 should have 2 (if no missing)
- Position i should have i+1 (if no missing)
- If arr[i] > i+1, gaps exist

Visual Example:
arr = [2,3,4,7,11]
Position: 0,1,2,3,4
Expected: 1,2,3,4,5 (if complete)
Actual:   2,3,4,7,11
Missing:  1 before 2, none before 3, none before 4, 5-6 before 7, 8-10 before 11

Missing counts:
Position 0: 2-1 = 1
Position 1: 3-2 = 1
Position 2: 4-3 = 1
Position 3: 7-4 = 3
Position 4: 11-5 = 6

Finding k=5:
Missing count increases: 1,1,1,3,6
We want where missing <= k but next missing > k
missing[3]=3 < 5 <= 6
So we search right of position 3

Final answer: position 4 (value 11)
kth missing = low + k = 4 + 5 = 9
(4 means position after index 4 in the logical array)

Why low + k Works:
- After binary search, low points to position where kth missing would be
- If all numbers 1 to low were present, they'd be at positions 0 to low-1
- Kth missing would be at position (low + k - 1) in sorted order
- Since we need the value (1-indexed), answer = low + k

Example: low=4, k=2
Numbers 1-4 plus missing count 2
1-indexed position: 4 + 2 = 6

Alternative Linear Approach (slower):
int findKthPositive(vector<int>& arr, int k) {
    int missing = 0;
    int i = 0;
    int num = 1;
    while(missing < k && i < arr.size()) {
        if(arr[i] != num) {
            missing++;
            if(missing == k) return num;
            num++;
        } else {
            i++;
            num++;
        }
    }
    return num + (k - missing - 1);
}

Time: O(n+k), Space: O(1)
But binary search is O(log n), much better

This Binary Search on Answer pattern applies to:
- Finding kth element after transformation
- Missing element problems
- Array with gaps
- Mapping position to value

Correctness Proof:
- Binary search finds position where arr[pos] - (pos+1) >= k
- For all previous positions, missing < k
- This means in the space [1, arr[pos]], there are exactly missing < k numbers before arr[pos]
- The kth missing is at position low+k in the complete positive integers sequence

*/
