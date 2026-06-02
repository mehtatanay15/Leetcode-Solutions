// LeetCode 3633: Earliest Finish Time With Two Schedules
// Problem: Find minimum finish time doing land and water tasks in either order
// Two options: land first then water, or water first then land
// Approach: Brute force - try all combinations and track minimum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, 
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        int minFinishTime = INT_MAX;
        
        // Try all combinations of land and water tasks
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // Option A: Do land task first, then water task
                int landFinishA = landStartTime[i] + landDuration[i];
                int waterStartA = max(landFinishA, waterStartTime[j]);
                int finishTimeA = waterStartA + waterDuration[j];
                
                // Option B: Do water task first, then land task
                int waterFinishB = waterStartTime[j] + waterDuration[j];
                int landStartB = max(waterFinishB, landStartTime[i]);
                int finishTimeB = landStartB + landDuration[i];
                
                // Track minimum finish time across both options
                minFinishTime = min({minFinishTime, finishTimeA, finishTimeB});
            }
        }
        
        return minFinishTime;
    }
};

/*
Time Complexity: O(n * m) where:
  - n = number of land tasks
  - m = number of water tasks
  - Double loop tries all combinations of land and water tasks
  - Each combination: O(1) calculations
  - Total: O(n * m)

Space Complexity: O(1)
  - Only using constant extra variables
  - No additional data structures
  - Input arrays not modified

Algorithm Explanation:

Problem Overview:
Given:
- n land tasks with start times and durations
- m water tasks with start times and durations
- Must do exactly one land task and one water task
- Can do them in any order

Goal: Find minimum total time to complete one land and one water task

Key Insight - Two Orderings:
For each combination of land task i and water task j:
1. Option A: Land first, then water
   - Land: starts at landStartTime[i], duration landDuration[i]
   - Land finishes at: landStartTime[i] + landDuration[i]
   - Water: can start at max(landFinish, waterStartTime[j])
   - Water finishes at: waterStart + waterDuration[j]

2. Option B: Water first, then land
   - Water: starts at waterStartTime[j], duration waterDuration[j]
   - Water finishes at: waterStartTime[j] + waterDuration[j]
   - Land: can start at max(waterFinish, landStartTime[i])
   - Land finishes at: landStart + landDuration[i]

Why Both Orderings Matter:
- Sometimes land first is better (water task can start immediately)
- Sometimes water first is better (land task already finished)
- Must try both to find optimal

Constraint on Start Times:
- landStartTime[i]: earliest you can start land task i
- waterStartTime[j]: earliest you can start water task j
- Can't start a task before its designated start time
- But task can start later if previous task hasn't finished

Example 1: landStartTime=[0], landDuration=[1], 
           waterStartTime=[1], waterDuration=[1]

Combination (i=0, j=0):

Option A (Land first, then water):
- Land finishes at: 0 + 1 = 1
- Water can start at: max(1, 1) = 1
- Water finishes at: 1 + 1 = 2
- finishTimeA = 2

Option B (Water first, then land):
- Water finishes at: 1 + 1 = 2
- Land can start at: max(2, 0) = 2
- Land finishes at: 2 + 1 = 3
- finishTimeB = 3

minFinishTime = min(2, 3) = 2 ✓

Why Option A is better: Water task's earliest start matches land finish,
so no waiting. Option B requires waiting for land to start.

Example 2: landStartTime=[0], landDuration=[2],
           waterStartTime=[0], waterDuration=[1]

Combination (i=0, j=0):

Option A (Land first, then water):
- Land finishes at: 0 + 2 = 2
- Water can start at: max(2, 0) = 2
- Water finishes at: 2 + 1 = 3
- finishTimeA = 3

Option B (Water first, then land):
- Water finishes at: 0 + 1 = 1
- Land can start at: max(1, 0) = 1
- Land finishes at: 1 + 2 = 3
- finishTimeB = 3

minFinishTime = min(3, 3) = 3

Both orderings give same result because both must wait for one task.
The 1-unit task finishes first, then the 2-unit task takes 2 more.

Example 3: landStartTime=[1], landDuration=[5],
           waterStartTime=[2], waterDuration=[3]

Combination (i=0, j=0):

Option A (Land first, then water):
- Land finishes at: 1 + 5 = 6
- Water can start at: max(6, 2) = 6
- Water finishes at: 6 + 3 = 9
- finishTimeA = 9

Option B (Water first, then land):
- Water finishes at: 2 + 3 = 5
- Land can start at: max(5, 1) = 5
- Land finishes at: 5 + 5 = 10
- finishTimeB = 10

minFinishTime = min(9, 10) = 9 ✓

Land first is better: water finishes first naturally.

Example 4: landStartTime=[0, 10], landDuration=[5, 2],
           waterStartTime=[0, 5], waterDuration=[3, 1]

We try all 4 combinations:

Combo (i=0, j=0):
- Option A: land 0→5, water 5→8, finish=8
- Option B: water 0→3, land 3→8, finish=8

Combo (i=0, j=1):
- Option A: land 0→5, water 5→6, finish=6
- Option B: water 5→6, land 6→11, finish=11

Combo (i=1, j=0):
- Option A: land 10→12, water 12→15, finish=15
- Option B: water 0→3, land 10→12, finish=12

Combo (i=1, j=1):
- Option A: land 10→12, water 12→13, finish=13
- Option B: water 5→6, land 10→12, finish=12

minFinishTime = min(8, 8, 6, 11, 15, 12, 13, 12) = 6 ✓

Best choice: land task 0, water task 1, land first order.

Example 5: landStartTime=[5], landDuration=[10],
           waterStartTime=[0], waterDuration=[15]

Combination (i=0, j=0):

Option A (Land first, then water):
- Land finishes at: 5 + 10 = 15
- Water can start at: max(15, 0) = 15
- Water finishes at: 15 + 15 = 30
- finishTimeA = 30

Option B (Water first, then land):
- Water finishes at: 0 + 15 = 15
- Land can start at: max(15, 5) = 15
- Land finishes at: 15 + 10 = 25
- finishTimeB = 25

minFinishTime = min(30, 25) = 25

Water first is better because water task duration is longer,
so getting it started first uses that time more efficiently.

Example 6: landStartTime=[0], landDuration=[1],
           waterStartTime=[10], waterDuration=[1]

Combination (i=0, j=0):

Option A (Land first, then water):
- Land finishes at: 0 + 1 = 1
- Water can start at: max(1, 10) = 10
- Water finishes at: 10 + 1 = 11
- finishTimeA = 11

Option B (Water first, then land):
- Water finishes at: 10 + 1 = 11
- Land can start at: max(11, 0) = 11
- Land finishes at: 11 + 1 = 12
- finishTimeB = 12

minFinishTime = min(11, 12) = 11

Land first is better despite water's later start time.
The wait for water's start time is unavoidable anyway.

Edge Cases Handled:

1. Single task for each (n=1, m=1):
   - Try one combination with both orderings
   - Returns minimum of the two

2. Early start times:
   - landStartTime and waterStartTime can be 0
   - Code handles this correctly

3. Large durations:
   - Finish time could exceed INT_MAX if sum is too large
   - Assuming valid test cases

4. All tasks with same start time:
   - Ordering determines which finishes first
   - Both orderings must be tried

5. Water task much later than land:
   - Land task done by the time water can start
   - No overlap, finish time = landStart + landDuration + waterDuration

Algorithm Correctness:

Key observations:
1. Must choose exactly one land and one water task
2. Can perform them in any order
3. Can't start a task before its designated start time
4. Finish time determined by order and start/duration constraints

The algorithm:
- Exhaustively tries all n*m combinations
- For each combination, tries both orderings
- Tracks the minimum across all 2*n*m possibilities
- Returns the overall minimum

Why exhaustive search works:
- Small constraints (n and m likely ≤ 100)
- O(n*m) is acceptable (10,000 operations max)
- Simple logic, no complex optimizations needed

Could Greedy Work?
Attempt 1: Always pick shortest tasks
- Counter-example: landStart=0,landDur=100, waterStart=0,waterDur=1
- Shortest: land=1 (duration 1... wait, that's not in this case)
- Actually all durations given, can't choose arbitrarily
- So greedy on task choice doesn't apply

Attempt 2: Always land first
- Counter-example shown in Example 5
- Water first sometimes better
- So no fixed order is optimal

Attempt 3: Greedy on start times
- Doesn't account for durations
- Suboptimal (Example 3)

Therefore: Exhaustive search is necessary

Why Not Dynamic Programming?
- State space would be: (land_index, water_index, order)
- That's still O(n*m*2) = O(n*m)
- Same complexity as exhaustive search
- Exhaustive is simpler

Why Not Heuristic/Pruning?
- Could try some pruning strategies
- But with n*m ≤ 10,000, not necessary
- Exhaustive search already efficient enough

Optimization Opportunities (if needed):

1. Early termination:
```cpp
if (minFinishTime < some_threshold) return minFinishTime;
```
- If threshold available, could terminate early
- Not applicable here

2. Preprocessing:
```cpp
// Find minimum land duration, minimum water duration
// Could help with pruning (theoretical lower bound)
```
- Adds complexity without significant benefit

3. Ordering of iterations:
- Could iterate in order of durations
- Might find good solutions quickly
- But must still try all for correctness

For this problem: exhaustive search is optimal.

Common Mistakes to Avoid:

1. Using max(start_time, previous_finish):
   - Correct: must wait for both previous task to finish AND designated start time
   - Wrong: using only one of these

2. Forgetting to try both orderings:
   - Must try land first AND water first
   - Single ordering is suboptimal

3. Not using INT_MAX initialization:
   - min comparison needs initial value
   - INT_MAX is standard for this

4. Integer overflow:
   - Assuming reasonable input constraints
   - landStartTime + landDuration + waterDuration unlikely to overflow int

5. Off-by-one in loop bounds:
   - i < n and j < m are correct
   - 0-indexed arrays

6. Modifying input arrays:
   - Code doesn't modify, correct approach

Complexity Analysis:

Time: O(n * m)
- n land tasks, m water tasks
- Try all combinations: n*m
- For each: O(1) calculations
- Total: O(n*m)

For typical constraints (n, m ≤ 100):
- 10,000 operations
- Completes in < 1ms

Space: O(1)
- Only variables: n, m, minFinishTime, loop variables
- No dynamic allocation

Alternative Approaches Comparison:

Approach 1: Exhaustive Search (Current)
- Time: O(n*m)
- Space: O(1)
- Clarity: Very clear
- Status: ✓ Optimal

Approach 2: DP with Memoization
- Time: O(n*m)
- Space: O(n*m) for memo table
- Clarity: More complex
- Status: Overcomplicated

Approach 3: Greedy with Heuristics
- Time: O(n*m log n + n*m log m) if sorting
- Space: O(n + m) for sorted arrays
- Clarity: Medium
- Status: ✗ Incorrect (no optimal greedy property)

Current exhaustive search is best choice.

Why This Problem Matters:

1. Teaches scheduling optimization
2. Shows importance of trying all cases
3. Demonstrates constraint satisfaction
4. Real-world application: task scheduling
5. Illustrates when exhaustive search is viable

When to Use This Approach:

1. Small constraint space (< 100,000 combinations)
2. No optimal substructure for DP
3. No greedy property
4. Simple and correct solution is best

Real-world Applications:

1. Manufacturing: land and water production lines
2. Task scheduling: interleaving work streams
3. Resource allocation: two-phase processes
4. Time optimization: finding best completion time

Variants:

1. Three or more task types:
```cpp
// Nested loops for each task type
// Factorial ordering permutations
// Much more complex
```

2. Multiple land/water tasks (choose subset):
```cpp
// NP-hard problem (knapsack-like)
// Requires DP or branch-and-bound
```

3. Preemption allowed:
```cpp
// Can pause and resume tasks
// Different algorithm entirely
```

4. With dependencies:
```cpp
// Some tasks must complete before others
// Requires topological sort + scheduling
```

Learning Points:

1. When exhaustive search is appropriate
2. Constraint satisfaction importance
3. Handling multiple task orderings
4. Time calculation with start constraints
5. min() function with initializer list
6. When greedy fails
7. Real-world optimization problems
8. Trade-offs: simplicity vs optimization

This problem teaches:
- Core scheduling concepts
- Constraint handling
- Importance of trying alternatives
- Simple solution beats complex one
- Real-world optimization

Final Notes:

This is a good problem because:
- Clear problem statement
- Simple but non-obvious solution
- Illustrates scheduling complexity
- Shows when exhaustive is viable
- Interview-friendly difficulty

The key insight:
- Both task orderings matter
- Must try all combinations
- Pick minimum finish time
- No shortcuts with current constraints

This problem would become harder with:
- More task types
- Task dependencies
- Resource constraints
- Larger input sizes

But for current constraints, exhaustive search is perfect.
*/
