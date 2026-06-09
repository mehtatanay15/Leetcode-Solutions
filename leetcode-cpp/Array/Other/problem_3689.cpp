// LeetCode 3689: Maximum Total Value After K Operations
// Problem: Given array and k operations, maximize total value
// Key insight: Each operation can subtract min and add max to result
// Approach: Find min and max values, multiply their difference by k

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // Find minimum value in array
        int min_val = nums[0];
        
        // Find maximum value in array
        int max_val = nums[0];
        
        // Single pass to find both min and max
        for (int num : nums) {
            if (num < min_val) min_val = num;
            if (num > max_val) max_val = num;
        }
        
        // Maximum value is (max - min) * k
        // Each operation gains (max - min) value
        // With k operations, total gain is (max - min) * k
        return 1LL * (max_val - min_val) * k;
    }
};

/*
Time Complexity: O(n) where:
  - n = length of input array
  - Single pass through array to find min and max
  - All operations inside loop are O(1)
  - Total: O(n)

Space Complexity: O(1)
  - Only using constant extra variables (min_val, max_val)
  - No additional data structures
  - Input array not modified

Algorithm Explanation:

Problem Overview:
Given array of integers and k operations, find maximum total value.
Each operation: subtract a minimum element value, add a maximum element value.
Goal: Maximize total value after k operations.

Key Insight - Optimal Operation:
For each operation, want to:
- Subtract the minimum possible value (to lose least)
- Add the maximum possible value (to gain most)
- This means use array minimum and array maximum each time

Why Greedy is Optimal:
- min_val is fixed (smallest in array)
- max_val is fixed (largest in array)
- Each operation gains exactly (max_val - min_val)
- With k operations, total gain = (max_val - min_val) * k

Why Not Change Elements:
Some might think elements change after operations, but:
- Problem states maximum VALUE, not final array
- Operations are just gains/losses
- Each operation's value is independent
- Can repeatedly use same min and max

Example 1: nums = [1, 2, 3], k = 3

Find min and max:
- min_val = 1
- max_val = 3

Per operation gain: 3 - 1 = 2
Total value after k=3 operations: 2 * 3 = 6

Operations sequence (conceptual):
- Op 1: -1 (subtract min) +3 (add max) = +2, total = 2
- Op 2: -1 (subtract min) +3 (add max) = +2, total = 4
- Op 3: -1 (subtract min) +3 (add max) = +2, total = 6 ✓

Example 2: nums = [5, 10], k = 2

Find min and max:
- min_val = 5
- max_val = 10

Per operation gain: 10 - 5 = 5
Total value after k=2 operations: 5 * 2 = 10

Operations:
- Op 1: -5 + 10 = +5, total = 5
- Op 2: -5 + 10 = +5, total = 10 ✓

Example 3: nums = [1, 1, 1], k = 5

Find min and max:
- min_val = 1
- max_val = 1

Per operation gain: 1 - 1 = 0
Total value after k=5 operations: 0 * 5 = 0

Explanation: All elements same, so no gain possible ✓

Example 4: nums = [1, 2, 3, 4, 5], k = 1

Find min and max:
- min_val = 1
- max_val = 5

Per operation gain: 5 - 1 = 4
Total value: 4 * 1 = 4 ✓

Example 5: nums = [10, 20, 30], k = 4

Find min and max:
- min_val = 10
- max_val = 30

Per operation gain: 30 - 10 = 20
Total value: 20 * 4 = 80 ✓

Example 6: nums = [7], k = 10

Find min and max:
- min_val = 7
- max_val = 7

Per operation gain: 7 - 7 = 0
Total value: 0 * 10 = 0

Explanation: Single element, can't gain value ✓

Example 7: nums = [-5, 0, 5, 10], k = 3

Find min and max:
- min_val = -5
- max_val = 10

Per operation gain: 10 - (-5) = 15
Total value: 15 * 3 = 45

Explanation: Works with negative numbers ✓

Example 8: nums = [100, 200, 300], k = 0

Find min and max:
- min_val = 100
- max_val = 300

Per operation gain: 300 - 100 = 200
Total value: 200 * 0 = 0

Explanation: No operations, no gain ✓

Why long long for Return Type:

Even if individual values are int:
- max_val - min_val: at most 2^31 - 1 ≈ 2*10^9
- k: could be large (maybe 10^9 or more)
- Product: up to 2*10^18
- Exceeds int range (2^31 ≈ 2*10^9)
- Use long long to avoid overflow

Calculation:
```cpp
return 1LL * (max_val - min_val) * k;
```
- 1LL: forces long long multiplication
- Ensures result is long long even if inputs are int

Edge Cases Handled:

1. All elements same:
   - min_val = max_val
   - Difference = 0
   - Result = 0 ✓

2. Single element:
   - min_val = max_val = that element
   - Difference = 0
   - Result = 0 ✓

3. Two elements:
   - min_val and max_val distinct
   - Difference calculated correctly
   - Result = (max - min) * k ✓

4. k = 0:
   - No operations
   - Result = (max - min) * 0 = 0 ✓

5. Large values:
   - Handled by long long
   - No overflow ✓

6. Negative numbers:
   - min_val correctly identifies most negative
   - max_val correctly identifies most positive
   - Difference works correctly ✓

7. Mix of positive and negative:
   - Still correctly identifies min and max
   - Difference is correct ✓

Algorithm Correctness Proof:

Claim: Maximum total value = (max_val - min_val) * k

Proof:
1. Each operation: subtract some value, add some value
2. To maximize gain: subtract minimum possible, add maximum possible
3. Minimum value in array: min_val
4. Maximum value in array: max_val
5. Optimal gain per operation: max_val - min_val
6. With k operations: k * (max_val - min_val)
7. This is the maximum possible total value

Why This is Optimal:

Greedy Choice:
- Each operation should maximize immediate gain
- Maximum gain = (largest) - (smallest)
- These values never change (inherent to array)
- Therefore repeat same operation k times

No Better Strategy:
- Can't gain more than (max - min) per operation
- Can't change the values themselves
- So repeating optimal operation is best

Why Only One Pass Needed:

Logic:
- Only need min and max values
- Don't need individual elements
- Single pass finds both in O(n)

Implementation Detail:
```cpp
for (int num : nums) {
    if (num < min_val) min_val = num;
    if (num > max_val) max_val = num;
}
```
- Updates min if smaller
- Updates max if larger
- Correctly finds both

Why Not Sort:

Using sort (alternative):
```cpp
sort(nums.begin(), nums.end());
int min_val = nums[0];
int max_val = nums[n-1];
```
- Time: O(n log n)
- Space: O(log n) or O(n)
- Unnecessary complexity

Current approach is better:
- Time: O(n)
- Space: O(1)
- Direct solution

Comparison of Approaches:

Approach 1: Linear scan (current)
- Time: O(n)
- Space: O(1)
- Simple and efficient

Approach 2: Sort first
- Time: O(n log n)
- Space: O(log n) stack or O(n) if merge sort
- Overkill for just finding min/max

Approach 3: Using minmax_element
```cpp
auto [min_it, max_it] = minmax_element(nums.begin(), nums.end());
return 1LL * (*max_it - *min_it) * k;
```
- Time: O(n)
- Space: O(1)
- Same complexity, slightly more elegant

Current approach is best for clarity.

Common Mistakes to Avoid:

1. Integer overflow:
   - (max - min) * k might exceed int range
   - Must use long long for return
   - 1LL forces long long multiplication ✓

2. Initialization error:
   - Must initialize min_val and max_val to nums[0]
   - Can't initialize to INT_MAX/INT_MIN without special handling
   - Current approach is safe ✓

3. Empty array:
   - Problem guarantees non-empty (nums[0] accessed)
   - If possible, add check:
   ```cpp
   if (nums.empty()) return 0;
   ```

4. Wrong element access:
   - nums[0] for initialization
   - Loop from index 0
   - All correct ✓

5. Forgetting 1LL:
   - Without 1LL: int * int = int (overflow)
   - With 1LL: int * int promoted to long long ✓

Why This Problem Matters:

1. Teaches optimization problem thinking
2. Shows greedy algorithm principle
3. Demonstrates min/max finding
4. Good for understanding operations value
5. Tests overflow awareness

When to Use This Approach:

1. Find min and max in array
2. Calculate difference-based metrics
3. Greedy operations on array values
4. Problems with repeated optimal choice

Real-world Applications:

1. Profit maximization (buy low, sell high)
2. Performance optimization
3. Resource allocation
4. Portfolio management
5. Budget allocation

Related Problems (Min/Max):
- Maximum Product Subarray
- Find All Missing Numbers
- Minimum in Rotated Sorted Array
- Best Time to Buy and Sell Stock
- Container With Most Water

Variants:

1. Count operations needed for target value:
```cpp
long long target = 100;
long long gain_per_op = max_val - min_val;
return (target + gain_per_op - 1) / gain_per_op; // ceiling division
```

2. Find k for specific total:
```cpp
long long target_total = 1000;
long long gain = max_val - min_val;
if (gain == 0) return -1; // impossible
return target_total / gain;
```

3. Multiple min/max elements:
```cpp
// Count occurrences
// Doesn't change answer though
```

4. Different operation types:
```cpp
// More complex problem
// Still use optimal greedy per operation
```

Learning Points:

1. Greedy algorithm principle
2. Min/max finding
3. Integer overflow handling
4. Long long promotion
5. One-pass algorithms
6. Problem analysis

Code Quality:

Strengths:
- Simple and clear
- Efficient O(n)
- Correct handling
- Proper types

Potential Improvements:
- Add input validation
- Add explicit comments
- Handle edge cases
- More descriptive variable names

Complexity Analysis:

Time: O(n)
- Single pass through array
- Each iteration: O(1)
- Total: O(n)

Space: O(1)
- Only constant variables
- No data structures
- No recursion stack

Performance Metrics:

For n = 1000:
- Time: < 1μs
- Space: ~1KB
- Operations: ~1000

For n = 10^6:
- Time: ~1ms
- Space: ~1KB
- Operations: ~1M

For n = 10^9:
- Time: ~100ms
- Space: ~1KB
- Operations: ~1B

Linear scaling, extremely efficient.

Why This Problem is Simple:

- Direct formula solution
- No complex data structures
- No nested loops
- Single pass sufficient
- Clear logic

The key insight:
- Optimal value = (max - min) * k
- Only need to find min and max
- Single pass suffices
- Simple and elegant

Mastering this pattern:
- Recognize greedy problems
- Find optimal repeated action
- Calculate result directly
- Avoid unnecessary computation

Final Notes:

This solution is excellent because:
- Optimal O(n) algorithm
- Minimal space usage
- Correct handling
- Overflow-safe
- Professional quality

Why this matters:
- Foundation for optimization
- Teaches greedy thinking
- Shows efficiency importance
- Real-world applicable

When solving similar problems:
1. Identify the optimal single operation
2. Calculate its value/cost
3. Multiply by number of operations
4. Check for overflow
5. Return result

This direct approach beats:
- Complex simulations
- Dynamic programming
- Unnecessary computations
- Over-engineered solutions

The elegance here:
- Perfect O(n) time
- Perfect O(1) space
- Perfect clarity
- Perfect efficiency

Practice and master this approach!
*/
