// LeetCode 455: Assign Cookies
// Problem: Assign cookies to children such that each child is maximally satisfied
// Approach: Greedy + Two Pointers (sort both arrays and use two-pointer matching)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int i = 0;  // pointer for children
        int j = 0;  // pointer for cookies
        
        while (i < g.size() && j < s.size()) {
            // if current cookie can satisfy current child
            if (s[j] >= g[i]) {
                i++; // child is satisfied, move to next child
            }
            j++; // move to next cookie regardless
        }
        
        return i; // number of satisfied children
    }
};

/*
Time Complexity: O(n log n + m log m) where n = children, m = cookies
- Sorting both arrays

Space Complexity: O(1) excluding the output

Greedy Strategy:
- Sort both arrays in ascending order
- Use two pointers to greedily match cookies with children
- Try to assign the smallest cookie that can satisfy each child
- This ensures we don't waste larger cookies on children with small requirements

Example:
Input: g = [1,2,3], s = [1,1]
Output: 1

Explanation:
- Child 0 requires greed value 1, Child 1 requires 2, Child 2 requires 3
- Cookie 0 has size 1, Cookie 1 has size 1
- Assign Cookie 0 to Child 0 (1 >= 1) ✓
- Cookie 1 cannot satisfy Child 1 (1 < 2) ✗
- Result: 1 child satisfied

Example 2:
Input: g = [1,2], s = [1,2,3]
Output: 2

Explanation:
- Child 0 requires 1, Child 1 requires 2
- Cookie 0 (size 1) → Child 0 ✓
- Cookie 1 (size 2) → Child 1 ✓
- Result: 2 children satisfied
*/
