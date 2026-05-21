// LeetCode 3043: Find the Longest Common Prefix Length
// Problem: Find the longest common numeric prefix between any element in arr1 and arr2
// A numeric prefix is obtained by removing digits from the right
// Approach: Hash set for arr1 prefixes, check each arr2 element's prefixes

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        // Store all numeric prefixes from arr1
        unordered_set<int> prefixes;
        
        // Extract all numeric prefixes from each element in arr1
        for (int val : arr1) {
            while (val > 0) {
                // Add the current prefix (with rightmost digits removed)
                prefixes.insert(val);
                // Remove rightmost digit: e.g., 1521 → 152 → 15 → 1
                val /= 10;
            }
        }
        
        // Track the maximum prefix length found
        int maxLength = 0;
        
        // Check each element in arr2 for common prefixes
        for (int val : arr2) {
            while (val > 0) {
                // If this prefix exists in arr1's prefixes
                if (prefixes.count(val)) {
                    // Calculate the length of this prefix (number of digits)
                    maxLength = max(maxLength, static_cast<int>(to_string(val).length()));
                    // Found a match for this arr2 element, check next element
                    break;
                }
                // Remove rightmost digit and check next prefix
                val /= 10;
            }
        }
        
        return maxLength;
    }
};

/*
Time Complexity: O(m * log10(max_arr1) + n * log10(max_arr2))
  - Building prefixes from arr1: m elements × log10(max value)
    * For each element, divide by 10 until 0: at most log10(num) times
    * Insert into set: O(1) average
  - Checking prefixes from arr2: n elements × log10(max value)
    * For each element, divide by 10 until 0: at most log10(num) times
    * Lookup in set: O(1) average
  - Converting to string for length: O(log10(num))
  - Total: O((m + n) * log10(max_value))

Space Complexity: O(m * log10(max_value))
  - Hash set stores all prefixes from arr1
  - Each element contributes log10(value) prefixes
  - Worst case: m × log10(max_value) entries

Algorithm Explanation:

Problem Overview:
Given two arrays of integers, find the longest numeric prefix common to any element
from arr1 and any element from arr2.

Numeric Prefix Definition:
- For number 1521, numeric prefixes are: 1521, 152, 15, 1
- Obtained by repeatedly removing the rightmost digit
- The "length" of prefix 1521 is 4 (4 digits)
- The "length" of prefix 152 is 3 (3 digits)

Key Insight - Divide by 10 for Prefixes:
- Instead of converting to string, use division: val /= 10
- This removes the rightmost digit numerically
- More efficient than string manipulation
- Example: 1521 → 152 → 15 → 1 → 0 (loop ends)

Two-Phase Approach:

Phase 1 - Build Prefix Set:
- Store all numeric prefixes from arr1 in a hash set
- For each number in arr1, generate all prefixes by dividing by 10
- This preprocessing enables O(1) lookup later

Phase 2 - Find Longest Match:
- For each element in arr2, check its prefixes
- Use the first matching prefix (longest for this element)
- Track the maximum length across all matches

Why First Match is Longest for Each Element:
- We extract prefixes from longest to shortest
- First match found is the longest prefix of arr2[i] that exists in arr1
- We break immediately, no need to check shorter prefixes of arr2[i]

Example 1: arr1 = [1521, 228, 1], arr2 = [4, 0, 924]

Phase 1 - Build prefixes from arr1:
- 1521: add 1521, 152, 15, 1
- 228: add 228, 22, 2
- 1: add 1
- prefixes = {1521, 152, 15, 1, 228, 22, 2}

Phase 2 - Check arr2:
- val = 4: Check 4 in prefixes? No. 0 < 0? No, loop ends. No match.
- val = 0: While condition fails immediately (0 > 0? No). No match.
- val = 924: Check 924 in prefixes? No → val = 92
              Check 92 in prefixes? No → val = 9
              Check 9 in prefixes? No → val = 0
              0 > 0? No, loop ends. No match.
- maxLength = 0

Return 0 (no common prefix)

Example 2: arr1 = [1521, 228, 1], arr2 = [15, 228]

Phase 1 - Build prefixes:
- prefixes = {1521, 152, 15, 1, 228, 22, 2}

Phase 2 - Check arr2:
- val = 15: Check 15 in prefixes? YES!
  * length = to_string(15).length() = 2
  * maxLength = max(0, 2) = 2
  * break
- val = 228: Check 228 in prefixes? YES!
  * length = to_string(228).length() = 3
  * maxLength = max(2, 3) = 3
  * break

Return 3 ✓

Example 3: arr1 = [156, 12], arr2 = [15, 123]

Phase 1 - Build prefixes:
- 156: 156, 15, 1
- 12: 12, 1
- prefixes = {156, 15, 1, 12}

Phase 2 - Check arr2:
- val = 15: Check 15 in prefixes? YES!
  * length = 2
  * maxLength = 2

- val = 123: Check 123 in prefixes? No → val = 12
             Check 12 in prefixes? YES!
  * length = 2
  * maxLength = max(2, 2) = 2

Return 2 ✓

Edge Cases:
1. Single digit numbers: e.g., 5, 7
   - Only prefix is the number itself
   - Divide once: 5 → 0, loop ends

2. No common prefixes: return 0
   - Example: arr1 = [1], arr2 = [2]
   - Prefixes of 1: {1}
   - Prefixes of 2: {2}
   - No match: return 0

3. Array with 0:
   - 0 > 0 is false, loop never executes
   - No prefixes generated for 0

4. Leading zeros don't occur:
   - Numeric division naturally avoids leading zeros
   - 100 / 10 = 10, not 010

5. Large numbers:
   - Division by 10 efficiently handles any size
   - Set lookup remains O(1) average

Algorithm Characteristics:

Numeric vs String Approach:
- Numeric: val /= 10 (efficient integer division)
- String: to_string, then remove last character (more operations)
- Current solution uses numeric for extraction, string for length calculation
- Could optimize by counting divisions instead of to_string

Optimization: Count Digits Instead of to_string:
Instead of: `static_cast<int>(to_string(val).length())`
Could use: `int len = 0; int temp = val; while (temp > 0) { len++; temp /= 10; } `
This avoids string conversion overhead.

Why Set Instead of Map/Array:
- Only need membership test, not frequency count
- Set is more natural for this use case
- Unordered_set gives O(1) average vs O(log n) for tree-based set

Memory Efficiency:
- For m elements with at most d digits:
  * Total prefixes ≤ m × d
  * Space: O(m × d) for set
  * If d = log10(max_value), space is logarithmic per element

Time-Space Tradeoff:
- Current approach: O((m+n)×d) time, O(m×d) space
- Alternative (nested loops with string comparison): O(m×n×d²) time, O(d) space
- Current is far superior for large arrays

Common Mistakes:
1. Comparing strings instead of integers (slower)
2. Forgetting to cast to int for length calculation
3. Not breaking after finding first match in arr2 loop
4. Handling 0 incorrectly (0 > 0 is already false)
5. Using regular set instead of unordered_set (slower lookup)

Problem Variants:
- Find longest common SUFFIX (reverse numbers first)
- Find all common prefixes (use vector instead of max)
- Find count of common prefixes (adjust counting logic)
- Case-insensitive string prefixes (different problem, same approach structure)

Correctness Proof:
The algorithm finds the longest common numeric prefix by:
1. Exhaustively storing all prefixes of arr1
2. For each arr2 element, checking prefixes from longest to shortest
3. Taking the maximum length across all matches

This is correct because:
- The set contains ALL prefixes of arr1, so we don't miss any
- The longest matching prefix is found first due to division order
- The maximum across all matches gives the global maximum
*/
