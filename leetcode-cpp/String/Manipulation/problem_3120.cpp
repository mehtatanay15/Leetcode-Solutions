// LeetCode 3120: Count Special Characters in String
// Problem: Count letters that appear in both uppercase and lowercase forms in the word
// A letter is "special" if both 'a' (or any lowercase letter) and 'A' (corresponding uppercase) appear
// Approach: Track presence of lowercase and uppercase separately, then count matches

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        // Track which lowercase letters appear in the word
        vector<bool> lower(26, false);
        
        // Track which uppercase letters appear in the word
        vector<bool> upper(26, false);
        
        // First pass: mark presence of each letter in both cases
        for (char c : word) {
            if (c >= 'a' && c <= 'z') {
                // Lowercase letter: map to index 0-25
                lower[c - 'a'] = true;
            } else if (c >= 'A' && c <= 'Z') {
                // Uppercase letter: map to index 0-25
                upper[c - 'A'] = true;
            }
        }
        
        // Count how many letters appear in both cases
        int specialCount = 0;
        
        for (int i = 0; i < 26; i++) {
            // If letter i appears in both lowercase and uppercase
            if (lower[i] && upper[i]) {
                specialCount++;
            }
        }
        
        return specialCount;
    }
};

/*
Time Complexity: O(n) where n is the length of the word
  - First pass: iterate through all characters once → O(n)
  - Second pass: iterate through 26 letters → O(26) = O(1)
  - Total: O(n + 26) = O(n)

Space Complexity: O(1)
  - Two fixed-size arrays of 26 booleans
  - Space independent of input size (alphabet is fixed at 26)
  - O(26) = O(1) constant space

Algorithm Explanation:

Problem Overview:
Given a word (string), count how many letters appear in both uppercase and lowercase forms.
A letter is "special" if both its lowercase version (e.g., 'a') and uppercase version (e.g., 'A') 
appear anywhere in the word (not necessarily adjacent).

Key Insight - Two Boolean Arrays:
- Use one array to track lowercase letter presence: lower[0..25]
  * lower[i] = true if character ('a' + i) appears in word
- Use one array to track uppercase letter presence: upper[0..25]
  * upper[i] = true if character ('A' + i) appears in word
- Count positions where both arrays are true

Why This Approach:
- Simple and efficient: O(n) time, O(1) space
- No sorting or complex data structures needed
- Clear logic: two passes, first collect info, then count matches

Example 1: word = "aBb"
Characters: 'a' (lowercase a), 'B' (uppercase B), 'b' (lowercase b)

First pass (marking presence):
- 'a': lower[0] = true (index for 'a' is 0)
- 'B': upper[1] = true (index for 'B' is 1)
- 'b': lower[1] = true (index for 'b' is 1)

After first pass:
- lower = [T,T,F,F,...,F] (indices 0 and 1 true)
- upper = [F,T,F,F,...,F] (index 1 true)

Second pass (counting matches):
- i=0: lower[0]=true && upper[0]=false → no match
- i=1: lower[1]=true && upper[1]=true → match! count=1
- i=2..25: both false → no match

Return 1 ✓ (only 'b' and 'B' form a special pair)

Example 2: word = "ABC"
Characters: 'A' (uppercase A), 'B' (uppercase B), 'C' (uppercase C)

First pass:
- 'A': upper[0] = true
- 'B': upper[1] = true
- 'C': upper[2] = true

After first pass:
- lower = [F,F,F,...,F] (all false)
- upper = [T,T,T,F,...,F] (indices 0, 1, 2 true)

Second pass (counting matches):
- i=0: lower[0]=false && upper[0]=true → no match
- i=1: lower[1]=false && upper[1]=true → no match
- i=2: lower[2]=false && upper[2]=true → no match
- i=3..25: both false → no match

Return 0 ✓ (no lowercase letters, so no special pairs)

Example 3: word = "aAbBcC"
Characters: 'a', 'A', 'b', 'B', 'c', 'C'

First pass:
- 'a': lower[0] = true
- 'A': upper[0] = true
- 'b': lower[1] = true
- 'B': upper[1] = true
- 'c': lower[2] = true
- 'C': upper[2] = true

After first pass:
- lower = [T,T,T,F,...,F]
- upper = [T,T,T,F,...,F]

Second pass:
- i=0: lower[0]=true && upper[0]=true → match! count=1
- i=1: lower[1]=true && upper[1]=true → match! count=2
- i=2: lower[2]=true && upper[2]=true → match! count=3
- i=3..25: both false → no match

Return 3 ✓ (all three letters have both cases)

Example 4: word = "aabbccdd"
Characters: only lowercase letters

First pass:
- All characters are lowercase
- lower = [T,T,T,T,F,...,F]
- upper = [F,F,F,F,F,...,F]

Second pass:
- i=0: lower[0]=true && upper[0]=false → no match
- i=1: lower[1]=true && upper[1]=false → no match
- i=2: lower[2]=true && upper[2]=false → no match
- i=3: lower[3]=true && upper[3]=false → no match
- i=4..25: both false → no match

Return 0 ✓ (only lowercase letters exist)

Example 5: word = "AABBCC"
Characters: only uppercase letters

First pass:
- All characters are uppercase
- lower = [F,F,F,...,F]
- upper = [T,T,T,F,...,F]

Second pass:
- i=0: lower[0]=false && upper[0]=true → no match
- i=1: lower[1]=false && upper[1]=true → no match
- i=2: lower[2]=false && upper[2]=true → no match
- i=3..25: both false → no match

Return 0 ✓ (only uppercase letters exist)

Example 6: word = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
All 26 letters appear in both cases

First pass:
- lower = [T,T,T,...,T] (all true)
- upper = [T,T,T,...,T] (all true)

Second pass:
- Every position 0-25: both true → all match

Return 26 ✓ (all 26 letters are special)

Edge Cases:
1. Empty string "": no characters → return 0
2. Single character "a": only lowercase → return 0
3. Single uppercase "A": only uppercase → return 0
4. Duplicates "aaa": lowercase 'a' only → return 0
5. Order doesn't matter "Aa" vs "aA": both give return 1
6. Mixed with non-alphabetic "a1A": treated same as "aA" → return 1

Character Mapping:
- 'a' (lowercase) → index 0 → 'a' - 'a' = 0
- 'b' (lowercase) → index 1 → 'b' - 'a' = 1
- 'z' (lowercase) → index 25 → 'z' - 'a' = 25
- 'A' (uppercase) → index 0 → 'A' - 'A' = 0
- 'B' (uppercase) → index 1 → 'B' - 'A' = 1
- 'Z' (uppercase) → index 25 → 'Z' - 'A' = 25

Algorithm Characteristics:

Why Separate Arrays:
- Could use a single array with 52 indices (26 lowercase + 26 uppercase)
- But separate arrays make logic clearer
- More intuitive to understand the special pair concept
- Similar performance either way

Why Two Passes:
- First pass: collect all character presence information
- Second pass: count matches
- Alternative: could check in single pass with set lookups (less efficient)

Alternative Approach 1 (Using Sets):
```cpp
int numberOfSpecialChars(string word) {
    unordered_set<char> chars(word.begin(), word.end());
    int count = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        if (chars.count(c) && chars.count(c - 32)) {  // -32 converts 'a' to 'A'
            count++;
        }
    }
    return count;
}
```
Time: O(n + 26) = O(n)
Space: O(min(n, 52)) (set size)

Alternative Approach 2 (Using Bitmask):
```cpp
int numberOfSpecialChars(string word) {
    int lower = 0, upper = 0;
    for (char c : word) {
        if (c >= 'a' && c <= 'z') {
            lower |= (1 << (c - 'a'));
        } else {
            upper |= (1 << (c - 'A'));
        }
    }
    return __builtin_popcount(lower & upper);
}
```
Time: O(n)
Space: O(1)
Uses bitwise operations for more compact representation

Why Boolean Arrays are Best:
- Simple and clear
- Fixed space: exactly 52 booleans
- Fast access: O(1) array indexing
- No bitwise tricks needed
- Easy to understand for most programmers

Performance Notes:
- For typical words (length 1-100), all approaches are effectively O(1) constant time
- Boolean array approach is most straightforward
- Bitmask approach is more elegant but less readable
- Set approach trades space for simplicity

Problem Variants:
- Find which letters are special: collect them in array/set
- Count vowels that are special: add vowel check
- Case-insensitive count: apply toLowerCase first
- Count pairs with specific order (lowercase before uppercase): track first/last indices

Why This Problem Matters:
- Teaches character manipulation and indexing
- Introduces the concept of tracking presence in multiple ways
- Good warm-up for more complex string problems
- Demonstrates alphabet mapping to array indices (fundamental technique)
*/
