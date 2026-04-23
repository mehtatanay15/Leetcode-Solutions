// LeetCode 205: Isomorphic Strings
// Problem: Determine if two strings are isomorphic (one-to-one character mapping)
// Approach: Two-way character mapping using arrays

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // Arrays for one-way mapping (using ASCII indices)
        int mapST[256];  // Map from s to t
        int mapTS[256];  // Map from t to s (ensure one-to-one)

        // Initialize all mappings to -1 (not set)
        for(int i = 0; i < 256; i++) {
            mapST[i] = -1;
            mapTS[i] = -1;
        }

        // Check each character pair
        for(int i = 0; i < s.length(); i++) {
            char c1 = s[i];
            char c2 = t[i];

            // First time seeing this pair
            if(mapST[c1] == -1 && mapTS[c2] == -1) {
                mapST[c1] = c2;  // s[c1] maps to t[c2]
                mapTS[c2] = c1;  // t[c2] maps back to s[c1]
            }
            // Already have a mapping - verify it's consistent
            else {
                if(mapST[c1] != c2 || mapTS[c2] != c1) {
                    return false;  // Inconsistent mapping
                }
            }
        }

        return true;
    }
};

/*
Time Complexity: O(n)
- Single pass through both strings
- n: length of strings (must be equal)

Space Complexity: O(1)
- Fixed size arrays of 256 (constant)
- Independent of input size

Algorithm (Two-way Mapping):
1. Create two mapping arrays:
   - mapST: character from s maps to character in t
   - mapTS: character from t maps back to character in s
2. Initialize all mappings to -1 (unset)
3. For each character pair (s[i], t[i]):
   a. If both are unmapped:
      - Create bidirectional mapping
      - mapST[s[i]] = t[i]
      - mapTS[t[i]] = s[i]
   b. If at least one is already mapped:
      - Verify consistency: mapST[s[i]] == t[i] AND mapTS[t[i]] == s[i]
      - If inconsistent, return false
4. If all pairs are consistent, return true

Key Insight - Why Two-way Mapping:
- Isomorphic means one-to-one correspondence
- 'a' must always map to same character in t
- That character in t must only come from 'a' (not from multiple chars)
- One-way mapping alone isn't sufficient
- Example: s="baab", t="xyyx"
  * 'b'->y, 'a'->x works for s->t
  * But in t, both 'y' from 'b' and 'x' from 'a' are unique
  * This is isomorphic ✓
- Counter-example: s="baab", t="xyxy"
  * 'b'->'x' and 'a'->'y' (first pair)
  * 'a'->'x' (second pair) but 'a' already maps to 'y' ✗
  * Need to catch this with two-way check

Example 1:
Input: s = "egg", t = "add"

Initialize: all mappings = -1

i=0: c1='e', c2='a'
- mapST['e']==−1 and mapTS['a']==−1
- mapST['e'] = 'a'
- mapTS['a'] = 'e'

i=1: c1='g', c2='d'
- mapST['g']==−1 and mapTS['d']==−1
- mapST['g'] = 'd'
- mapTS['d'] = 'g'

i=2: c1='g', c2='d'
- mapST['g']!=−1 or mapTS['d']!=−1
- Check: mapST['g'] == 'd'? Yes ✓
- Check: mapTS['d'] == 'g'? Yes ✓
- Continue

Output: true

Example 2:
Input: s = "foo", t = "bar"

i=0: c1='f', c2='b'
- mapST['f'] = 'b'
- mapTS['b'] = 'f'

i=1: c1='o', c2='a'
- mapST['o'] = 'a'
- mapTS['a'] = 'o'

i=2: c1='o', c2='r'
- mapST['o']!=−1 (it's 'a')
- Check: mapST['o'] == 'r'? No (mapST['o']='a' but r!='a')
- Return false

Output: false (o can't map to both a and r)

Example 3:
Input: s = "paper", t = "title"

i=0: 'p'->'t', mapST['p']='t', mapTS['t']='p'
i=1: 'a'->'i', mapST['a']='i', mapTS['i']='a'
i=2: 'p'->'t', check: mapST['p']='t' ✓, mapTS['t']='p' ✓
i=3: 'e'->'l', mapST['e']='l', mapTS['l']='e'
i=4: 'r'->'e'
- Check if 'r' unmapped: mapST['r']=−1, mapTS['e']=−1? No!
- mapTS['e'] already set to 'a' (from i=1)
- This would mean 'e' in t comes from both 'a' and 'r'
- Violates one-to-one mapping
- Return false

Output: false

Actually let me retrace:
i=0: 'p'->'t'
i=1: 'a'->'i'
i=2: 'p'->'t' (consistent)
i=3: 'e'->'l'
i=4: 'r'->'e'
- mapST['r']=−1 and mapTS['e']=−1? 
- mapTS['e'] is set to 'a' already (at i=1)
- So mapTS['e'] != −1
- Check: mapST['r'] != 'e'?
- mapST['r'] is −1, so −1 != 'e'? Yes
- Return false ✓

Edge Cases:
- Different lengths: should return false (but problem guarantees equal)
- Single character: always true
- Same strings: always true
- All same char in s, all different in t: false

Character Mapping Visualization:
s = "baab"
t = "xyyx"

Mapping:
'b' <-> 'x'
'a' <-> 'y'

All characters have unique mappings both ways: isomorphic ✓

Why Array vs HashMap:
- Array[256]: O(1) access, fixed space, simple
- HashMap: O(1) average, dynamic space, more complex
- For character mapping, array is better
- Works because character values are bounded (0-255 for standard ASCII)

Alternative with HashMap:
std::unordered_map<char, char> mS, mT;
for(auto i = 0; i < s.size(); i++) {
    if((mS.count(s[i]) && mS[s[i]] != t[i]) ||
       (mT.count(t[i]) && mT[t[i]] != s[i]))
        return false;
    mS[s[i]] = t[i];
    mT[t[i]] = s[i];
}
return true;

*/
