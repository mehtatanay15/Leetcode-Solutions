// LeetCode 151: Reverse Words in a String
// Problem: Reverse the order of words in a string (skip extra spaces)
// Approach: Two pointers (right to left extraction)

class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();

        // Step 1: Replace spaces with delimiter for easy identification
        for(int i = 0; i < n; i++) {
            if(s[i] == ' ') {
                s[i] = '#';
            }
        }

        vector<string> words;
        int i = n - 1;

        // Step 2: Extract words from right to left
        while(i >= 0) {
            // Skip delimiters (spaces)
            if(s[i] == '#') {
                i--;
                continue;
            }

            int r = i;  // Right boundary of current word

            // Move left to find word start
            while(i >= 0 && s[i] != '#') {
                i--;
            }

            int l = i + 1;  // Left boundary of current word

            // Extract word from right to left (automatically reverses order)
            words.push_back(s.substr(l, r - l + 1));
        }

        // Step 3: Join words with single space
        string result = "";
        for(int i = 0; i < words.size(); i++) {
            if(i > 0) result += " ";
            result += words[i];
        }

        return result;
    }
};

/*
Time Complexity: O(n)
- Replace spaces: O(n)
- Extract words (right to left): O(n)
- Join words: O(n)
- Total: O(n)

Space Complexity: O(n)
- Vector to store words: O(n)
- Result string: O(n)

Algorithm (Right-to-Left Extraction):
1. Replace all spaces with '#' for easy delimiter detection
2. Start from rightmost character (i = n-1)
3. For each word from right to left:
   a. Skip all delimiters (#)
   b. Mark right boundary (r = i)
   c. Move left until we hit a delimiter or start
   d. Mark left boundary (l = i+1)
   e. Extract word using substr(l, length)
   f. Add word to result vector
4. By extracting from right to left, words are automatically in reversed order
5. Join words with single space

Why Right-to-Left:
- Extracting from end gives us reversed word order automatically
- Avoids need for explicit reverse operation
- More efficient than left-to-right with additional reverse

Example 1:
Input: "  Hello World  "

After replace spaces:
"##Hello#World##"

Right-to-left extraction:
i=14: s[14]='#', skip
i=13: s[13]='#', skip
i=12: s[12]='d', r=12
i=11,10,...: letters, move left
i=5: s[5]='#', boundary found, l=6
- Extract "World", add to words
i=4: s[4]='#', skip
i=3: s[3]='o', r=3
i=2,1: letters, move left
i=0: s[0]='#', boundary found, l=1
- Extract "Hello", add to words
i=-1: stop

words = ["World", "Hello"]
Join with space: "World Hello"

Output: "World Hello"

Example 2:
Input: "the sky is blue"

After replace:
"the#sky#is#blue"

Extraction (right to left):
- Extract "blue"
- Extract "is"
- Extract "sky"
- Extract "the"

words = ["blue", "is", "sky", "the"]
Join: "blue is sky the"

Output: "the sky is blue"

Edge Cases:
- Leading spaces: skipped in extraction
- Trailing spaces: skipped before extraction starts
- Multiple consecutive spaces: collapsed into single space
- Single word: returns that word
- Empty string: returns empty

Alternative Approaches:
1. Direct reverse + two pointers:
   - Reverse entire string
   - Reverse each word
   - Time: O(n), Space: O(1) if in-place

2. Split and reverse:
   - Split by space
   - Reverse word order
   - Join
   - Time: O(n), Space: O(n)

Why This Approach:
- Clear visualization of extracting right to left
- Naturally gives reversed order
- Good balance of readability and efficiency
- Shows understanding of pointer techniques
*/
};