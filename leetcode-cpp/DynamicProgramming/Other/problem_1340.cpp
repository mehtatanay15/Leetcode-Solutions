// LeetCode 1340: Maximum Jumps Index Within Constraints
// Problem: Find maximum number of jumps in array where from index i you can jump to j if |i-j| <= d and arr[j] < arr[i]
// Approach: DFS with memoization - for each position, recursively explore valid jumps in both directions

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int dfs(int i, vector<int>& arr, int d, vector<int>& dp) {
        // If already computed, return memoized result
        if (dp[i] != 0) return dp[i];
        
        int max_jumps = 1;  // Current position counts as 1 jump
        int n = arr.size();
        
        // Explore jumps to the RIGHT (forward direction)
        // Can jump from i to j where i < j <= min(i + d, n - 1)
        for (int j = i + 1; j <= min(i + d, n - 1); ++j) {
            // Stop if we encounter element >= current element (can't jump)
            if (arr[j] >= arr[i]) break;
            // Recursively get max jumps from position j, add 1 for current jump
            max_jumps = max(max_jumps, 1 + dfs(j, arr, d, dp));
        }

        // Explore jumps to the LEFT (backward direction)
        // Can jump from i to j where max(i - d, 0) <= j < i
        for (int j = i - 1; j >= max(i - d, 0); --j) {
            // Stop if we encounter element >= current element (can't jump)
            if (arr[j] >= arr[i]) break;
            // Recursively get max jumps from position j, add 1 for current jump
            max_jumps = max(max_jumps, 1 + dfs(j, arr, d, dp));
        }

        // Memoize and return the maximum jumps from position i
        return dp[i] = max_jumps;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        // DP array: dp[i] = maximum jumps starting from position i
        vector<int> dp(n, 0);
        
        int ans = 0;
        
        // Try starting from each position and find maximum
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dfs(i, arr, d, dp));
        }
        
        return ans;
    }
};

/*
Time Complexity: O(n²) in worst case
  - Each of n positions visited at most once (due to memoization)
  - From each position, we explore at most 2*d neighbors
  - Total: O(n * d) where d ≤ n, so O(n²)
  - With memoization, each state computed only once

Space Complexity: O(n + recursion_depth)
  - DP array: O(n)
  - Recursion call stack: O(n) in worst case (long chain)
  - Total: O(n)

Algorithm Explanation:

Problem Overview:
Given an array arr and jump distance d, find the longest sequence of jumps where:
- From index i, can jump to index j if |i - j| <= d
- Can only jump to index j if arr[j] < arr[i] (strictly smaller)
- Goal: Find the maximum number of jumps in any sequence

Key Insight - DFS with Memoization:
- This is a longest path problem in a directed acyclic graph (DAG)
- Each element can only jump to smaller elements → no cycles
- DFS explores all possible jump sequences from each position
- Memoization stores results to avoid recomputation

Why DAG Property:
- Since arr[j] < arr[i] is required for jumps, we always move to strictly smaller values
- This guarantees no cycles (can't return to a previous position with larger value)
- Topological ordering naturally emerges from decreasing values

Memoization Strategy:
- dp[i] = maximum jumps starting from position i
- Base case: dp[i] = 1 initially (position i itself)
- Transition: dp[i] = 1 + max(dp[j]) for all valid j we can jump to
- Early return if dp[i] already computed

Two-Direction Exploration:
- Right jumps: explore positions i+1 to min(i+d, n-1)
- Left jumps: explore positions max(i-d, 0) to i-1
- Stop in each direction when arr[j] >= arr[i] (can't jump further in that direction due to ordering constraint)

Example 1: arr = [7, 6, 5, 4, 3, 2, 1], d = 1
Starting from each position:
- i=0 (7): can jump to 1 (6), then 2 (5), ..., total: 7 jumps
- i=1 (6): can jump to 0 (7)? No (7 >= 6). Jump to 2 (5), then 3 (4), ..., total: 6 jumps
- i=6 (1): can only stay, total: 1 jump
Return: 7

Trace from i=0:
- dfs(0, arr, 1, dp):
  - max_jumps = 1
  - Right: j=1, arr[1]=6 < arr[0]=7? Yes, max_jumps = max(1, 1+dfs(1,...))
    - dfs(1, arr, 1, dp):
      - max_jumps = 1
      - Right: j=2, arr[2]=5 < arr[1]=6? Yes, max_jumps = max(1, 1+dfs(2,...))
        - Continue recursively...
      - Left: j=0, arr[0]=7 >= arr[1]=6? Yes, break
      - return dp[1] = result
  - Left: j=-1 out of bounds, skip
  - return dp[0] = result

Example 2: arr = [2, 3, 1, 6, 4, 2, 3], d = 2
Valid jumps from each position (within distance d and to strictly smaller):
- From 0 (2): can jump to 2 (1) → distance 2, value 1 < 2 ✓
- From 1 (3): can jump to 2 (1) → distance 1, value 1 < 3 ✓
- From 2 (1): nowhere (no smaller values reachable)
- From 3 (6): can jump to 2 (1) → distance 1, 1 < 6 ✓
               can jump to 4 (4) → distance 1, 4 < 6 ✓
               can jump to 5 (2) → distance 2, 2 < 6 ✓
- From 4 (4): can jump to 2 (1) → distance 2, 1 < 4 ✓
               can jump to 5 (2) → distance 1, 2 < 4 ✓
- From 5 (2): can jump to 2 (1) → distance 3? No (exceeds d=2)
- From 6 (3): can jump to 5 (2) → distance 1, 2 < 3 ✓

Maximum path: 3 (6) → 4 (4) → 5 (2) → total 3 jumps
Or: 3 (6) → 2 (1) → total 2 jumps
Return: 3

Example 3: arr = [1, 3, 1, 2, 1], d = 3
Valid jumps:
- From 0 (1): nowhere (smallest element)
- From 1 (3): can jump to 0, 2, 3, 4 (all < 3 within distance 3)
- From 2 (1): nowhere
- From 3 (2): can jump to 0, 2, 4 (all < 2 within distance 3)
- From 4 (1): nowhere

Maximum from 1: jump to any smaller value
Path: 1 (3) → 0 (1) → total 2 jumps
Or: 1 (3) → 3 (2) → 4 (1) → total 3 jumps
Return: 3

Edge Cases:
1. Single element: [x] → always return 1
2. All equal: [5, 5, 5] → can't jump anywhere, return 1
3. Increasing: [1, 2, 3, 4] → can only jump from position 0, return 1
4. Decreasing: [4, 3, 2, 1] with d=1 → longest chain is 4 jumps
5. d >= n-1: can reach any element → depends on values
6. Large d: reduces to finding longest strictly decreasing subsequence

Algorithm Characteristics:

Why Not Greedy:
- Can't just pick the smallest value in range (might miss longer paths)
- Example: [3, 1, 4, 1, 2] with d=2
  - From 0 (3): could jump to 1 (1) or 3 (1)
  - From 1: nowhere (smallest), total 2 jumps from path 0→1
  - From 3: nowhere, total 2 jumps from path 0→3
  - But 0→2→4→3 requires proper exploration

Why DFS Works:
- Explores all possible paths from a position
- Memoization prevents exponential blowup
- DAG structure guarantees termination

Time Complexity Details:
- State space: n positions
- Transitions: each position explores O(d) neighbors
- Per state: O(d) work
- Total with memoization: O(n * d)
- In worst case d=n, so O(n²)

Space Complexity Details:
- DP array: O(n)
- Call stack depth: O(n) at worst (long decreasing chain)
- Total: O(n)

Optimization Notes:
- Early break when arr[j] >= arr[i] is crucial (avoids unnecessary exploration)
- Memoization is essential (without it, would be exponential)
- Starting from all positions guarantees finding global maximum
- Could optimize by sorting by value and processing in order (but DFS is simpler)

Alternative Approach (Iterative DP with Sorting):
```cpp
int maxJumps(vector<int>& arr, int d) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    // Create pairs of (value, index) and sort by value
    vector<pair<int, int>> sorted_arr;
    for (int i = 0; i < n; i++) {
        sorted_arr.push_back({arr[i], i});
    }
    sort(sorted_arr.begin(), sorted_arr.end());
    
    int ans = 1;
    
    // Process in increasing order of values
    for (auto [val, i] : sorted_arr) {
        // Check neighbors j to see if we can jump from j to i
        for (int j = max(0, i - d); j <= min(n - 1, i + d); j++) {
            if (arr[j] > arr[i]) {  // can jump from j to i
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    
    return ans;
}
```
Time: O(n log n + n*d)
Space: O(n)

Current DFS Approach Advantages:
- More intuitive to understand
- Naturally handles the constraint checking
- No need for separate sorting step
- Easier to visualize the jump sequences
*/
