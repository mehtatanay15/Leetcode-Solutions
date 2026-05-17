// LeetCode 1306: Jump Game III
// Problem: Given an array where arr[i] = jump length, determine if you can reach index 0 from start
// At each index i, you can jump forward arr[i] steps or backward arr[i] steps
// Goal: Return true if you can reach index 0 (which contains 0)
// Approach: Backtracking with recursion - try both jump directions, mark visited with -1

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        // Out of bounds check: invalid index
        if (start < 0 || start >= arr.size()) {
            return false;
        }
        
        // Already visited: prevent infinite loops (marked with -1)
        if (arr[start] < 0) {
            return false;
        }
        
        // Found target: arr[start] == 0 means we reached the goal
        if (arr[start] == 0) {
            return true;
        }
        
        // Get jump length before marking as visited
        int jump = arr[start];
        
        // Mark current position as visited (prevent revisiting)
        arr[start] = -1;
        
        // Try both directions: forward and backward
        // Forward jump: jump to start + jump
        // Backward jump: jump to start - jump
        bool canReachRight = canReach(arr, start + jump);
        bool canReachLeft = canReach(arr, start - jump);
        
        // Return true if either direction leads to index 0
        return canReachRight || canReachLeft;
    }
};

/*
Time Complexity: O(n) where n is the length of array
  - Each index visited at most once (marked with -1)
  - Recursion tree bounded by n nodes
  - Total: O(n)

Space Complexity: O(n)
  - Recursion call stack depth: O(n) in worst case
  - Array marking uses O(1) extra space

Algorithm Explanation:

Problem Overview:
Given an array arr where arr[i] represents a jump length, and a starting index.
From any index i, you can jump forward arr[i] steps to i+arr[i] or backward arr[i] steps to i-arr[i].
Goal: Reach index 0 where arr[0] = 0.

Key Insight - Backtracking Approach:
- This is a graph reachability problem disguised as an array problem
- Each index is a node, and jumps are edges
- At each index, we have 2 choices: jump forward or backward
- We need to explore all possibilities until we find index 0

Visited Marking Strategy:
- Mark visited indices with -1 to prevent infinite loops
- When arr[start] < 0, we know we've already processed this index
- This avoids revisiting the same positions infinitely

Base Cases:
1. Index out of bounds: return false (cannot reach 0)
2. Index already visited (value < 0): return false (already explored)
3. Index is 0 (arr[i] = 0): return true (found target)

Recursive Case:
- Save the jump value before marking as visited
- Recursively try jumping right: canReach(arr, start + jump)
- Recursively try jumping left: canReach(arr, start - jump)
- Return true if either path leads to index 0

Example 1: arr = [4, 2, 3, 0, 3, 1, 2], start = 5
Initial: arr[5] = 1
- Mark arr[5] = -1
- Try canReach(5+1=6, arr) and canReach(5-1=4, arr)

Right path: start=6
- arr[6] = 2
- Mark arr[6] = -1
- Try canReach(6+2=8, arr) and canReach(6-2=4, arr)
- canReach(8) → out of bounds → false

Left path: start=4
- arr[4] = 3
- Mark arr[4] = -1
- Try canReach(4+3=7, arr) and canReach(4-3=1, arr)
- canReach(7) → out of bounds → false

Continue exploring... eventually will reach index 0

Let me trace through properly:
arr = [4, 2, 3, 0, 3, 1, 2], start = 5

canReach(5):
  arr[5] = 1
  arr[5] = -1  (mark visited)
  canReach(5+1=6):
    arr[6] = 2
    arr[6] = -1
    canReach(8): out of bounds → false
    canReach(4):
      arr[4] = 3
      arr[4] = -1
      canReach(7): out of bounds → false
      canReach(1):
        arr[1] = 2
        arr[1] = -1
        canReach(3):
          arr[3] = 0 → return true ✓
        (short-circuits, returns true)
      returns true
    returns true
  returns true
  
Answer: true (reached from 5 → 6 → 4 → 1 → 3)

Example 2: arr = [0], start = 0
canReach(0):
  arr[0] = 0 → return true immediately ✓
  
Answer: true

Example 3: arr = [2, 3, 1, 1, 4], start = 3
canReach(3):
  arr[3] = 1
  arr[3] = -1
  canReach(4):
    arr[4] = 4
    arr[4] = -1
    canReach(8): out of bounds → false
    canReach(0):
      arr[0] = 2
      arr[0] = -1
      canReach(2):
        arr[2] = 1
        arr[2] = -1
        canReach(3):
          arr[3] = -1 (already visited) → false
        canReach(1):
          arr[1] = 3
          arr[1] = -1
          canReach(4): arr[4] = -1 → false
          canReach(-2): out of bounds → false
          return false
        return false
      return false
    return false
  canReach(2):
    arr[2] = 1
    arr[2] = -1
    canReach(3): arr[3] = -1 → false
    canReach(1):
      arr[1] = 3
      arr[1] = -1
      canReach(4): arr[4] = -1 → false
      canReach(-2): out of bounds → false
      return false
    return false
  return false

Answer: false (cannot reach 0)

Edge Cases:
1. Start at index 0: arr[0] = 0 → immediate true
2. Start at last index: can only jump forward (out of bounds) or backward
3. All paths lead out of bounds: return false
4. Cycles in path: prevented by -1 marking
5. Single element array [0]: return true
6. Jump value larger than array length: goes out of bounds

Optimization Notes:
- BFS approach: Could use queue instead of recursion
- DFS approach: Current recursive solution
- Space tradeoff: Recursive uses O(n) stack; iterative uses O(n) queue
- Both have same time complexity O(n)

Visited Marking Explanation:
Instead of using a separate visited set/array, we mark with -1:
- Pros: No extra space (besides recursion stack)
- Cons: Modifies input array
- If immutable array required: use separate boolean array or set

Alternative Approaches:
1. BFS with queue:
   - Time: O(n), Space: O(n)
   - Easier to understand iteratively
   
2. DFS with visited set:
   - Time: O(n), Space: O(n)
   - More idiomatic for some
   
3. Current approach (mark with -1):
   - Time: O(n), Space: O(n) for recursion stack
   - Most space-efficient for visited tracking

Why Backtracking Works Here:
- Each position has at most 2 unexplored directions
- Recursion naturally explores both branches
- Marking prevents revisiting (important for cycles)
- Early termination when arr[i] == 0
*/
