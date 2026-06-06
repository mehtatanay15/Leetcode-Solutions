// LeetCode 2574: Left and Right Sum Differences
// Problem: For each index i, find |leftSum[i] - rightSum[i]|
// Left sum: sum of all elements to the left of i
// Right sum: sum of all elements to the right of i
// Approach: Two-pass with running sums to compute in one iteration

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int leftSum = 0;
        int rightSum = 0;
        vector<int> answer;
        
        // First pass: calculate total sum (this will be initial rightSum)
        for (int num : nums) {
            rightSum += num;
        }
        
        // Second pass: calculate difference for each position
        for (int num : nums) {
            // Remove current element from right sum (it's not to the right of itself)
            rightSum -= num;
            
            // Calculate and store the absolute difference
            answer.push_back(abs(leftSum - rightSum));
            
            // Add current element to left sum for next iteration
            leftSum += num;
        }
        
        return answer;
    }
};

/*
Time Complexity: O(n) where:
  - n = length of input array
  - First pass to calculate total sum: O(n)
  - Second pass to compute differences: O(n)
  - Total: O(2n) = O(n)

Space Complexity: O(n)
  - Output array: O(n)
  - Other variables: O(1)
  - Total: O(n) for output (required)

Algorithm Explanation:

Problem Overview:
Given array nums, for each index i compute:
- leftSum[i] = sum of all elements before index i
- rightSum[i] = sum of all elements after index i
- answer[i] = |leftSum[i] - rightSum[i]|

Key Insight - Running Sums:
Instead of recalculating sums for each position:
1. Track running leftSum as we iterate forward
2. Calculate rightSum by subtracting current and past elements from total
3. Compute difference on-the-fly

Why This Works:

Initial state:
- leftSum = 0 (nothing to the left of index 0)
- rightSum = sum of entire array

At each index i:
- rightSum should be sum of elements after i
- leftSum is already sum of elements before i
- After processing i:
  - rightSum -= nums[i] (removes i from right)
  - leftSum += nums[i] (adds i to left for next iteration)

Example Walkthrough: nums = [10, 4, 8, 3]

Initial calculation:
- rightSum = 10 + 4 + 8 + 3 = 25

Iteration 1 (i=0, num=10):
- rightSum = 25 - 10 = 15 (elements to right: 4, 8, 3)
- leftSum = 0 (no elements to left)
- Difference = |0 - 15| = 15
- leftSum = 0 + 10 = 10

Iteration 2 (i=1, num=4):
- rightSum = 15 - 4 = 11 (elements to right: 8, 3)
- leftSum = 10 (element to left: 10)
- Difference = |10 - 11| = 1
- leftSum = 10 + 4 = 14

Iteration 3 (i=2, num=8):
- rightSum = 11 - 8 = 3 (elements to right: 3)
- leftSum = 14 (elements to left: 10, 4)
- Difference = |14 - 3| = 11
- leftSum = 14 + 8 = 22

Iteration 4 (i=3, num=3):
- rightSum = 3 - 3 = 0 (no elements to right)
- leftSum = 22 (elements to left: 10, 4, 8)
- Difference = |22 - 0| = 22
- leftSum = 22 + 3 = 25

Answer: [15, 1, 11, 22] ✓

Example 1: nums = [10]

Initial:
- rightSum = 10

Iteration 1 (i=0, num=10):
- rightSum = 10 - 10 = 0 (no elements to right)
- leftSum = 0 (no elements to left)
- Difference = |0 - 0| = 0

Answer: [0] ✓

Example 2: nums = [1, 2, 3, 4, 5]

Initial:
- rightSum = 15

Iteration 1 (i=0, num=1):
- rightSum = 15 - 1 = 14
- leftSum = 0
- Difference = |0 - 14| = 14
- leftSum = 1

Iteration 2 (i=1, num=2):
- rightSum = 14 - 2 = 12
- leftSum = 1
- Difference = |1 - 12| = 11
- leftSum = 3

Iteration 3 (i=2, num=3):
- rightSum = 12 - 3 = 9
- leftSum = 3
- Difference = |3 - 9| = 6
- leftSum = 6

Iteration 4 (i=3, num=4):
- rightSum = 9 - 4 = 5
- leftSum = 6
- Difference = |6 - 5| = 1
- leftSum = 10

Iteration 5 (i=4, num=5):
- rightSum = 5 - 5 = 0
- leftSum = 10
- Difference = |10 - 0| = 10

Answer: [14, 11, 6, 1, 10] ✓

Example 3: nums = [5, 5, 5, 5]

Initial:
- rightSum = 20

Iteration 1 (i=0, num=5):
- rightSum = 20 - 5 = 15
- leftSum = 0
- Difference = |0 - 15| = 15

Iteration 2 (i=1, num=5):
- rightSum = 15 - 5 = 10
- leftSum = 5
- Difference = |5 - 10| = 5

Iteration 3 (i=2, num=5):
- rightSum = 10 - 5 = 5
- leftSum = 10
- Difference = |10 - 5| = 5

Iteration 4 (i=3, num=5):
- rightSum = 5 - 5 = 0
- leftSum = 15
- Difference = |15 - 0| = 15

Answer: [15, 5, 5, 15] ✓

Example 4: nums = [1, -2, 3, -4, 5]

Initial:
- rightSum = 1 - 2 + 3 - 4 + 5 = 3

Iteration 1 (i=0, num=1):
- rightSum = 3 - 1 = 2
- leftSum = 0
- Difference = |0 - 2| = 2
- leftSum = 1

Iteration 2 (i=1, num=-2):
- rightSum = 2 - (-2) = 4
- leftSum = 1
- Difference = |1 - 4| = 3
- leftSum = -1

Iteration 3 (i=2, num=3):
- rightSum = 4 - 3 = 1
- leftSum = -1
- Difference = |-1 - 1| = 2
- leftSum = 2

Iteration 4 (i=3, num=-4):
- rightSum = 1 - (-4) = 5
- leftSum = 2
- Difference = |2 - 5| = 3
- leftSum = -2

Iteration 5 (i=4, num=5):
- rightSum = 5 - 5 = 0
- leftSum = -2
- Difference = |-2 - 0| = 2

Answer: [2, 3, 2, 3, 2] ✓

Example 5: nums = [100, 200, 300]

Initial:
- rightSum = 600

Iteration 1 (i=0, num=100):
- rightSum = 600 - 100 = 500
- leftSum = 0
- Difference = |0 - 500| = 500
- leftSum = 100

Iteration 2 (i=1, num=200):
- rightSum = 500 - 200 = 300
- leftSum = 100
- Difference = |100 - 300| = 200
- leftSum = 300

Iteration 3 (i=2, num=300):
- rightSum = 300 - 300 = 0
- leftSum = 300
- Difference = |300 - 0| = 300

Answer: [500, 200, 300] ✓

Edge Cases Handled:

1. Single element:
   - leftSum = 0, rightSum = 0
   - Difference = 0 ✓

2. Two elements [a, b]:
   - At i=0: |0 - b| = b
   - At i=1: |a - 0| = a
   - Correct ✓

3. All same elements:
   - Differences are symmetric around middle
   - Handled correctly ✓

4. Negative numbers:
   - abs() handles all cases
   - Works with negatives ✓

5. Very large values:
   - Sum might overflow int
   - Problem constraints should guarantee no overflow
   - Use long long if needed

Why This Algorithm is Optimal:

1. Linear Time:
   - Two simple passes through array
   - O(n) is optimal (must read all elements)

2. Space Efficient:
   - O(n) for output (required)
   - O(1) extra space (just variables)

3. Clear and Intuitive:
   - Straightforward logic
   - Easy to understand and debug
   - No complex data structures

Alternative Approaches:

1. Brute Force (less efficient):
```cpp
for (int i = 0; i < n; i++) {
    int leftSum = 0, rightSum = 0;
    for (int j = 0; j < i; j++) leftSum += nums[j];
    for (int j = i + 1; j < n; j++) rightSum += nums[j];
    answer.push_back(abs(leftSum - rightSum));
}
```
- Time: O(n²)
- Space: O(n)
- Too slow

2. Prefix/Suffix Arrays:
```cpp
vector<int> prefix(n), suffix(n);
for (i = 0; i < n; i++) {
    prefix[i] = (i > 0 ? prefix[i-1] : 0) + nums[i];
    suffix[i] = (i < n-1 ? suffix[i+1] : 0) + nums[i];
}
for (i = 0; i < n; i++) {
    int leftSum = (i > 0 ? prefix[i-1] : 0);
    int rightSum = (i < n-1 ? suffix[i+1] : 0);
    answer.push_back(abs(leftSum - rightSum));
}
```
- Time: O(n)
- Space: O(n) extra
- More complex but clearer for some

3. HashMap (unnecessary):
```cpp
unordered_map<int, pair<int,int>> cache;
// Doesn't help here
```
- Not applicable

Current solution is best:
- O(n) time
- O(1) extra space
- Simple and clear

Why This Problem is Useful:

1. Teaches prefix sum technique
2. Shows single-pass optimization
3. Good for practicing array manipulation
4. Common interview problem
5. Foundation for more complex problems

When to Use This Pattern:

1. Need left and right information
2. Can calculate incrementally
3. Want to avoid nested loops
4. Space efficiency matters

Real-world Applications:

1. Array partitioning algorithms
2. Load balancing (balance left vs right)
3. Tree traversal (left subtree vs right subtree)
4. Signal processing (left channel vs right channel)
5. Game logic (left side vs right side)

Related Problems:
- Maximum Subarray (prefix sum)
- Subarray Sum Equals K (hashmap + prefix)
- Product of Array Except Self (prefix/suffix)
- Prefix Sum Range Queries
- Range Sum Query

Variants:

1. Find index with minimum difference:
```cpp
int minDiff = INT_MAX, minIndex = 0;
for (int i = 0; i < answer.size(); i++) {
    if (answer[i] < minDiff) {
        minDiff = answer[i];
        minIndex = i;
    }
}
return minIndex;
```

2. Find if any index has difference > threshold:
```cpp
for (int diff : answer) {
    if (diff > threshold) return true;
}
return false;
```

3. Return sum of all differences:
```cpp
long long sum = 0;
for (int diff : answer) sum += diff;
return sum;
```

4. Return differences mod some value:
```cpp
for (int& diff : answer) diff %= MOD;
```

Learning Points:

1. Two-pass optimization
2. Running sum technique
3. In-place calculation
4. Space optimization
5. Problem analysis and optimization
6. When simple is better than complex

Code Quality:

Strengths:
- Clear variable names
- Simple logic
- Efficient space usage
- No unnecessary operations

Potential Improvements:
- Add comments for clarity
- Could use long long for safety
- Could add input validation

Complexity Analysis Justification:

Time: O(n)
- First loop: n iterations, O(n)
- Second loop: n iterations, O(n)
- Total: 2n = O(n)

Space: O(n)
- Output array: n elements, O(n)
- Other variables: O(1)
- Total: O(n) dominated by output

Why O(n) is optimal:
- Must read all n elements
- Must write n results
- Cannot do better

Performance Metrics:

For n = 10^5:
- Time: < 1ms
- Space: ~400KB (int array)
- Total operations: ~200,000

For n = 10^6:
- Time: ~5ms
- Space: ~4MB
- Total operations: ~2M

Linear growth, no issues at scale.

Common Mistakes to Avoid:

1. Forgetting abs():
   - Differences can be negative
   - Must use abs() or handle signs

2. Not updating rightSum:
   - Must remove current element from rightSum
   - Forgetting this gives wrong answer

3. Not updating leftSum:
   - Must add current element to leftSum
   - For next iteration to be correct

4. Wrong order of operations:
   - rightSum -= num before using it
   - leftSum += num after using it

5. Off-by-one errors:
   - Array indexing is 0-based
   - Loop bounds must be correct

6. Integer overflow:
   - Sum can exceed int range
   - Use long long if needed

Why This Problem is Good:

- Simple problem with elegant solution
- Teaches important technique
- Common in interviews
- Good for learning optimization
- Foundation for more complex problems

Final Notes:

This is a classic problem because:
- Simple to state
- Non-obvious optimization exists
- Teaches important technique
- Common in interviews
- Great learning example

The key insight:
- Use running sums to avoid recomputation
- Process in single pass
- Calculate both left and right incrementally
- Result is O(n) instead of O(n²) or O(n) with O(n) space

This pattern applies to many problems:
- Any left/right information
- Any prefix/suffix computation
- Any incremental calculation
- Any two-pointer scenarios

Master this technique and apply it widely!
*/
