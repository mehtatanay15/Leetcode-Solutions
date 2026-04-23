// LeetCode 3: Longest Substring Without Repeating Characters
// Problem: Find length of longest substring with no repeating characters
// Approach: Sliding Window with HashSet

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> st;  // Current window characters
        int left = 0;            // Left pointer of window
        int maxLen = 0;          // Maximum length found

        // Expand window with right pointer
        for(int right = 0; right < s.length(); right++) {

            // If character already in window, shrink from left
            while(st.count(s[right])) {
                st.erase(s[left]);
                left++;
            }

            // Add current character to window
            st.insert(s[right]);
            
            // Update maximum length
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

/*
Time Complexity: O(n)
- Each character visited at most twice (once by right, once by left)
- Window moves monotonically left to right
- Total: O(n)

Space Complexity: O(min(m, n))
- m: size of charset (at most 26 for lowercase, 128 for ASCII)
- n: length of string
- HashSet stores at most min(m, n) unique characters

Algorithm (Sliding Window):
1. Use two pointers: left and right, both start at 0
2. For each right pointer:
   a. Expand window: check if s[right] is in set
   b. If duplicate found:
      - Shrink window from left until duplicate removed
      - Remove left character, increment left
   c. Add current character to set
   d. Update maximum length = right - left + 1
3. Return maximum length

Key Insight - Monotonic Window:
- Left pointer only moves right (never left)
- Right pointer only moves right
- Window size contracts and expands
- Guarantees O(n) complexity

Example 1:
Input: s = "abcabcbb"

Right=0, s[0]='a':
- Not in set
- st = {'a'}
- len = 0 - 0 + 1 = 1, maxLen = 1

Right=1, s[1]='b':
- Not in set
- st = {'a', 'b'}
- len = 1 - 0 + 1 = 2, maxLen = 2

Right=2, s[2]='c':
- Not in set
- st = {'a', 'b', 'c'}
- len = 2 - 0 + 1 = 3, maxLen = 3

Right=3, s[3]='a':
- Already in set!
- While loop: erase s[0]='a', left=1
- st = {'b', 'c'}
- 'a' not in set anymore
- Insert 'a'
- st = {'b', 'c', 'a'}
- len = 3 - 1 + 1 = 3, maxLen = 3

Right=4, s[4]='b':
- Already in set!
- While loop: erase s[1]='b', left=2
- st = {'c', 'a'}
- 'b' not in set
- Insert 'b'
- st = {'c', 'a', 'b'}
- len = 4 - 2 + 1 = 3, maxLen = 3

Right=5, s[5]='c':
- Already in set!
- While loop: erase s[2]='c', left=3
- st = {'a', 'b'}
- 'c' not in set
- Insert 'c'
- st = {'a', 'b', 'c'}
- len = 5 - 3 + 1 = 3, maxLen = 3

Right=6, s[6]='b':
- Already in set!
- While loop: erase s[3]='a', left=4
- st = {'b', 'c'}
- st.count('b') still 1
- While continues: erase s[4]='b', left=5
- st = {'c'}
- 'b' not in set
- Insert 'b'
- st = {'c', 'b'}
- len = 6 - 5 + 1 = 2, maxLen = 3

Right=7, s[7]='b':
- Already in set!
- While loop: erase s[5]='c', left=6
- st = {'b'}
- Still 'b' in set
- While continues: erase s[6]='b', left=7
- st = {}
- 'b' not in set
- Insert 'b'
- st = {'b'}
- len = 7 - 7 + 1 = 1, maxLen = 3

Output: 3 (substring "abc")

Example 2:
Input: s = "au"

Right=0: st={'a'}, len=1, maxLen=1
Right=1: st={'a','u'}, len=2, maxLen=2

Output: 2 (entire string)

Example 3:
Input: s = "dvdf"

Right=0: st={'d'}, len=1, maxLen=1
Right=1: st={'d','v'}, len=2, maxLen=2
Right=2: st={'d','v','f'}, len=3, maxLen=3
Right=3: 'f' not yet in set at right=2
- Actually 'f' is in set
- erase s[0]='d', left=1
- st={'v','f'}
- Insert 'f'
- st={'v','f'}
- len=3-1+1=3, maxLen=3

Output: 3 (substring "vdf")

Edge Cases:
- Empty string: return 0
- Single character: return 1
- All unique: return length
- All same: return 1

SlidingWindow Pattern:
- Two pointers technique
- Monotonic expansion and contraction
- Efficient for many substring/subarray problems
- Works when problem has monotonic property

Why HashSet (not HashMap):
- Only need to track presence, not frequency
- Set operations: O(1) insert, erase, count
- More memory efficient than HashMap
- For frequency tracking would need HashMap

Alternative Approaches:
1. HashMap with indices:
   - Store last seen index of each character
   - Update left = max(left, last_index[c] + 1)
   - Slightly cleaner logic

2. Array for ASCII:
   - Use array[256] instead of unordered_set
   - Faster in practice (fixed array vs hash table)
   - Better cache locality

Optimization for Small Charset:
- If you know charset (e.g., lowercase only)
- Use array[26] instead of unordered_set
- Time: O(n), Space: O(26) = O(1)
*/