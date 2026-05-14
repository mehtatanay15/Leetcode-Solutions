// LeetCode 2784: Check if it is Possible to Make Array Equal
// Problem: Determine if an array is "good"
// An array of length n is "good" if it contains:
//   - Exactly n-1 unique elements
//   - All elements from 1 to n-1 appear exactly once
//   - Element n appears at least twice
// Approach: Hash map frequency counting + validation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isGood(vector<int>& nums) {
        // Count frequency of each element
        unordered_map<int, int> mpp;
        for (int i = 0; i < nums.size(); i++) {
            mpp[nums[i]]++;
        }

        // n is the target value that should appear at least twice
        // Array has n+1 elements if it's good
        int n = nums.size() - 1;

        // Must have exactly n unique elements
        // (values 1 to n-1 unique, plus value n)
        if (mpp.size() != n) return false;

        // Validate frequency requirements
        for (auto it = mpp.begin(); it != mpp.end(); it++) {
            int val = it->first;
            int count = it->second;

            // Value n (the max) should appear at least 2 times
            if (val == n) {
                if (count < 2) return false;
            }
            // Values 1 to n-1 should appear exactly 1 time
            else if (val >= 1 && val < n) {
                if (count != 1) return false;
            }
            // Any other value makes array invalid
            else {
                return false;
            }
        }

        return true;
    }
};

/*
Time Complexity: O(n) where n is the size of the array
  - Iteration 1: Count frequencies - O(n)
  - Iteration 2: Validate map entries - O(n) in worst case
  - Total: O(n)

Space Complexity: O(n)
  - Hash map stores at most n unique elements

Algorithm Explanation:

Problem Definition:
An array of length n+1 is "good" if it contains exactly the values [1, 2, ..., n-1, n, n]
(i.e., all integers from 1 to n-1 appear once, and n appears twice)

Key Insight - Frequency Pattern:
- If array is good, it must have exactly n unique values
- Those values must be: 1, 2, ..., n-1, n
- Frequency requirement:
  * Value n: frequency = 2 (or more in general)
  * Values 1 to n-1: frequency = 1 each
  * Any other value: invalid

Validation Strategy:
1. Count frequency of all elements using hash map
2. Check if number of unique elements = n (array length - 1)
3. For each unique value:
   - If it's n: must have frequency ≥ 2
   - If it's in [1, n-1]: must have frequency = 1
   - Otherwise: invalid

Why This Works:
- If mpp.size() != n, then either:
  * We have fewer than n unique values (missing some from 1 to n)
  * We have more than n unique values (extra values beyond n)
  * Both cases make the array not good
- Then we verify the exact frequency pattern required

Example 1:
nums = [1, 1, 3, 2]
n = 4 - 1 = 3

Frequency map: {1: 2, 3: 1, 2: 1}
- mpp.size() = 3 ✓ (equals n)
- Value 3 (n): count = 1 ✗ (need ≥ 2)
- Return false

Example 2:
nums = [1, 3, 3, 2]
n = 4 - 1 = 3

Frequency map: {1: 1, 3: 2, 2: 1}
- mpp.size() = 3 ✓ (equals n)
- Value 3 (n): count = 2 ✓ (≥ 2)
- Value 1: count = 1 ✓ (in [1, n-1], count = 1)
- Value 2: count = 1 ✓ (in [1, n-1], count = 1)
- Return true

Example 3:
nums = [1, 1, 1, 2]
n = 4 - 1 = 3

Frequency map: {1: 3, 2: 1}
- mpp.size() = 2 ✗ (not equal to n=3, missing value 3)
- Return false

Edge Cases:
1. Array with values > n: Invalid (outside range)
2. Array with value 0 or negative: Invalid
3. Missing any value from 1 to n-1: Invalid (mpp.size() != n)
4. Value n appears only once: Invalid (need ≥ 2)
5. Duplicate values in [1, n-1]: Invalid (should appear exactly once)
6. Single element array [x]: n=0, valid if x=0 (but problematic case)

Optimization Notes:
- Could use array instead of hash map if values guaranteed to be in range [1, n]
- Then check by counting at indices 1 to n
- Space would be O(n) but constant factor smaller
- Time would still be O(n)
*/
