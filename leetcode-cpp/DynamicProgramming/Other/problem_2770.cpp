// LeetCode 2770: Maximum Jumps
// Problem: From index i, can jump to index j if |nums[j] - nums[i]| <= target
// Find the maximum number of jumps to reach the last index
// Return -1 if last index is unreachable
// Approach: Dynamic Programming - tabulation with forward iteration

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        
        // dp[i] = maximum jumps to reach index i
        // Initialize with -1 (unreachable), 0 for starting position
        vector<int> dp(n, -1);
        dp[0] = 0;  // Start at index 0 with 0 jumps

        // Iterate through each index
        for (int i = 0; i < n; i++) {
            // Skip unreachable indices
            if (dp[i] == -1) {
                continue;
            }

            // Try to jump to all positions after current index
            for (int j = i + 1; j < n; j++) {
                int diff = nums[j] - nums[i];
                
                // Check if jump is valid
                // Can jump if absolute difference is within target
                // This is equivalent to: -target <= diff <= target
                if (diff <= target && diff >= -target) {
                    // Update maximum jumps to reach j
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }
        
        return dp[n - 1];
    }
};

/*
Time Complexity: O(n²) - For each index, check all subsequent indices
  - Outer loop: O(n)
  - Inner loop: O(n)
  - Total: O(n²)
Space Complexity: O(n) - DP array storage

Algorithm Explanation:

Key Concept - Valid Jump:
- From index i to index j (where j > i)
- Jump is valid if: |nums[j] - nums[i]| <= target
- Equivalently: -target <= (nums[j] - nums[i]) <= target
- No backward jumps allowed (j must be > i)

Dynamic Programming Approach:
1. dp[i] = maximum number of jumps to reach index i
2. Initialize: dp[0] = 0 (start at index 0), all others = -1 (unreachable)
3. For each index i where dp[i] != -1:
   - Try jumping to all indices j > i
   - If jump is valid: dp[j] = max(dp[j], dp[i] + 1)
4. Return dp[n-1] (result at last index)

Why Forward Iteration Works:
- Since we only jump forward (j > i), processing in order guarantees:
  - When we process index i, all valid jumps from i are to future indices
  - These future indices will be processed later
  - No need for recursion or memoization (tabulation approach)

Example 1:
nums = [1,3,1,4,1,5], target = 3

DP progression:
i=0 (nums[0]=1, dp[0]=0):
  j=1: diff=3-1=2 ≤ 3 ✓ → dp[1] = max(-1, 0+1) = 1
  j=2: diff=1-1=0 ≤ 3 ✓ → dp[2] = max(-1, 0+1) = 1
  j=3: diff=4-1=3 ≤ 3 ✓ → dp[3] = max(-1, 0+1) = 1
  j=4: diff=1-1=0 ≤ 3 ✓ → dp[4] = max(-1, 0+1) = 1
  j=5: diff=5-1=4 > 3 ✗

i=1 (nums[1]=3, dp[1]=1):
  j=2: diff=1-3=-2, |-2| ≤ 3 ✓ → dp[2] = max(1, 1+1) = 2
  j=3: diff=4-3=1 ≤ 3 ✓ → dp[3] = max(1, 1+1) = 2
  j=4: diff=1-3=-2, |-2| ≤ 3 ✓ → dp[4] = max(1, 1+1) = 2
  j=5: diff=5-3=2 ≤ 3 ✓ → dp[5] = max(-1, 1+1) = 2

i=2 (nums[2]=1, dp[2]=2):
  j=3: diff=4-1=3 ≤ 3 ✓ → dp[3] = max(2, 2+1) = 3
  j=4: diff=1-1=0 ≤ 3 ✓ → dp[4] = max(2, 2+1) = 3
  j=5: diff=5-1=4 > 3 ✗

i=3 (nums[3]=4, dp[3]=3):
  j=4: diff=1-4=-3, |-3| ≤ 3 ✓ → dp[4] = max(3, 3+1) = 4
  j=5: diff=5-4=1 ≤ 3 ✓ → dp[5] = max(2, 3+1) = 4

i=4 (nums[4]=1, dp[4]=4):
  j=5: diff=5-1=4 > 3 ✗

i=5 (nums[5]=5, dp[5]=4): No more indices

Final dp: [0, 1, 2, 3, 4, 4]
Result: dp[5] = 4

One possible path: 0 → 2 → 1 → 3 → 4 → 5 (5 jumps)
Wait, that's 4 jumps between 6 positions. Let me recount:
Jump 1: 0 → 2
Jump 2: 2 → 3  (diff=4-1=3 ≤ 3)
Jump 3: 3 → 4  (diff=1-4=-3)
Jump 4: 4 → 5  (diff=5-1=4 > 3) ✗

Let me try: 0 → 1 → 3 → 4 → 5
Jump 1: 0 → 1 (diff=3-1=2)
Jump 2: 1 → 3 (diff=4-3=1)
Jump 3: 3 → 4 (diff=1-4=-3)
Jump 4: 4 → 5 (diff=5-1=4 > 3) ✗

Hmm, let me try: 0 → 2 → 1 → 3 → 5
Jump 1: 0 → 2 (diff=1-1=0)
Jump 2: 2 → 1? (Can't go backward, j must be > i)

Actually, we can only jump forward (j > i), so the order must be strictly increasing in indices.

Let me reconsider: 0 → 1 → 2 (diff=1-3=-2) → 4 (diff=1-1=0) → 5 (diff=5-1=4 > 3) ✗

Or: 0 → 3 (diff=4-1=3) → 4 (diff=1-4=-3) → 5 (diff=5-1=4 > 3) ✗

Or: 0 → 4 (diff=1-1=0) → 5 (diff=5-1=4 > 3) ✗

Actually from my dp calculation above, dp[5] = 4, which means 4 jumps to reach index 5.
But the maximum should be at index 5 with dp[5] = 4.

Wait, I think I made an error. Let me recalculate more carefully:

i=3 (nums[3]=4, dp[3]=3):
  j=5: diff=5-4=1 ≤ 3 ✓ → dp[5] = max(-1, 3+1) = 4

So one path achieving 4 jumps to index 5 must exist.

Possible path to reach index 5 in 4 jumps:
0 → 1 → 3 → 4 → ? (need to reach 5)

Actually, from index 4, we can't reach 5 because |5-1| = 4 > 3.
From index 3, we can reach 5 because |5-4| = 1 ≤ 3.

So path: 0 → 1 → 3 → 5 is 3 jumps.

But from index 4, the difference is 4, which exceeds target 3.
So from 4 we can't reach 5.

Let me recalculate the final answer. Based on my DP table:
dp[5] after all iterations should be 4.

Ah! I see my error. After processing all indices, index 4 updates index 5, but index 5 is already processed, so we need to continue.

Actually, wait. After i=3, we have dp[5] = 4.
Then at i=4, we check j=5, but |5-1| = 4 > 3, so no update.

So the final answer is dp[5] = 4. But how to verify the path?

Let me think: if dp[5] = 4, there must be a sequence of 4 jumps reaching 5.
One possibility could be a different index update.

Actually, reviewing my trace:
- i=3: dp[5] gets set to max(2, 3+1) = 4

So one path is: something reaches index 3 with 3 jumps, then 3→5.

What path reaches index 3 with 3 jumps?
- i=2: dp[3] gets set to max(1, 2+1) = 3

So one path is: something reaches index 2 with 2 jumps, then 2→3.

What path reaches index 2 with 2 jumps?
- i=1: dp[2] gets set to max(1, 1+1) = 2

So one path is: something reaches index 1 with 1 jump, then 1→2.

What path reaches index 1 with 1 jump?
- i=0: dp[1] gets set to max(-1, 0+1) = 1

So path: 0 → 1 → 2 → 3 → 5
That's 4 jumps! And all differences check:
- 0→1: |3-1|=2 ≤ 3 ✓
- 1→2: |1-3|=2 ≤ 3 ✓
- 2→3: |4-1|=3 ≤ 3 ✓
- 3→5: |5-4|=1 ≤ 3 ✓

Great! So the answer is 4, which matches dp[5] = 4.

Example 2:
nums = [7,6,5,4,3,2,1], target = 1
All elements are decreasing, and differences between consecutive elements are 1.

From index 0:
  j=1: diff=-1, |-1| ≤ 1 ✓ → dp[1] = 1

From index 1:
  j=2: diff=-1, |-1| ≤ 1 ✓ → dp[2] = 2

And so on, dp[n-1] = n-1 = 6

Example 3:
nums = [6,9,6,5,7,8], target = 1

From index 0 (nums[0]=6):
  j=1: diff=9-6=3 > 1 ✗
  j=2: diff=6-6=0 ≤ 1 ✓ → dp[2] = 1
  j=3: diff=5-6=-1 ≤ 1 ✓ → dp[3] = 1
  j=4: diff=7-6=1 ≤ 1 ✓ → dp[4] = 1
  j=5: diff=8-6=2 > 1 ✗

From index 1 (nums[1]=9):
  j=2: diff=6-9=-3 > 1 ✗ (|-3| > 1)
  All others have differences > 1

From index 2 (nums[2]=6, dp[2]=1):
  j=3: diff=5-6=-1 ≤ 1 ✓ → dp[3] = max(1, 1+1) = 2
  j=4: diff=7-6=1 ≤ 1 ✓ → dp[4] = max(1, 1+1) = 2
  j=5: diff=8-6=2 > 1 ✗

From index 3 (nums[3]=5, dp[3]=2):
  j=4: diff=7-5=2 > 1 ✗
  j=5: diff=8-5=3 > 1 ✗

From index 4 (nums[4]=7, dp[4]=2):
  j=5: diff=8-7=1 ≤ 1 ✓ → dp[5] = max(-1, 2+1) = 3

Final dp: [0, -1, 1, 2, 2, 3]
Result: dp[5] = 3

Key Insights:
- Forward-only jumps simplify DP (no need for memoization/recursion)
- Tabulation approach builds solutions bottom-up
- Absolute difference check: |a-b| ≤ target
- -1 indicates unreachable indices
- Final answer is dp[n-1] (result at last index)

Edge Cases:
- n = 1: already at last index, return 0
- All differences > target: unreachable, return -1
- target = 0: can only jump to equal values
- Negative numbers: still works (uses absolute difference)
*/
