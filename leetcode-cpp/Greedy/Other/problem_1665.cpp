// LeetCode 1665: Minimum Effort to Complete All Tasks
// Problem: Given tasks with actual and minimum energy requirements
// Find minimum initial energy needed to complete all tasks in any order
// Approach: Greedy sorting - sort by (minimum - actual) difference in descending order

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Step 1: Sort tasks by energy gain/loss (minimum - actual) in descending order
        // Greedy principle: Do tasks with larger energy requirements first
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        
        int initialEnergy = 0;  // Minimum initial energy needed
        int currentEnergy = 0;  // Current energy level as we process tasks
        
        // Step 2: Process tasks in sorted order
        for (const auto& task : tasks) {
            int actual = task[0];      // Energy consumed by this task
            int minimum = task[1];     // Minimum energy needed to attempt this task
            
            // If current energy is insufficient, increase initial energy
            if (currentEnergy < minimum) {
                initialEnergy += (minimum - currentEnergy);
                currentEnergy = minimum;
            }
            
            // Execute the task: consume actual energy
            currentEnergy -= actual;
        }
        
        return initialEnergy;
    }
};

/*
Time Complexity: O(n log n) - Dominated by sorting where n = number of tasks
Space Complexity: O(1) - Only using constant extra space (sorting in-place)

Algorithm Explanation:

Key Insight - Greedy Sorting Strategy:
- Sort tasks by (minimum - actual) in descending order
- This ensures tasks requiring more energy "gain" are done first
- Minimizes the total initial energy needed

Why This Works:
- For each task, we need at least 'minimum' energy to attempt it
- After attempting, we lose 'actual' energy
- The net energy change is -(actual)
- If we do high-requirement tasks first, we accumulate energy loss slower
- This allows us to handle subsequent tasks with lower initial energy

State Variables:
- currentEnergy: Energy level as we progress through tasks
- initialEnergy: Additional energy needed to ensure we never go negative

Algorithm Steps:
1. Sort tasks by (minimum - actual) descending
2. For each task in sorted order:
   - If currentEnergy < minimum:
     * Need to increase initialEnergy by the gap
     * Set currentEnergy to minimum
   - Subtract actual energy from currentEnergy
3. Return totalInitialEnergy

Example 1:
tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]

Calculate differences: (min - actual)
- [1,3]: 3-1 = 2
- [2,4]: 4-2 = 2
- [10,11]: 11-10 = 1
- [10,12]: 12-10 = 2
- [8,9]: 9-8 = 1

Sort by difference descending: [1,3], [2,4], [10,12] (all have diff=2), then [10,11], [8,9]
Actually, multiple tasks have same difference. Let's sort all by difference descending.

Sorted by diff descending: those with diff=2 first, then diff=1
Order after sorting: [1,3], [2,4], [10,12], [10,11], [8,9]

Processing:
1. Task [1,3]: min=3, actual=1
   - currentEnergy=0, need 3 → initialEnergy += 3-0 = 3, currentEnergy = 3
   - Execute: currentEnergy = 3-1 = 2

2. Task [2,4]: min=4, actual=2
   - currentEnergy=2, need 4 → initialEnergy += 4-2 = 2 (total 5), currentEnergy = 4
   - Execute: currentEnergy = 4-2 = 2

3. Task [10,12]: min=12, actual=10
   - currentEnergy=2, need 12 → initialEnergy += 12-2 = 10 (total 15), currentEnergy = 12
   - Execute: currentEnergy = 12-10 = 2

4. Task [10,11]: min=11, actual=10
   - currentEnergy=2, need 11 → initialEnergy += 11-2 = 9 (total 24), currentEnergy = 11
   - Execute: currentEnergy = 11-10 = 1

5. Task [8,9]: min=9, actual=8
   - currentEnergy=1, need 9 → initialEnergy += 9-1 = 8 (total 32), currentEnergy = 9
   - Execute: currentEnergy = 9-8 = 1

Result: initialEnergy = 32

Example 2:
tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
Let me reconsider the sort. The comparator sorts by (a[1] - a[0]) > (b[1] - b[0])

Actually, for tasks with equal differences, the sort is stable or depends on default comparison.
Let me trace through with proper sorting:

Differences: [2, 2, 1, 2, 1]
After sorting (largest difference first): positions with diff=2 first

If we take them in order [1,3], [2,4], [10,12], then [10,11], [8,9]:

Initial: initialEnergy=0, currentEnergy=0

[1,3]: min=3, actual=1
  currentEnergy < 3 → initialEnergy += 3, currentEnergy = 3
  currentEnergy -= 1 → currentEnergy = 2

[2,4]: min=4, actual=2
  currentEnergy < 4 → initialEnergy += 2, currentEnergy = 4
  currentEnergy -= 2 → currentEnergy = 2

[10,12]: min=12, actual=10
  currentEnergy < 12 → initialEnergy += 10, currentEnergy = 12
  currentEnergy -= 10 → currentEnergy = 2

[10,11]: min=11, actual=10
  currentEnergy < 11 → initialEnergy += 9, currentEnergy = 11
  currentEnergy -= 10 → currentEnergy = 1

[8,9]: min=9, actual=8
  currentEnergy < 9 → initialEnergy += 8, currentEnergy = 9
  currentEnergy -= 8 → currentEnergy = 1

Total: initialEnergy = 3 + 2 + 10 + 9 + 8 = 32

Example 3:
tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]

A different order to show importance of sorting.
What if we don't sort and do [10,12] first?

[10,12]: min=12, actual=10
  currentEnergy < 12 → initialEnergy += 12, currentEnergy = 12
  currentEnergy -= 10 → currentEnergy = 2

[10,11]: min=11, actual=10
  currentEnergy < 11 → initialEnergy += 9, currentEnergy = 11
  currentEnergy -= 10 → currentEnergy = 1

[8,9]: min=9, actual=8
  currentEnergy < 9 → initialEnergy += 8, currentEnergy = 9
  currentEnergy -= 8 → currentEnergy = 1

[1,3]: min=3, actual=1
  currentEnergy ≥ 3 → no change
  currentEnergy -= 1 → currentEnergy = 0

[2,4]: min=4, actual=2
  currentEnergy < 4 → initialEnergy += 4, currentEnergy = 4
  currentEnergy -= 2 → currentEnergy = 2

Total: initialEnergy = 12 + 9 + 8 + 4 = 33

So sorting matters! By doing high-requirement tasks first, we save 1 unit of energy.

Simpler Example:
tasks = [[1,5],[2,3]]

Differences:
- [1,5]: 5-1 = 4
- [2,3]: 3-2 = 1

Sort by difference descending: [1,5], [2,3]

Processing:
1. [1,5]: min=5, actual=1
   currentEnergy=0 < 5 → initialEnergy = 5, currentEnergy = 5
   currentEnergy -= 1 → currentEnergy = 4

2. [2,3]: min=3, actual=2
   currentEnergy=4 ≥ 3 → no change
   currentEnergy -= 2 → currentEnergy = 2

Result: initialEnergy = 5

If we reverse order: [2,3], [1,5]

1. [2,3]: min=3, actual=2
   currentEnergy=0 < 3 → initialEnergy = 3, currentEnergy = 3
   currentEnergy -= 2 → currentEnergy = 1

2. [1,5]: min=5, actual=1
   currentEnergy=1 < 5 → initialEnergy += 4 → initialEnergy = 7, currentEnergy = 5
   currentEnergy -= 1 → currentEnergy = 4

Result: initialEnergy = 7

So the greedy order saves 2 units of energy!

Key Insights:
- Sorting by (minimum - actual) descending is the greedy choice
- This minimizes total initial energy requirement
- The intuition: complete high-effort tasks while you have energy
- Lower-effort tasks can be done with less accumulated energy

Proof Sketch (Exchange Argument):
- If two adjacent tasks i, j have diff(i) < diff(j)
- Doing j then i requires less initial energy than i then j
- Therefore, sorting by descending difference is optimal

Edge Cases:
- Single task: straightforward
- All tasks identical: order doesn't matter
- Task with actual > minimum: still works correctly
- All actual = 0: initialEnergy = sum of all minimum values
*/
