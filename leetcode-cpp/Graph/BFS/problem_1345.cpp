// LeetCode 1345: Jump Game IV
// Problem: Minimum jumps to reach last index where you can jump to adjacent indices or same value indices
// At each index i, you can jump to i-1, i+1, or any index j where arr[j] == arr[i]
// Goal: Find minimum number of jumps to reach index n-1
// Approach: BFS with HashMap optimization - group indices by value for O(n) complexity

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        
        // Edge case: already at or near end
        if (n <= 1) return 0;

        // Create a mapping from value to all indices where that value appears
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; ++i) {
            valueToIndices[arr[i]].push_back(i);
        }

        // BFS setup
        queue<int> q;
        vector<bool> visited(n, false);

        // Start BFS from index 0
        q.push(0);
        visited[0] = true;
        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            
            // Process all nodes at current distance level
            for (int i = 0; i < size; ++i) {
                int curr = q.front();
                q.pop();

                // Found target: reached last index
                if (curr == n - 1) {
                    return steps;
                }

                // Jump to adjacent index (right)
                if (curr + 1 < n && !visited[curr + 1]) {
                    visited[curr + 1] = true;
                    q.push(curr + 1);
                }

                // Jump to adjacent index (left)
                if (curr - 1 >= 0 && !visited[curr - 1]) {
                    visited[curr - 1] = true;
                    q.push(curr - 1);
                }

                // Jump to any index with the same value
                if (valueToIndices.count(arr[curr])) {
                    for (int nextIdx : valueToIndices[arr[curr]]) {
                        if (!visited[nextIdx]) {
                            visited[nextIdx] = true;
                            q.push(nextIdx);
                        }
                    }

                    // Optimization: Remove this value from map to avoid reprocessing
                    // After visiting all indices with arr[curr], we don't need this entry
                    valueToIndices.erase(arr[curr]);
                }
            }
            
            steps++;
        }

        return -1; // Should never reach here if array has at least 1 element
    }
};

/*
Time Complexity: O(n) where n is the array length
  - Each index visited at most once: O(n)
  - HashMap operations: O(n) total
  - Mapping creation: O(n)
  - Erasing value from map: O(1) amortized per unique value
  - Total: O(n)

Space Complexity: O(n)
  - Queue: O(n) in worst case
  - Visited array: O(n)
  - HashMap: O(n) to store all indices

Algorithm Explanation:

Problem Overview:
Given an array arr, at index i you can:
1. Jump to i + 1
2. Jump to i - 1
3. Jump to any index j where arr[j] == arr[i]

Goal: Find minimum number of jumps to reach index n-1 (last index).
Each jump counts as 1 step.

BFS Approach:
- BFS finds shortest path in unweighted graphs
- Here, each jump = 1 edge in graph
- Nodes = array indices
- Edges = valid jumps (adjacent indices or same value indices)

Key Insight - HashMap Optimization:
Without optimization: From each index, we might check ALL indices with same value
With optimization: Group indices by value, then erase after processing
This ensures each index is added to queue at most once, and each comparison happens O(1) times

Why Erase After Processing:
When we process an index i with value v:
- We add all unvisited indices with value v to queue
- We mark them as visited
- We erase the mapping for value v from HashMap
- Future indices with value v won't try to add these already-visited indices again
- This is the key to achieving O(n) time complexity

Example 1: arr = [100, -23, -23, 404, 100, 23, 23, 23, 3, 404]
Goal: reach index 9

Initial BFS:
- Queue: [0], visited: [0]
- valueToIndices: {100: [0,4], -23: [1,2], 404: [3,9], 23: [5,6,7], 3: [8]}

Step 1: Process index 0
- Adjacent: index 1 (not visited) → add to queue
- Same value (100): indices [0,4]
  * Index 0: already visited
  * Index 4: not visited → add to queue
- Erase value 100 from map
- Queue: [1, 4], visited: [0,1,4], steps = 1

Step 2: Process index 1
- Adjacent: index 0 (visited), index 2 (not visited)
  * Index 2: not visited → add to queue
- Same value (-23): indices [1,2]
  * Index 1: already visited
  * Index 2: just marked visited → already in queue
- Erase value -23
- Queue: [4, 2], visited: [0,1,4,2], steps = 1

Continue until we reach index 9...
Eventually, we'll reach the last index with minimum steps

Example 2: arr = [7]
n = 1 → return 0 immediately (already at last index)

Example 3: arr = [7, 6, 9, 6, 9, 6, 9, 7]
Multiple paths with value 6 (indices 1,3,5) and value 9 (indices 2,4,6)
BFS finds optimal path by exploring level by level

Step-by-step:
Level 0: Start at index 0
Level 1: Can reach indices 1 and other indices with value 7
Level 2: From reachable indices, can reach new indices with 1 jump
...continue until reaching index 7

Edge Cases:
1. Single element: arr = [x] → return 0
2. All same values: arr = [1,1,1,1,1] → can jump from 0→1→2→...→n-1 in n-1 jumps
3. All different values: arr = [1,2,3,4,5] → can only use adjacent jumps
4. Large values: Same logic, just different jump distances
5. Negative values: Algorithm handles negative values same way

Complexity Analysis Detailed:

Time: Why O(n)?
- Each of n indices added to queue at most once
- Each index dequeued at most once
- For each index, we check:
  * Adjacent indices (2 checks): O(1)
  * Same value indices in map: O(k) where k = count of same values
  * But after processing, we erase the value entry
  * Total iterations over all same-value indices: O(n) for entire algorithm
- HashMap operations: count, access, erase are O(1) average
- Total: O(n) iterations + O(n) same-value iterations = O(n)

Space: Why O(n)?
- Queue stores at most all n indices
- Visited array stores n booleans
- HashMap stores references to all n indices
- Total: O(n)

Alternative Approaches:

1. BFS without HashMap optimization:
   - Time: O(n²) in worst case
   - Space: O(n)
   - Simpler code but slower

2. DFS Backtracking:
   - Time: O(n²) in worst case
   - Space: O(n) recursion stack
   - Less efficient than BFS

3. Dijkstra's Algorithm:
   - Time: O(n log n) with priority queue
   - Space: O(n)
   - Overkill since all edges have weight 1

Why BFS is Optimal:
- When all edges have equal weight (weight = 1), BFS finds shortest path
- No need for Dijkstra's more complex logic
- HashMap optimization brings it to O(n) time
- Simple and efficient solution

Problem Comparison:
| Problem | Jumps | Values | Complexity |
|---------|-------|--------|------------|
| 1306    | arr[i]| -      | O(n)       |
| 1345    | adj+val| +     | O(n)       |
| 45      | max   | -      | O(n)       |
| 55      | reachable| -   | O(n)       |

The HashMap optimization is crucial here because without it,
checking all indices with same value repeatedly would be O(n²).
By erasing, we ensure each value comparison happens at most once total.
*/
