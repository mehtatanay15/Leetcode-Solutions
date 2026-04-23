// LeetCode 70: Climbing Stairs
// Problem: Climb n stairs, can take 1 or 2 steps at a time. How many ways?
// Approach: Dynamic Programming (Space-Optimized - using two variables)

class Solution {
public:
    int climbStairs(int n) {
        // Base cases
        if(n <= 2) return n;

        // Use two variables instead of array
        // f represents dp[i-2], s represents dp[i-1]
        int f = 1;  // Ways to climb 1 stair (1)
        int s = 2;  // Ways to climb 2 stairs (1+1 or 2)

        // For each stair from 3 to n
        for(int i = 3; i <= n; i++) {
            // To reach stair i: come from (i-1) or (i-2)
            // dp[i] = dp[i-1] + dp[i-2]
            int c = f + s;
            f = s;      // f becomes previous s (dp[i-2])
            s = c;      // s becomes current (dp[i])
        }
        
        return s;
    }
};

/*
Time Complexity: O(n)
- Single loop from 3 to n
- Each iteration: O(1) operations

Space Complexity: O(1)
- Only using two variables (f, s)
- Space-optimized version (no array needed)

Algorithm (DP with Space Optimization):
1. Base cases:
   - n = 1: 1 way (1)
   - n = 2: 2 ways (1+1 or 2)
2. For each stair from 3 to n:
   - Total ways to reach stair i = ways to reach (i-1) + ways to reach (i-2)
   - This is because from stair (i-1) we take 1 step, from (i-2) we take 2 steps
   - Update variables for next iteration

Why This is DP:
- Overlapping subproblems: ways to reach n depends on ways to reach n-1 and n-2
- Optimal substructure: solution uses optimal solutions of smaller problems
- Classic example of DP

Mathematical Pattern:
- This is the Fibonacci sequence!
- F(1) = 1
- F(2) = 2
- F(3) = 3
- F(4) = 5
- F(5) = 8
- Pattern: F(n) = F(n-1) + F(n-2)

Example 1:\nInput: n = 2\nWays to reach stair 2:\n1. 1 step + 1 step → [1, 1]\n2. 2 steps → [2]\nTotal: 2 ways\n\nOutput: 2\n\nExample 2:\nInput: n = 3\nWays to reach stair 3:\n1. 1+1+1 → [1,1,1]\n2. 1+2   → [1,2]\n3. 2+1   → [2,1]\nTotal: 3 ways\n\nOutput: 3\n\nExample 3:\nInput: n = 4\nWays to reach stair 4:\n1. 1+1+1+1\n2. 1+1+2\n3. 1+2+1\n4. 2+1+1\n5. 2+2\nTotal: 5 ways\n\nOutput: 5\n\nSteps for n=4:\nInitial: f=1, s=2\n\ni=3:\n- c = 1+2 = 3\n- f = 2, s = 3\n- dp[3] = 3\n\ni=4:\n- c = 2+3 = 5\n- f = 3, s = 5\n- dp[4] = 5\n\nReturn: 5\n\nEdge Cases:\n- n = 1: return 1\n- n = 2: return 2\n- Large n: may overflow int, consider using long\n\nVariable Tracking:\n- f (first): represents dp[i-2]\n- s (second): represents dp[i-1]\n- c (current): represents dp[i]\n\nAlternative Approaches:\n- DP with array (O(n) space): store all values\n- Recursive with memoization (O(n) time, O(n) space): top-down DP\n- Math formula (O(1) time, O(1) space): using Fibonacci formula\n\nWhy Space Optimization Works:\n- To compute dp[i], we only need dp[i-1] and dp[i-2]\n- We don't need to store all previous values\n- Just keep two variables and update them as we go\n- Reduces space from O(n) to O(1)\n*/