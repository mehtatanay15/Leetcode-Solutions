// LeetCode 1871: Jump Game VII
// Problem: Can we reach the last index from first index by jumping with constraints?
// We can jump from i to j if: minJump <= j-i <= maxJump and s[j] == '0'
// The destination must be reachable (dp[j] = true) and must be '0' in string
// Approach: DP with sliding window optimization - maintain count of reachable positions

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        
        // Last position must be '0' to be reachable
        if (s[n - 1] != '0') return false;
        
        // dp[i] = can we reach position i?
        vector<bool> dp(n, false);
        dp[0] = true;  // We start at position 0
        
        // Counter for number of reachable positions in current valid jump range
        int c = 0;
        
        // Process each position from left to right
        for (int i = 1; i < n; ++i) {
            // Add to counter if position (i - minJump) is reachable
            // This means from (i - minJump) we can jump to position i (distance = minJump)
            if (i >= minJump && dp[i - minJump]) {
                c++;
            }
            
            // Remove from counter if position (i - maxJump - 1) is outside our range
            // Positions beyond (i - maxJump) can't jump to i anymore (distance > maxJump)
            if (i > maxJump && dp[i - maxJump - 1]) {
                c--;
            }
            
            // We can reach position i if:
            // 1. s[i] == '0' (position is a landing pad)
            // 2. c > 0 (there's at least one reachable position within jump range)
            if (s[i] == '0' && c > 0) {
                dp[i] = true;
            }
        }
        
        return dp[n - 1];
    }
};

/*
Time Complexity: O(n) where n is the length of string
  - Single pass through the string
  - Each operation (counter updates, DP updates) is O(1)
  - No nested loops, linear traversal only

Space Complexity: O(n)
  - DP array of size n stores reachability for each position
  - Counter uses O(1) extra space

Algorithm Explanation:

Problem Overview:
Given a string s (contains only '0' and '1') and jump constraints minJump and maxJump:
- Start at index 0 (position 0)
- Goal: reach the last index n-1
- Constraint: can only land on positions with '0'
- Jump distance: must be between minJump and maxJump (inclusive)

Key Insight - Sliding Window Counter:
- Naive approach: for each position i with s[i]=='0', check all positions in range
  * This would be O(n * maxJump) - too slow
- Optimized approach: maintain a running count of reachable positions in valid range
  * As we move forward, we add positions entering the range
  * As we move forward, we remove positions leaving the range
  * This makes it O(n)

Counter Logic:
- c = count of reachable positions from which we can jump to current position i
- When processing position i:
  1. Add position (i - minJump) if it's reachable (it can now jump to i with distance minJump)
  2. Remove position (i - maxJump - 1) if it exists (it can no longer jump to i, distance too far)
  3. If s[i] == '0' and c > 0, we can reach position i

Why Sliding Window Works:
- Range of positions that can jump to i: [i - maxJump, i - minJump]
- As i increases, this range shifts right
- We only need to maintain count of reachable positions in this range
- Adding at left: i - minJump (closest reachable in range)
- Removing at left: i - maxJump - 1 (position leaving the range, now too far)

Example 1: s = "011010", minJump = 2, maxJump = 3
Positions: 0='0', 1='1', 2='1', 3='0', 4='1', 5='0'

Initial: dp = [T,F,F,F,F,F], c = 0

i=1 (s[1]='1'):
  - i >= minJump? 1 >= 2? No
  - i > maxJump? 1 > 3? No
  - s[1]=='0'? No, skip
  - dp = [T,F,F,F,F,F], c = 0

i=2 (s[2]='1'):
  - i >= minJump? 2 >= 2? Yes, dp[2-2]=dp[0]=true, c++ → c=1
  - i > maxJump? 2 > 3? No
  - s[2]=='0'? No, skip
  - dp = [T,F,F,F,F,F], c = 1

i=3 (s[3]='0'):
  - i >= minJump? 3 >= 2? Yes, dp[3-2]=dp[1]=false, no change
  - i > maxJump? 3 > 3? No
  - s[3]=='0' && c>0? Yes! dp[3] = true
  - dp = [T,F,F,T,F,F], c = 1

i=4 (s[4]='1'):
  - i >= minJump? 4 >= 2? Yes, dp[4-2]=dp[2]=false, no change
  - i > maxJump? 4 > 3? Yes, dp[4-3-1]=dp[0]=true, c-- → c=0
  - s[4]=='0'? No, skip
  - dp = [T,F,F,T,F,F], c = 0

i=5 (s[5]='0'):
  - i >= minJump? 5 >= 2? Yes, dp[5-2]=dp[3]=true, c++ → c=1
  - i > maxJump? 5 > 3? Yes, dp[5-3-1]=dp[1]=false, no change
  - s[5]=='0' && c>0? Yes! dp[5] = true
  - dp = [T,F,F,T,F,T], c = 1

Return dp[5] = true ✓

Why return true: we can reach position 5 via path: 0 → 3 → 5
- Jump from 0 to 3: distance = 3, 2 <= 3 <= 3 ✓
- Jump from 3 to 5: distance = 2, 2 <= 2 <= 3 ✓

Example 2: s = "01101110", minJump = 3, maxJump = 9
Positions: 0='0', 1='1', 2='1', 3='0', 4='1', 5='1', 6='1', 7='0'

Initial: dp = [T,F,F,F,F,F,F,F], c = 0

i=1 (s[1]='1'):
  - 1 >= 3? No
  - s[1]=='0'? No
  - c = 0

i=2 (s[2]='1'):
  - 2 >= 3? No
  - s[2]=='0'? No
  - c = 0

i=3 (s[3]='0'):
  - 3 >= 3? Yes, dp[0]=true, c++ → c=1
  - 3 > 9? No
  - s[3]=='0' && c>0? Yes! dp[3]=true
  - c = 1

i=4 (s[4]='1'):
  - 4 >= 3? Yes, dp[1]=false, no change
  - 4 > 9? No
  - s[4]=='0'? No
  - c = 1

i=5 (s[5]='1'):
  - 5 >= 3? Yes, dp[2]=false, no change
  - 5 > 9? No
  - s[5]=='0'? No
  - c = 1

i=6 (s[6]='1'):
  - 6 >= 3? Yes, dp[3]=true, c++ → c=2
  - 6 > 9? No
  - s[6]=='0'? No
  - c = 2

i=7 (s[7]='0'):
  - 7 >= 3? Yes, dp[4]=false, no change
  - 7 > 9? No
  - s[7]=='0' && c>0? Yes! dp[7]=true
  - c = 2

Return dp[7] = true ✓

Why return true: we can reach position 7 via path: 0 → 3 → 7
- Jump from 0 to 3: distance = 3 ✓
- Jump from 3 to 7: distance = 4, 3 <= 4 <= 9 ✓

Example 3: s = "0110", minJump = 1, maxJump = 2
Positions: 0='0', 1='1', 2='1', 3='0'

Initial: dp = [T,F,F,F], c = 0

i=1 (s[1]='1'):
  - 1 >= 1? Yes, dp[0]=true, c++ → c=1
  - 1 > 2? No
  - s[1]=='0'? No
  - c = 1

i=2 (s[2]='1'):
  - 2 >= 1? Yes, dp[1]=false, no change
  - 2 > 2? No
  - s[2]=='0'? No
  - c = 1

i=3 (s[3]='0'):
  - 3 >= 1? Yes, dp[2]=false, no change
  - 3 > 2? Yes, dp[0]=true, c-- → c=0
  - s[3]=='0' && c>0? No (c=0)
  - dp[3] stays false
  - c = 0

Return dp[3] = false ✓

Why return false: can't reach position 3
- From 0: can jump to 1 (dist 1) or 2 (dist 2), but both are '1'
- Can't reach any '0' except position 0 itself

Edge Cases:
1. s[n-1] != '0': impossible to reach → return false immediately
2. minJump > n-1: can't reach last position → impossible
3. maxJump < 1: can't make any jumps → only possible if n == 1
4. n == 1: already at destination → return s[0]=='0' (should be true)
5. All '1's except endpoints: might be unreachable

Algorithm Characteristics:

Why Sliding Window is Optimal:
- Naive nested loop: O(n * maxJump) - too slow for large maxJump
- Sliding window: O(n) - maintains count as window moves
- Key insight: we don't need exact positions, just count in range

Counter Maintenance:
- Counter c always represents: count of reachable positions in [i-maxJump, i-minJump]
- As we move from i to i+1:
  - New window: [(i+1)-maxJump, (i+1)-minJump] = [i+1-maxJump, i+1-minJump]
  - Old window: [i-maxJump, i-minJump]
  - Difference: add (i+1)-minJump, remove i-maxJump
  - Which is: add (i+1)-minJump if in range, remove (i+1)-maxJump-1 if was in old window

Why This Order:
- We add before checking/removing to avoid off-by-one errors
- When i = 1 and minJump = 2: (i >= minJump) is false, so nothing added yet
- When i = 2 and minJump = 2: add position 0 (can jump distance 2)

Time Complexity Justification:
- While maxJump could be large, we never iterate through all reachable positions
- We just maintain a counter that updates in O(1)
- Overall: single pass = O(n)

Space Complexity:
- DP array is necessary (need to track reachability)
- No other major data structures
- O(n) space is optimal for this problem
*/
