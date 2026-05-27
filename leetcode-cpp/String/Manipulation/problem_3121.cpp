// LeetCode 3121: Count Special Characters II
// Problem: Count letters where BOTH cases exist AND lowercase appears before uppercase in the string
// Variant of 3120: adds ordering constraint - lowercase must come before uppercase
// Approach: Track last occurrence of each lowercase, first occurrence of each uppercase, then validate ordering

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        // Track the last (rightmost) index of each lowercase letter
        vector<int> last_lower(26, -1);
        
        // Track the first (leftmost) index of each uppercase letter
        vector<int> first_upper(26, -1);
        
        // First pass: record last occurrence of lowercase, first occurrence of uppercase
        for (int i = 0; i < word.length(); ++i) {
            if (islower(word[i])) {
                // Update last occurrence of this lowercase letter
                last_lower[word[i] - 'a'] = i;
            } else {
                // Record only the first (leftmost) occurrence of this uppercase letter
                if (first_upper[word[i] - 'A'] == -1) {
                    first_upper[word[i] - 'A'] = i;
                }
            }
        }
        
        int specialCount = 0;
        
        // Second pass: count special characters
        // Special char: both cases exist AND lowercase appears before uppercase
        for (int i = 0; i < 26; ++i) {
            if (last_lower[i] != -1 &&              // lowercase exists
                first_upper[i] != -1 &&            // uppercase exists
                last_lower[i] < first_upper[i]) {  // lowercase comes before uppercase
                specialCount++;
            }
        }
        
        return specialCount;
    }
};

/*
Time Complexity: O(n) where n is the length of the word
  - First pass: single iteration through all characters → O(n)
  - Second pass: iterate through 26 letters → O(26) = O(1)
  - Total: O(n + 26) = O(n)

Space Complexity: O(1)
  - Two fixed-size arrays of 26 integers
  - Space independent of input size
  - O(26) = O(1) constant space

Algorithm Explanation:

Problem Overview (Variant of 3120):
Given a word, count letters where:
1. Both lowercase and uppercase forms appear
2. At least one lowercase occurrence comes BEFORE at least one uppercase occurrence

Key Difference from 3120:
- 3120: Just checks if both cases exist (order doesn't matter)
- 3121: Checks if both cases exist AND lowercase appears before uppercase

Why Track First/Last:
- last_lower[i]: rightmost position of lowercase letter i
  * We need the latest occurrence to maximize chance of coming before uppercase
- first_upper[i]: leftmost position of uppercase letter i
  * We need the earliest occurrence to minimize chance of coming after lowercase
- If last_lower[i] < first_upper[i], the letter definitely satisfies the ordering constraint

Example 1: word = "aAbBcC"
First pass (record positions):
- i=0: 'a' (lowercase) → last_lower[0] = 0
- i=1: 'A' (uppercase) → first_upper[0] = 1
- i=2: 'b' (lowercase) → last_lower[1] = 2
- i=3: 'B' (uppercase) → first_upper[1] = 3
- i=4: 'c' (lowercase) → last_lower[2] = 4
- i=5: 'C' (uppercase) → first_upper[2] = 5

After first pass:
- last_lower = [0,2,4,...]
- first_upper = [1,3,5,...]

Second pass:
- i=0: last_lower[0]=0, first_upper[0]=1, 0 < 1? Yes! count++
- i=1: last_lower[1]=2, first_upper[1]=3, 2 < 3? Yes! count++
- i=2: last_lower[2]=4, first_upper[2]=5, 4 < 5? Yes! count++

Return 3 ✓ (all three letters: a→A, b→B, c→C order satisfied)

Example 2: word = "AaBbCc"
First pass:
- i=0: 'A' (uppercase) → first_upper[0] = 0
- i=1: 'a' (lowercase) → last_lower[0] = 1
- i=2: 'B' (uppercase) → first_upper[1] = 2
- i=3: 'b' (lowercase) → last_lower[1] = 3
- i=4: 'C' (uppercase) → first_upper[2] = 4
- i=5: 'c' (lowercase) → last_lower[2] = 5

After first pass:
- last_lower = [1,3,5,...]
- first_upper = [0,2,4,...]

Second pass:
- i=0: last_lower[0]=1, first_upper[0]=0, 1 < 0? No
- i=1: last_lower[1]=3, first_upper[1]=2, 3 < 2? No
- i=2: last_lower[2]=5, first_upper[2]=4, 5 < 4? No

Return 0 ✓ (all uppercase appear before lowercase, order violated)

Example 3: word = "AaBaCb"
First pass:
- i=0: 'A' → first_upper[0] = 0
- i=1: 'a' → last_lower[0] = 1
- i=2: 'B' → first_upper[1] = 2
- i=3: 'a' → last_lower[0] = 3 (updated)
- i=4: 'C' → first_upper[2] = 4
- i=5: 'b' → last_lower[1] = 5

After first pass:
- last_lower = [3,5,...]
- first_upper = [0,2,4,...]

Second pass:
- i=0: last_lower[0]=3, first_upper[0]=0, 3 < 0? No (uppercase A comes first globally)
- i=1: last_lower[1]=5, first_upper[1]=2, 5 < 2? No (uppercase B comes first globally)
- i=2: last_lower[2]=-1 (no lowercase c)

Return 0 ✓ (even though 'a' appears after initial 'A', we have no valid pair)

Example 4: word = "aAbBcCdEfG"
First pass:
- i=0: 'a' → last_lower[0] = 0
- i=1: 'A' → first_upper[0] = 1
- i=2: 'b' → last_lower[1] = 2
- i=3: 'B' → first_upper[1] = 3
- i=4: 'c' → last_lower[2] = 4
- i=5: 'C' → first_upper[2] = 5
- i=6: 'd' → last_lower[3] = 6
- i=7: 'E' → first_upper[4] = 7
- i=8: 'f' → last_lower[5] = 8
- i=9: 'G' → first_upper[6] = 9

After first pass:
- last_lower = [0,2,4,6,8,-1,...]
- first_upper = [1,3,5,7,9,-1,...]

Second pass:
- i=0: 0 < 1? Yes! count++ (a before A)
- i=1: 2 < 3? Yes! count++ (b before B)
- i=2: 4 < 5? Yes! count++ (c before C)
- i=3: 6 < 7? Yes! count++ (d before E)
- i=4: last_lower[4]=-1 (no lowercase e)
- i=5: 8 < 9? Yes! count++ (f before G)
- i=6: last_lower[6]=-1 (no lowercase g)

Return 5 ✓

Example 5: word = "aaAAaaBBbb"
First pass:
- i=0: 'a' → last_lower[0] = 0
- i=1: 'a' → last_lower[0] = 1
- i=2: 'A' → first_upper[0] = 2
- i=3: 'A' → first_upper[0] = 2 (already set, skip)
- i=4: 'a' → last_lower[0] = 4
- i=5: 'a' → last_lower[0] = 5
- i=6: 'B' → first_upper[1] = 6
- i=7: 'B' → first_upper[1] = 6 (already set, skip)
- i=8: 'b' → last_lower[1] = 8
- i=9: 'b' → last_lower[1] = 9

After first pass:
- last_lower = [5,9,...]
- first_upper = [2,6,...]

Second pass:
- i=0: last_lower[0]=5, first_upper[0]=2, 5 < 2? No (uppercase comes before last lowercase)
- i=1: last_lower[1]=9, first_upper[1]=6, 9 < 6? No (uppercase comes before last lowercase)

Return 0 ✓ (uppercase appears before the final lowercase for each letter)

Example 6: word = "abc"
First pass:
- i=0: 'a' → last_lower[0] = 0
- i=1: 'b' → last_lower[1] = 1
- i=2: 'c' → last_lower[2] = 2

After first pass:
- last_lower = [0,1,2,...]
- first_upper = [-1,-1,-1,...] (all -1, no uppercase letters)

Second pass:
- i=0: last_lower[0]=0, first_upper[0]=-1? No (first_upper is -1)
- i=1: last_lower[1]=1, first_upper[1]=-1? No
- i=2: last_lower[2]=2, first_upper[2]=-1? No

Return 0 ✓ (no uppercase letters exist)

Example 7: word = "ABC"
First pass:
- i=0: 'A' → first_upper[0] = 0
- i=1: 'B' → first_upper[1] = 1
- i=2: 'C' → first_upper[2] = 2

After first pass:
- last_lower = [-1,-1,-1,...] (all -1, no lowercase letters)
- first_upper = [0,1,2,...]

Second pass:
- i=0: last_lower[0]=-1? No (last_lower is -1)
- i=1: last_lower[1]=-1? No
- i=2: last_lower[2]=-1? No

Return 0 ✓ (no lowercase letters exist)

Algorithm Characteristics:

Why Track Last Lowercase, First Uppercase:
- We want to know if ANY lowercase appears before ANY uppercase
- last_lower[i] = rightmost lowercase i → includes all lowercase occurrences
- first_upper[i] = leftmost uppercase i → includes all uppercase occurrences
- Checking last_lower < first_upper is the strongest condition
- If this fails, no lowercase-before-uppercase arrangement is possible

Why Not Track All Occurrences:
- Could store arrays of all indices for each letter
- But we only need last and first for the ordering check
- This reduces space from O(n) to O(1)

Comparison with 3120:
| Aspect | 3120 | 3121 |
|--------|------|------|
| Requirement | Both cases exist | Both cases exist + order |
| Data tracking | Boolean (presence) | Integer (position) |
| Space | O(1) with booleans | O(1) with integers |
| Time | O(n) | O(n) |
| Complexity | Simpler | Slightly more complex |

Alternative Approach (Single Pass):
```cpp
int numberOfSpecialChars(string word) {
    int lower_mask = 0, upper_mask = 0;
    vector<int> last_lower(26, -1), first_upper(26, -1);
    
    for (int i = 0; i < word.length(); ++i) {
        if (islower(word[i])) {
            last_lower[word[i] - 'a'] = i;
            lower_mask |= (1 << (word[i] - 'a'));
        } else {
            if (first_upper[word[i] - 'A'] == -1) {
                first_upper[word[i] - 'A'] = i;
            }
            upper_mask |= (1 << (word[i] - 'A'));
        }
    }
    
    int count = 0;
    for (int i = 0; i < 26; ++i) {
        if (last_lower[i] != -1 && first_upper[i] != -1 && last_lower[i] < first_upper[i]) {
            count++;
        }
    }
    return count;
}
```
Adds bitmask optimization but with same complexity.

Edge Cases:
1. Single character "a": only lowercase → return 0
2. Single character "A": only uppercase → return 0
3. Empty string "": return 0
4. No overlap "aAbBcC": all lowercase before uppercase → return 3 (if ordered correctly)
5. No overlap "AaBbCc": all uppercase before lowercase → return 0
6. One letter "aA": return 1
7. One letter "Aa": return 0 (uppercase first)
8. Many duplicates "aaaa...AAAA...": same as single occurrence check

Why This Problem:
- Teaches position tracking and ordering constraints
- Extends the concept of presence checking from 3120
- Useful for problems requiring "before/after" validation
- Demonstrates the value of tracking first/last occurrences

Optimization Notes:
- Early return optimization for empty string possible
- No sorting needed (linear scan suffices)
- Could short-circuit if all 26 letters checked
- The two-array approach is cleaner than combined array

Common Mistakes:
1. Not initializing arrays to -1 (using 0 causes false matches)
2. Checking first_upper[i] == 0 directly (position 0 is valid!)
3. Forgetting to update last_lower on subsequent occurrences
4. Always setting first_upper instead of only on first occurrence
5. Using wrong index (letter - 'a') vs (letter - 'A')
*/
