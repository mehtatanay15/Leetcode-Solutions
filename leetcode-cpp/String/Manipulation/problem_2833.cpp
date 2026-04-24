// LeetCode 2833: Furthest Distance From Origin
// Problem: Given a string of moves (L, R, _), find the maximum distance from origin
// Approach: Greedy - Count each move type and apply blanks to the direction with more moves

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int right = 0;
        int left = 0;
        int blank = 0;

        // Count occurrences of each move type
        for(char ch: moves){
            if(ch == 'L') left++;
            else if(ch == 'R') right++;
            else blank++;
        }

        // Greedy: apply blank moves to the direction with more moves
        if(right > left) 
        {
            right += blank;
            return right - left;
        }
        else 
        {
            left += blank;
            return left - right;
        }
    }
};

/*
Time Complexity: O(n) - single pass through the string to count
Space Complexity: O(1) - only using constant extra space

Algorithm:
1. Count occurrences of 'L', 'R', and '_' (blank) moves
2. If right count > left count:
   - Apply all blank moves to the right to maximize distance
   - Return right - left (final position)
3. Otherwise:
   - Apply all blank moves to the left to maximize distance
   - Return left - right (final distance)

Example:
- Input: "L_LL_R__R"
- L count: 3, R count: 2, Blank count: 3
- Since left > right, apply blanks to left
- Final left: 3 + 3 = 6, right: 2
- Result: 6 - 2 = 4

Key Insight:
- To maximize distance, we always want to use blank moves in the direction that has more moves
- This is because net distance = max(left_moves, right_moves)
- Blanks can be used to extend the direction with more moves
*/
