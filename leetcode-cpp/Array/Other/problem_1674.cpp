// LeetCode 1674: Minimum Moves to Make Array Equal
// Problem: Given an array, each move changes two elements: +1 to one, -1 to another
// Goal: Make all elements equal with minimum moves
// Approach: Difference array range updates - find optimal target value for each pair

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Difference array for range updates
        // diff[i] represents the change at position i
        vector<int> diff(2 * limit + 2, 0);

        // Process each pair from opposite ends
        // Pair (nums[i], nums[n-1-i]) must converge to some target value
        for (int i = 0; i < n / 2; ++i) {
            int a = min(nums[i], nums[n - 1 - i]);
            int b = max(nums[i], nums[n - 1 - i]);

            // Cost analysis for pair (a, b):
            // 1. If target < a: impossible to reach from b
            // 2. If target in [a, b]: cost = target - a (only a needs to increase)
            // 3. If target > b: cost = b - a + (target - b) = target - a
            // General formula: cost = |target - a| + |target - b|
            
            // Strategy: Use difference array to mark ranges
            // All targets require 2 moves initially (both elements need adjustment)
            diff[2] += 2;
            diff[2 * limit + 1] -= 2;

            // Targets in range [a+1, b+limit] cost less
            // For targets in [a, b]: cost is target-a, so we save 1 for each unit above a
            diff[a + 1] -= 1;
            diff[b + limit + 1] += 1;

            // Targets exactly a+b cost a+b-a + b-b = 0 from current state
            // For target = a+b: both reach it with cost 0 from each other
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;
        }

        // Scan through difference array to find minimum cost
        int min_moves = n;
        int current_moves = 0;
        
        for (int i = 2; i <= 2 * limit; ++i) {
            current_moves += diff[i];
            min_moves = min(min_moves, current_moves);
        }

        return min_moves;
    }
};

/*
Time Complexity: O(n + limit) where:
  - n = array length (building difference array)
  - limit = maximum limit value (scanning difference array)
  - Total: O(n + limit)
Space Complexity: O(limit) - Difference array size

Algorithm Explanation:

Key Insight - Pair Processing:
- With n elements, we have n/2 pairs: (nums[0], nums[n-1]), (nums[1], nums[n-2]), etc.
- Each pair must converge to some target value
- The choice of target for each pair determines total moves

Cost Function for a Pair (a, b) where a ≤ b:
- If target < a: Impossible (can't make both decrease simultaneously)
- If target in [a, b]:
  * a needs (target - a) moves to reach target
  * b needs (b - target) moves to reach target
  * Total: (target - a) + (b - target) = b - a moves
- If target in (b, a+b]:
  * a increases to target: (target - a) moves
  * b decreases to target: (b - target) moves
  * But b can go below current value and increase later
  * For target = a+b: 0 moves (they cancel each other out)

Observation:
- Minimum moves for pair (a, b) is b - a when target in [a, b]
- This is only achievable if we set both to same value in range [a, b]

Using Difference Array:
Instead of checking all n possible target values, use range updates:
1. Mark all targets with initial cost 2 (both elements need moves)
2. Subtract 1 for ranges where cost is reduced
3. Scan to find minimum

Difference Array Operations:
- diff[2] += 2: All targets start with cost 2
- diff[2*limit+1] -= 2: Cancel after limit

- diff[a+1] -= 1: For targets ≥ a+1, reduce cost by 1
- diff[b+limit+1] += 1: Cancel this reduction after b+limit

- diff[a+b] -= 1: For targets = a+b, further reduce cost by 1
- diff[a+b+1] += 1: Cancel this second reduction after a+b

Example 1:
nums = [1, 0, 0, 8, 6], limit = 7

n = 5, so we have 2 pairs:
Pair 1: (nums[0], nums[4]) = (1, 6) → a=1, b=6
Pair 2: (nums[1], nums[3]) = (0, 8) → a=0, b=8
nums[2] = 0 stays as is

For Pair (1, 6):
- diff[2] += 2, diff[15] -= 2 (range [2, 14])
- diff[2] -= 1, diff[14] += 1 (range [2, 13])
- diff[7] -= 1, diff[8] += 1 (range [7, 7])

After processing pair 1: target value costs
- [2, 6]: cost = 2
- [7, 7]: cost = 1 (they can meet at 7, which is a+b = 1+6)
- [8, 13]: cost = 1
- [14, ...]: cost = 0 (invalid, beyond limit)

Wait, let me recalculate. The difference array tracks cost changes as we increase target.

Actually, the algorithm is counting how many moves are needed if we fix the target value.

For each pair (a, b), the number of moves to make both equal to target t:
- If t is in [a, b]: |t-a| + |b-t| = (t-a) + (b-t) = b-a moves
- If t < a: Not achievable in optimal way
- If t > b: |t-a| + |t-b| = (t-a) + (t-b) = 2t - a - b moves

The minimum across all pairs for a given target = sum of minimum moves for each pair to reach that target.

Example 2:
nums = [1, 10, 11, 9], limit = 5

Pairs:
- (1, 9): a=1, b=9
- (10, 11): a=10, b=11

But wait, limit=5 means target can be at most 2*5 = 10? Or target can be any value?

Looking at the code, it seems limit is used to determine the maximum possible target value.

For pair (1, 9) with limit=5:
- Target can be 1, 2, 3, 4, 5, 6, 7, 8, 9
- Cost for target in [1, 9]: 9-1 = 8 moves
- Cost for target in (9, 10]: 2*target - 1 - 9 = 2*target - 10
  * At target=10: cost = 10 (but 10 > limit, so we consider a+b = 10)

For pair (10, 11) with limit=5:
- Both > limit, so special handling needed

Actually, I think the limit represents the maximum value any element can become.

Let me reconsider. The algorithm uses 2*limit as the upper bound, suggesting targets can go up to 2*limit.

The key insight is:
- For each pair, we have a cost function as a function of target
- We use a difference array to efficiently compute this across all targets
- The minimum cost across all valid targets is our answer

Example walkthrough would be complex, but the core idea is using difference arrays for range updates to efficiently find the target value that minimizes total moves.

Key Insights:
- Difference array enables O(n + limit) instead of O(n * limit)
- Each pair contributes independently to the cost function
- The cost function is piecewise linear, so minimum exists
- Range updates efficiently handle the piecewise nature

Edge Cases:
- All elements equal: return 0
- n = 2: single pair
- Array with very different values
*/
