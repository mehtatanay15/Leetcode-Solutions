// LeetCode 2144: Minimum Cost of Buying Textbooks
// Problem: Buy books where every 3rd book is free (sorted by price)
// Goal: Find minimum total cost to buy all books
// Approach: Greedy - sort descending, group in 3s, pay for top 2 only

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        // Sort in descending order so most expensive books come first
        sort(cost.begin(), cost.end(), greater<int>());
        
        int minCost = 0;
        int n = cost.size();
        
        // Process every 3 books as a group
        for (int i = 0; i < n; i += 3) {
            // Always pay for the most expensive (at position i)
            minCost += cost[i];
            
            // Pay for the second book if it exists
            if (i + 1 < n) {
                minCost += cost[i + 1];
            }
            
            // Skip the third book in the group (it's free)
            // No need to check i + 2, it's automatically free or doesn't exist
        }
        
        return minCost;
    }
};

/*
Time Complexity: O(n log n) where:
  - n = number of books
  - Sorting: O(n log n) using std::sort
  - Iteration: O(n) - single pass through sorted array
  - Total: O(n log n) dominated by sorting

Space Complexity: O(1)
  - Sorting done in-place
  - Only constant extra variables (minCost, i, n)
  - No additional data structures allocated

Algorithm Explanation:

Problem Overview:
Given prices of books with a special offer:
- Buy 2 books: get 1 book of <= price free
- Must choose which books to buy and which to get free
- Goal: minimize total cost to buy all books

Key Insight - Greedy Strategy:
Sort books in descending price order, group in 3s:
- Group 1: [Book1, Book2, Book3] where Book1 >= Book2 >= Book3
- Pay for Book1 and Book2 (both most expensive)
- Get Book3 free (least expensive in group)

Why Descending Order?
To maximize savings:
- Most expensive books have higher absolute value
- Want to waste the free slot on cheapest books possible
- But also want expensive books to be closest to free
- Descending ensures: in each group of 3, cheapest is the free one
- This maximizes total savings

Example visualization:
Books: [5, 1, 3, 9, 2]
Sorted ascending [1, 2, 3, 5, 9] (wrong):
- Groups: [1, 2, 3], [5, 9]
- Pay: 2 + 3 + 5 + 9 = 19 (paid for indices 1,2,3,4, free: 0)
- Free slot wasted on cheapest (1)

Sorted descending [9, 5, 3, 2, 1] (correct):
- Groups: [9, 5, 3], [2, 1]
- Pay: 9 + 5 + 2 = 16 (paid for indices 0,1,3, free: 2)
- Free slot wasted on cheapest (3)
- Savings: 19 - 16 = 3 ✓

Why is this optimal?
- Each group of 3 books must pay for exactly 2 (1 free)
- To minimize cost: free slot should be on cheapest book
- Descending order within each group ensures this
- With ceil(n/3) free books, want them to be cheapest possible
- Greedy grouping by sorted order achieves this

Example 1: cost = [3, 2, 1]

Initial: cost = [3, 2, 1]
After sort (descending): cost = [3, 2, 1]

Iteration i=0:
- minCost += cost[0] = 3, total = 3
- i + 1 = 1 < 3, minCost += cost[1] = 2, total = 5
- Skip cost[2] (free)

i = 3 >= n, exit loop

Result: 5

Explanation:
- Buy book costing 3: pay 3
- Buy book costing 2: pay 2
- Buy book costing 1: FREE
- Total: 5 ✓

Example 2: cost = [1, 2, 3, 4, 5]

Initial: cost = [1, 2, 3, 4, 5]
After sort (descending): cost = [5, 4, 3, 2, 1]

Iteration i=0:
- minCost += cost[0] = 5, total = 5
- i + 1 = 1 < 5, minCost += cost[1] = 4, total = 9
- Skip cost[2] = 3 (free)

Iteration i=3:
- minCost += cost[3] = 2, total = 11
- i + 1 = 4 < 5, minCost += cost[4] = 1, total = 12
- i + 2 = 5 not < 5, no free book

i = 6 >= 5, exit loop

Result: 12

Verification:
- Groups: [5,4,3] (pay 5+4, free 3), [2,1] (pay 2+1, no free)
- Total: 5 + 4 + 2 + 1 = 12 ✓

Example 3: cost = [1, 2, 3]

Initial: cost = [1, 2, 3]
After sort (descending): cost = [3, 2, 1]

Iteration i=0:
- minCost += cost[0] = 3, total = 3
- i + 1 = 1 < 3, minCost += cost[1] = 2, total = 5
- Skip cost[2] = 1 (free)

i = 3 >= 3, exit loop

Result: 5

Explanation:
- Buy books 3 and 2: pay 3 + 2 = 5
- Get book 1 free
- Total: 5 ✓

Example 4: cost = [5, 4, 3]

Initial: cost = [5, 4, 3]
After sort (descending): cost = [5, 4, 3] (already sorted)

Iteration i=0:
- minCost += cost[0] = 5, total = 5
- i + 1 = 1 < 3, minCost += cost[1] = 4, total = 9
- Skip cost[2] = 3 (free)

i = 3 >= 3, exit loop

Result: 9

Explanation:
- Pay for most expensive (5) and second (4)
- Get cheapest (3) free
- Total: 9 ✓

Example 5: cost = [8, 4, 6, 2, 3]

Initial: cost = [8, 4, 6, 2, 3]
After sort (descending): cost = [8, 6, 4, 3, 2]

Iteration i=0:
- minCost += cost[0] = 8, total = 8
- i + 1 = 1 < 5, minCost += cost[1] = 6, total = 14
- Skip cost[2] = 4 (free)

Iteration i=3:
- minCost += cost[3] = 3, total = 17
- i + 1 = 4 < 5, minCost += cost[4] = 2, total = 19
- i + 2 = 5 not < 5, remainder

i = 6 >= 5, exit loop

Result: 19

Verification:
- Groups: [8,6,4] (pay 8+6, free 4), [3,2] (pay 3+2, no free)
- Savings: 8+6+4+3+2=23, with free: 23-4=19 ✓

Example 6: cost = [1, 1, 1, 1, 1, 1, 1]

Initial: cost = [1, 1, 1, 1, 1, 1, 1]
After sort (descending): cost = [1, 1, 1, 1, 1, 1, 1] (all equal)

Iteration i=0:
- minCost += 1, total = 1
- minCost += 1, total = 2
- Skip (free)

Iteration i=3:
- minCost += 1, total = 3
- minCost += 1, total = 4
- Skip (free)

Iteration i=6:
- minCost += 1, total = 5
- i + 1 = 7 not < 7, no second book
- Skip (can't have third)

i = 9 >= 7, exit loop

Result: 5

Verification:
- 7 books total
- Groups of 3: 2 full groups (6 books), 1 book remaining
- Full groups: pay 1+1=2 each, so 4 total
- Remaining: 1 book, pay 1
- Total: 4 + 1 = 5 ✓

Edge Cases Handled:

1. Single book [5]:
   - i=0: minCost += 5 = 5
   - i+1=1 not < 1, no second book
   - Result: 5 ✓

2. Two books [5, 3]:
   - i=0: minCost += 5 = 5
   - i+1=1 < 2: minCost += 3 = 8
   - No third book to skip
   - Result: 8 ✓

3. Exactly 3 books [5, 3, 1]:
   - i=0: pay 5 + 3, skip 1
   - Result: 8 ✓

4. Many books with large values:
   - Descending sort handles this
   - No overflow risk (sum of costs fits in int)

5. Books with equal cost:
   - Sorting doesn't change positions (stable sort)
   - Still gets free slot on one of the equal-cost books
   - Correct result ✓

Why Greedy is Optimal:

Proof:
- n books total
- Number of free books: floor(n/3)
- Must have exactly this many free books (one per group of 3)
- To minimize cost: these free books should be the cheapest possible
- By sorting descending and grouping sequentially:
  - Each group gets the cheapest book in that group free
  - This distributes the cheapest floor(n/3) books as free
  - (with possible remainder book unpaired)
- Any other arrangement would waste free slots on more expensive books
- Therefore this is optimal

Alternative Approaches:

1. Ascending Sort (incorrect):
```cpp
sort(cost.begin(), cost.end()); // ascending
// Pay for every book except every 3rd
for each book: if index % 3 != 2: minCost += cost
```
Result: Correct sum but code structure different
Issues: free slot on most expensive in group, suboptimal

2. DP approach (overkill):
```cpp
dp[i] = min cost to buy first i books
// For each i, try grouping with previous books
```
Time: O(n) after precomputation
Space: O(n)
Not needed; greedy is simpler and faster

3. Recursion with memoization:
```cpp
memo = {}
def solve(idx):
    if idx >= n: return 0
    if idx in memo: return memo[idx]
    // Either buy 1 book, or buy 2 books and skip 3rd
    memo[idx] = ...
```
Time: O(n)
Space: O(n)
Overly complex for this problem

Why Greedy is Best:
- O(n log n) time (sorting dominates)
- O(1) space
- Simple, elegant, easy to understand
- Clearly correct

Common Mistakes to Avoid:

1. Sorting in ascending instead of descending:
   - Would waste free slots on expensive books
   - Result in suboptimal cost

2. Wrong grouping logic:
   - i += 3 must be the step, not i += 1
   - Each group should be exactly 3 books

3. Not checking i + 1 < n:
   - Last group might have 1 or 2 books only
   - Need bounds check for second book

4. Trying to mark book at i + 2 as free:
   - Don't need explicit code; loop structure handles it
   - Loop naturally skips every 3rd book

5. Off-by-one errors:
   - i + 1 < n checks correctly
   - i + 2 would be unnecessary

Optimization Opportunities:

1. Use partial_sort (for top books only):
   - Not beneficial here; need all books
   - full sort is standard approach

2. Custom comparator:
   - greater<int>() is simplest
   - Could use lambda, but no advantage

3. Early termination:
   - No early termination possible
   - Must process all books

4. Bitwise operations:
   - i += 3 is already optimal
   - No bitwise trick helps

Why This Problem Matters:

1. Teaches greedy algorithm design
2. Shows sorting for optimization
3. Demonstrates problem pattern recognition
4. Similar to many real-world scenarios
5. Good interview problem (simple but non-trivial)

When to Use This Approach:

1. Optimization with periodic discounts
2. Resource allocation with fixed ratios
3. Cost minimization with constraints
4. Greedy choice property applies

Real-world Applications:

1. Bulk discount pricing
2. Tax calculation strategies
3. Promotional offer optimization
4. Volume-based pricing
5. Bundle deals analysis

Related Problems (Greedy + Sorting):
- Best Time to Buy and Sell Stock
- Jump Game variants
- Candy Distribution
- Two City Scheduling
- Meeting Rooms

Variants:

1. Different free policy (every 2nd, 4th):
   - Change i += 3 to appropriate step
   - Adjust paid positions

2. Progressive discounts:
   - More complex; might need DP

3. Multiple types of books:
   - Could sort by type first, then apply algorithm

4. Combining offers:
   - Harder; might need optimization

Learning Points:

1. Greedy algorithm correctness
2. Sorting importance
3. Loop structure for grouping
4. Bounds checking
5. Problem pattern recognition
6. Why greedy works here vs other problems
7. Proof of optimality (exchange argument)
8. Alternative approaches evaluation

This problem teaches:
- Core greedy principle
- Sorting for optimization
- Pattern recognition (groups of 3)
- Why not all greedy works universally
- When to apply each technique

Complexity Breakdown:

Time:
- sort: O(n log n)
- loop: O(n)
- Total: O(n log n)

Space:
- sort: O(log n) stack depth (introsort)
- variables: O(1)
- Total: O(1) extra space

For large n:
- n = 10^5: < 1ms
- n = 10^6: < 10ms
- n = 10^7: < 100ms

Sorting algorithm:
- std::sort: introsort (quicksort + heapsort)
- In-place, O(n log n) guaranteed
- Better cache behavior after sort

Why Descending Specific:

Could we use ascending and just avoid paying for position % 3 == 2?
```cpp
sort(cost.begin(), cost.end());
for i = 0 to n:
    if i % 3 != 2:
        minCost += cost[i]
```
Result: Same cost, but ascending sort means:
- Cheapest books have free slot wasted on expensive one (relative)
- Descending is clearer: explicitly pay for most expensive

Correctness Verification:

For cost = [3, 2, 1]:
- Ascending: [1, 2, 3], skip position 2 (value 3), pay 1+2=3 (wrong!)
- Descending: [3, 2, 1], pay first two, skip last, pay 3+2=5 ✓

Key difference:
- Ascending: pay for the expensive book in each group
- Descending: pay for expensive books explicitly
- Descending pattern is clearer and harder to confuse

Final Notes:

This problem has:
- Simple solution
- O(n log n) complexity
- Clear greedy principle
- Few edge cases
- Good for learning greedy algorithms

Why it works:
- Periodic structure (every 3rd free)
- Can group greedily
- No conflicts between choices
- Optimal locally = optimal globally

This is a great teaching problem because:
- Easy to understand
- Greedy solution is clearly optimal
- Shows when to use sorting
- Demonstrates O(n log n) thinking
- Interview-friendly difficulty
*/
