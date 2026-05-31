// LeetCode 2126: Destroying Asteroids With Planet
// Problem: Determine if a planet can destroy all asteroids given initial mass
// The planet destroys asteroid if mass >= asteroid mass, then absorbs it
// Approach: Greedy - sort asteroids ascending, destroy smallest first

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        // Use long long to prevent integer overflow as planet gains mass
        long long currentMass = mass;
        
        // Sort in ascending order so we tackle smallest asteroids first
        sort(asteroids.begin(), asteroids.end());
        
        // Iterate through each asteroid
        for (int i = 0; i < asteroids.size(); i++) {
            if (currentMass >= asteroids[i]) {
                // Planet is big enough to destroy and absorb the asteroid
                currentMass += asteroids[i];
            } else {
                // Planet is too small and gets destroyed
                return false;
            }
        }
        
        // If we make it through the whole loop, all asteroids were destroyed
        return true;
    }
};

/*
Time Complexity: O(n log n) where:
  - n = number of asteroids
  - Sorting: O(n log n)
  - Iteration through sorted asteroids: O(n)
  - Total: O(n log n) dominated by sorting

Space Complexity: O(1)
  - Sorting is done in-place (quicksort/introsort)
  - Only using constant extra variables (currentMass)
  - No additional data structures

Algorithm Explanation:

Problem Overview:
Given:
- Planet with initial mass
- Array of asteroids with different masses
- Planet can destroy asteroid if mass >= asteroid mass
- Planet absorbs destroyed asteroid (mass increases)

Goal: Determine if planet can destroy all asteroids

Key Insight - Greedy Strategy:
Destroy asteroids in order of increasing mass (smallest first)
Why? Because:
1. Destroying small asteroid first gains less mass but is always safe if possible
2. If we can't destroy a small asteroid, we can't destroy a larger one either
3. Gaining mass from small asteroids helps destroy larger ones later
4. No benefit to attempting large asteroids first

Example: mass=10, asteroids=[3, 9, 19, 8]
- Sorted: [3, 8, 9, 19]
- Start: mass=10
- Destroy 3: 10 >= 3 ✓ → mass=13
- Destroy 8: 13 >= 8 ✓ → mass=21
- Destroy 9: 21 >= 9 ✓ → mass=30
- Destroy 19: 30 >= 19 ✓ → mass=49
- Result: true (all destroyed) ✓

Why Not Try Large First? mass=10, asteroids=[3, 9, 19, 8]
- If we try [19, 9, 8, 3] order:
- mass=10, 10 >= 19? No → fail immediately
- But we can succeed with different order!
- Greedy ascending order is optimal ✓

Proof of Correctness (Exchange Argument):

Suppose optimal solution destroys asteroids in order A1, A2, ..., An
where A1 <= A2 <= ... <= An (sorted)

If A1 > A2 (not sorted):
- At step 1: mass >= A1, so mass >= A2 also
- At step 2: current mass is (old mass + A1), still >= A2 since A1 >= A2
- So destroying in any order works if destructible in sorted order
- Conversely, if destructible in sorted order, any permutation works
- BUT: If we can't destroy in sorted order, we can't destroy at all
- Because if mass < A[i] in sorted array:
  - Destroying all smaller elements first gives max possible mass
  - If that's not enough, no ordering helps

Integer Overflow Consideration:
- Initial mass: int (up to 2^31-1 ≈ 2*10^9)
- Asteroid masses: int (up to 2*10^9)
- Sum could exceed 2^31-1
- Using long long prevents overflow
- Could have up to 10^5 asteroids * 10^9 mass each = 10^14 > int max
- long long: up to 2^63-1 ≈ 9*10^18 (sufficient)

Example 1: mass=10, asteroids=[3, 9, 19, 8]

Step-by-step execution:
Initial: currentMass=10, asteroids=[3, 9, 19, 8]

After sort: asteroids=[3, 8, 9, 19]

i=0, asteroid=3:
- currentMass(10) >= asteroids[0](3)? Yes
- currentMass = 10 + 3 = 13

i=1, asteroid=8:
- currentMass(13) >= asteroids[1](8)? Yes
- currentMass = 13 + 8 = 21

i=2, asteroid=9:
- currentMass(21) >= asteroids[2](9)? Yes
- currentMass = 21 + 9 = 30

i=3, asteroid=19:
- currentMass(30) >= asteroids[3](19)? Yes
- currentMass = 30 + 19 = 49

Loop ends, return true ✓

Example 2: mass=5, asteroids=[3, 4, 5]

Initial: currentMass=5, asteroids=[3, 4, 5]

After sort: asteroids=[3, 4, 5]

i=0, asteroid=3:
- currentMass(5) >= asteroids[0](3)? Yes
- currentMass = 5 + 3 = 8

i=1, asteroid=4:
- currentMass(8) >= asteroids[1](4)? Yes
- currentMass = 8 + 4 = 12

i=2, asteroid=5:
- currentMass(12) >= asteroids[2](5)? Yes
- currentMass = 12 + 5 = 17

Loop ends, return true ✓

Example 3: mass=3, asteroids=[6, 2, 4]

Initial: currentMass=3, asteroids=[6, 2, 4]

After sort: asteroids=[2, 4, 6]

i=0, asteroid=2:
- currentMass(3) >= asteroids[0](2)? Yes
- currentMass = 3 + 2 = 5

i=1, asteroid=4:
- currentMass(5) >= asteroids[1](4)? Yes
- currentMass = 5 + 4 = 9

i=2, asteroid=6:
- currentMass(9) >= asteroids[2](6)? Yes
- currentMass = 9 + 6 = 15

Loop ends, return true ✓

Example 4: mass=1, asteroids=[2, 3, 4]

Initial: currentMass=1, asteroids=[2, 3, 4]

After sort: asteroids=[2, 3, 4]

i=0, asteroid=2:
- currentMass(1) >= asteroids[0](2)? No (1 < 2)
- Return false ✓

Even though only first asteroid matters, result is false

Example 5: mass=1000, asteroids=[1]

Initial: currentMass=1000, asteroids=[1]

After sort: asteroids=[1]

i=0, asteroid=1:
- currentMass(1000) >= asteroids[0](1)? Yes
- currentMass = 1000 + 1 = 1001

Loop ends, return true ✓

Example 6: mass=54, asteroids=[29, 83, 58, 98, 40, 37, 77, 10, 42, 7, 52, 23, 80, 86, 77]

Initial: currentMass=54

After sort: [7, 10, 23, 29, 37, 40, 42, 52, 58, 77, 77, 80, 83, 86, 98]

Processing:
- 54 >= 7? Yes, mass=61
- 61 >= 10? Yes, mass=71
- 71 >= 23? Yes, mass=94
- 94 >= 29? Yes, mass=123
- 123 >= 37? Yes, mass=160
- 160 >= 40? Yes, mass=200
- 200 >= 42? Yes, mass=242
- 242 >= 52? Yes, mass=294
- 294 >= 58? Yes, mass=352
- 352 >= 77? Yes, mass=429
- 429 >= 77? Yes, mass=506
- 506 >= 80? Yes, mass=586
- 586 >= 83? Yes, mass=669
- 669 >= 86? Yes, mass=755
- 755 >= 98? Yes, mass=853

Return true (exponential growth) ✓

Edge Cases Handled:

1. Empty array (no asteroids):
   - For loop doesn't execute
   - Return true ✓

2. Single asteroid equal to mass:
   - mass >= asteroid? Yes
   - Destroy and absorb
   - Return true ✓

3. Single asteroid greater than mass:
   - mass >= asteroid? No
   - Return false ✓

4. All asteroids small relative to mass:
   - All destroyed easily
   - Return true ✓

5. Very large mass growth:
   - long long handles cumulative sum
   - No overflow ✓

6. Maximum values (all 2*10^9):
   - mass = 2*10^9
   - 10^5 asteroids of 2*10^9 each
   - Sum ≈ 2*10^14
   - long long (≈ 9*10^18) sufficient ✓

Algorithm Correctness Proof:

Lemma: If we can destroy all asteroids in sorted order, no other order works better.

Proof by contradiction:
- Suppose sorted order succeeds but we fail in some other order
- Let's say we fail when encountering asteroid A at some position
- Before A, we destroyed asteroids totaling sum S
- Our current mass is (initial + S)
- For failure: (initial + S) < A

In sorted order:
- If asteroid A appears in sorted array
- All asteroids before A are <= A
- When A is encountered in sorted order:
  - Current mass includes all smaller asteroids' masses
  - This gives maximum possible mass for that point
- If (initial + all_smaller) < A in sorted order, failure is unavoidable
- In any other order, reaching A means:
  - Some smaller asteroids might not be destroyed yet
  - Current mass is (initial + subset of S) < (initial + S)
  - Therefore impossible to destroy A

Conclusion: Sorted ascending order maximizes success probability.

Greedy Strategy Optimality:

Why greedy ascending works (not always optimal in all contexts):
1. This problem has greedy choice property:
   - Local optimal choice (destroy smallest first) leads to global optimum
2. Optimal substructure:
   - If we can destroy first k asteroids, problem reduces to remaining
3. No conflicts:
   - Destroying small asteroid never prevents destroying large one
   - Greedy never backtracks

Alternative Approaches:

1. Try all permutations:
```cpp
vector<int> perm = asteroids;
do {
    if (canDestroy(mass, perm)) return true;
} while (next_permutation(perm.begin(), perm.end()));
```
Time: O(n! * n) - exponential, infeasible for n > 10

2. Dynamic Programming (overkill):
```cpp
sort(asteroids.begin(), asteroids.end());
dp[i][j] = can destroy first i asteroids starting with mass j
```
Time: O(n * max_mass) - worse than greedy

3. Binary Search (incorrect):
```cpp
// Can't binary search on asteroid destruction order
// Problem has specific constraint: sequential destruction
```

Why Greedy is Optimal:
- O(n log n) time is near-optimal
- Space efficient: O(1)
- Simple, elegant solution
- Clearly correct logic

Common Mistakes to Avoid:

1. Forgetting to sort:
   - Without sorting, fails on cases like [3, 9, 19, 8]
   - Must sort ascending

2. Using int instead of long long:
   - For large inputs, cumulative sum overflows 32-bit int
   - Example: mass=10^9, 10^5 asteroids of 10^9 each
   - Sum ≈ 10^14 > 2^31

3. Checking currentMass > asteroids[i] instead of >=:
   - If mass equals asteroid, can still destroy
   - Condition should be >= not >

4. Modifying original array unnecessarily:
   - sort() modifies in-place, but that's okay
   - If immutability required, use stable_sort or extra space

5. Early termination bug:
   - Correctly returns false on first failure
   - Correctly continues to next on success

Performance Characteristics:

Input size performance:
- n=10: <1ms (sorting overhead minimal)
- n=1000: <1ms (O(n log n) ≈ 10000 ops)
- n=10^5: <10ms (O(n log n) ≈ 1.7M ops)
- n=10^6: ~100ms (O(n log n) ≈ 20M ops)

Sorting algorithm:
- std::sort uses introsort (quicksort + heapsort)
- Average: O(n log n)
- Worst: O(n log n) after recent improvements
- In-place sorting (space efficient)

Cache behavior:
- Sorted array has better cache locality
- Sequential access pattern in for loop
- Good cache hit rate after sorting

Why This Problem Matters:

1. Teaches greedy algorithm design
2. Shows importance of sorting
3. Demonstrates integer overflow concerns
4. Simple but non-trivial optimization
5. Common interview problem

When to Use Greedy Approach:

1. Greedy choice property exists
2. Optimal substructure exists
3. Problem has ordering constraint
4. Local choice leads to global optimum

Related Problems (Greedy):
- Jump Game (greedy jump distance)
- Gas Station (greedy starting point)
- Candy Distribution (greedy rating comparison)
- Interval Scheduling (greedy earliest end)

Variants:

1. Maximize asteroids destroyed:
   - Greedy sorted order still works
   - Stop when can't destroy next

2. Find minimum initial mass:
   - Binary search on mass
   - For each mass, use greedy check

3. With asteroid directions (collision):
   - More complex, different strategy
   - Can't use simple greedy

4. Multiple planets:
   - Distribute asteroids among planets
   - Still use greedy within each planet

Learning Points:

1. Greedy algorithms: when and why
2. Sorting as preprocessing step
3. Integer overflow handling with long long
4. Proof of correctness via exchange argument
5. Time complexity analysis
6. When greedy is optimal vs suboptimal
7. Edge case handling
8. Performance optimization

This problem teaches:
- Core greedy principle
- Sorting importance
- Simple but powerful optimization
- How small decisions compound (mass growth)

Real-world applications:
- Task scheduling (smallest job first)
- Resource allocation (minimal resources first)
- Risk management (smallest threats first)
- Load balancing (greedy assignment)
*/
