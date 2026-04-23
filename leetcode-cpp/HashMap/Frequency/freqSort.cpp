// LeetCode 451: Sort Characters By Frequency
// Problem: Sort string characters by their frequency in descending order
// Approach: HashMap + Sorting by frequency

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mpp;

        // Step 1: Count frequency of each character
        for(int i = 0; i < s.length(); i++) {
            mpp[s[i]]++;
        }

        // Step 2: Convert map to vector of pairs for sorting
        vector<pair<char, int>> arr(mpp.begin(), mpp.end());

        // Step 3: Sort by frequency (descending order)
        sort(arr.begin(), arr.end(), [](auto &a, auto &b) {
            return a.second > b.second;  // Sort by count in descending order
        });

        // Step 4: Build result string with characters repeated by frequency
        string result = "";
        for(auto &p : arr) {
            // Add character p.first, p.second times
            result += string(p.second, p.first);
        }

        return result;
    }
};

/*
Time Complexity: O(n + k log k)
- n: length of string (counting frequencies)
- k: number of unique characters (at most 26 for lowercase, 52 for mixed case)
- Counting: O(n)
- Sorting: O(k log k) where k <= 26 or 52
- Building result: O(n)
- Total: O(n + k log k) ≈ O(n) since k is constant

Space Complexity: O(k)
- HashMap stores at most k unique characters
- Vector stores at most k pairs
- Result string: O(n) but not counted as extra space

Algorithm (HashMap + Sorting):
1. Count frequency of each character using HashMap
2. Convert HashMap to vector of (char, frequency) pairs
3. Sort vector by frequency in descending order
   - Higher frequency characters come first
4. Build result string by:
   - For each character, append it frequency times
   - string(count, char) creates string with char repeated count times

Key Insight:
- Using string constructor string(count, char) to repeat characters
- More efficient than looping and appending individually
- Sorting by second element of pair (frequency)

Example 1:
Input: s = "tree"

Step 1 - Count frequencies:
mpp = {'t':1, 'r':1, 'e':2}

Step 2 - Create vector:
arr = [('t',1), ('r',1), ('e',2)]

Step 3 - Sort by frequency (descending):
arr = [('e',2), ('t',1), ('r',1)] (e has highest frequency)

Step 4 - Build result:
result = "ee" + "t" + "r" = "eetr"

Output: "eetr" or "eert" (order of same frequency characters may vary)

Example 2:
Input: s = "cccaabb"

Step 1 - Count:
mpp = {'c':3, 'a':2, 'b':2}

Step 2 - Vector:
arr = [('c',3), ('a',2), ('b',2)]

Step 3 - Sort:
arr = [('c',3), ('a',2), ('b',2)]

Step 4 - Build:
result = "ccc" + "aa" + "bb" = "cccaabb"

Output: "cccaabb" (or "cccbbaa" - same frequency order doesn't matter)

Edge Cases:
- Single character: returns that character
- All same frequency: can return in any order
- All unique: can return in any order
- Empty string: returns empty

String Constructor Trick:
- string(5, 'a') creates "aaaaa"
- Very efficient for repeating characters
- Better than loop: for(int i=0; i<5; i++) result += 'a';

Comparator Explanation:
- Lambda: [](auto &a, auto &b) { return a.second > b.second; }
- a and b are pairs<char, int>
- a.first = character, a.second = frequency
- Return true if a's frequency > b's frequency
- Sorts in descending order

Alternative Approaches:
1. Min Heap: Store all chars, pop in order (slower)
2. Bucket Sort: Create buckets for each frequency (O(n) time)
3. multiset: Automatically sorted, but slower than vector + sort

Why This Approach:
- Simple and straightforward
- HashMap for O(1) frequency lookup
- Sorting is efficient for small k (unique chars)
- Easy to understand and implement
*/