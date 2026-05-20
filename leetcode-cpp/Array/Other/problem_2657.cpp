// LeetCode 2657: Find the Prefix Common Array of Two Arrays
// Problem: Find C where C[i] = count of elements present in both A[0..i] and B[0..i]
// Approach: Frequency tracking - increment frequency for each element seen, count when frequency reaches 2

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        
        // Frequency array to track occurrences of each element
        // freq[x] = 0: x not seen yet
        // freq[x] = 1: x seen in either A or B
        // freq[x] = 2: x seen in both A and B
        vector<int> freq(n + 1, 0);
        
        // Result array to store prefix common counts
        vector<int> C(n, 0);
        
        // Track cumulative count of common elements
        int common = 0;
        
        for (int i = 0; i < n; i++) {
            // Process element from array A
            freq[A[i]]++;
            if (freq[A[i]] == 2) {
                // Element A[i] is now common (seen in both arrays)
                common++;
            }
            
            // Process element from array B
            freq[B[i]]++;
            if (freq[B[i]] == 2) {
                // Element B[i] is now common (seen in both arrays)
                common++;
            }

            // Store the count of common elements at this prefix
            C[i] = common;
        }
        
        return C;
    }
};

/*
Time Complexity: O(n) where n is the length of arrays A and B
  - Single pass through both arrays
  - Each element processed exactly twice (once from A, once from B)
  - Frequency array access: O(1)
  - Total: O(n)

Space Complexity: O(n)
  - Frequency array: O(n) for values up to n
  - Result array C: O(n)
  - Total: O(n) excluding output

Algorithm Explanation:

Problem Overview:
Given two arrays A and B of same length n containing permutation of [1..n],
find array C where C[i] = number of elements that appear in both A[0..i] and B[0..i]

Key Insight - Frequency Counting:
- Elements range from 1 to n (permutation property)
- An element is "common" when we've seen it in both A and B
- Track this using frequency array:
  * freq[x] = 1: seen in exactly one array
  * freq[x] = 2: seen in both arrays
- When freq becomes 2, increment common count

Why This Works:
- Each element appears exactly once in A and exactly once in B
- When we see an element, we increment its frequency
- If frequency was 1, it means we saw it in the other array previously
- When frequency becomes 2, we found a matching pair

Example 1: A = [1, 3, 2, 4], B = [3, 1, 4, 2]

Initial: freq = [0,0,0,0,0], common = 0, C = []

i=0: A[0]=1, B[0]=3
- freq[1]++ → freq[1]=1 (1 from A)
- freq[1] != 2, no increment
- freq[3]++ → freq[3]=1 (3 from B)
- freq[3] != 2, no increment
- common = 0
- C = [0]
- freq = [0,1,0,1,0]

i=1: A[1]=3, B[1]=1
- freq[3]++ → freq[3]=2 (3 now in both!)
- freq[3] == 2, common++ → common = 1
- freq[1]++ → freq[1]=2 (1 now in both!)
- freq[1] == 2, common++ → common = 2
- C = [0, 2]
- freq = [0,2,0,2,0]

i=2: A[2]=2, B[2]=4
- freq[2]++ → freq[2]=1 (2 from A)
- freq[2] != 2, no increment
- freq[4]++ → freq[4]=1 (4 from B)
- freq[4] != 2, no increment
- common = 2
- C = [0, 2, 2]
- freq = [0,2,1,2,1]

i=3: A[3]=4, B[3]=2
- freq[4]++ → freq[4]=2 (4 now in both!)
- freq[4] == 2, common++ → common = 3
- freq[2]++ → freq[2]=2 (2 now in both!)
- freq[2] == 2, common++ → common = 4
- C = [0, 2, 2, 4]
- freq = [0,2,2,2,2]

Return [0, 2, 2, 4] ✓

Verification:
- i=0: A[0..0]={1}, B[0..0]={3}, common={} → count=0 ✓
- i=1: A[0..1]={1,3}, B[0..1]={3,1}, common={1,3} → count=2 ✓
- i=2: A[0..2]={1,3,2}, B[0..2]={3,1,4}, common={1,3} → count=2 ✓
- i=3: A[0..3]={1,3,2,4}, B[0..3]={3,1,4,2}, common={1,3,2,4} → count=4 ✓

Example 2: A = [2, 3, 1], B = [3, 1, 2]

Initial: freq = [0,0,0,0], common = 0

i=0: A[0]=2, B[0]=3
- freq[2]++ → freq[2]=1
- freq[3]++ → freq[3]=1
- common = 0
- C = [0]

i=1: A[1]=3, B[1]=1
- freq[3]++ → freq[3]=2, common++ → common=1
- freq[1]++ → freq[1]=1
- common = 1
- C = [0, 1]

i=2: A[2]=1, B[2]=2
- freq[1]++ → freq[1]=2, common++ → common=2
- freq[2]++ → freq[2]=2, common++ → common=3
- common = 3
- C = [0, 1, 3]

Return [0, 1, 3] ✓

Edge Cases:
1. n=1: Single element, must be same in both → [1]
2. A=[1], B=[1] → [1]
3. A and B completely different except last element: count builds up gradually
4. All elements common at different prefixes

Frequency Array Size:
- Why n+1? Because elements are from 1 to n, so index 0 unused
- Could optimize to use indices 0 to n-1 with different mapping
- n+1 is simpler and clearer

Alternative Approaches:

1. Set-based approach:
   - Time: O(n log n) with set operations
   - Space: O(n)
   - Insert elements into sets, check intersection size
   - Slower than frequency array

2. Bitmask approach (if n ≤ 64):
   - Time: O(n)
   - Space: O(1)
   - Track seen elements as bits
   - Use XOR: if bit appears twice, becomes 0
   - Can count remaining 1-bits
   - Works but less intuitive

3. Current frequency array:
   - Time: O(n)
   - Space: O(n)
   - Most straightforward
   - Clear and efficient

Why Frequency Array is Optimal:
- Takes advantage of permutation property (elements 1 to n)
- O(1) access to frequency of any element
- Direct way to track "common" count
- No sorting or complex data structures needed

Common Mistakes to Avoid:
1. Forgetting to initialize freq array to correct size (n+1)
2. Checking if freq[x] == 1 instead of == 2 for common elements
3. Not resetting common count (but it's cumulative, shouldn't reset)
4. Off-by-one errors in frequency array indexing
5. Processing A[i] and B[i] separately instead of together in same iteration

Permutation Property Usage:
- Arrays A and B are permutations of [1, 2, ..., n]
- Each value 1 to n appears exactly once in A
- Each value 1 to n appears exactly once in B
- This guarantees that when freq[x] becomes 2, x appears in both arrays
- Without permutation property, would need different approach

Problem Variants:
- Find elements common up to each prefix: current problem
- Find when each element becomes common: record index when freq[x] reaches 2
- Find total common elements (just return common count)
- Find indices where new common element appears: track changes

Correctness:
The algorithm correctly counts common elements because:
1. Initially, freq[x] = 0 for all x
2. When we first see x in A or B, freq[x] becomes 1
3. When we see x in the other array, freq[x] becomes 2
4. Exactly at this moment, we increment common
5. After both occurrences are processed, freq[x] remains 2
6. Since it's a permutation, each element seen at most twice
7. The cumulative count correctly tracks common prefix elements
*/
