// LeetCode 1764: Form Array by Concatenating Subarrays of Another Array
// Problem: Find minimum number of subarrays needed from nums to form target
// Approach: Greedy matching with tracking

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();   
        int minDistance = n;     // Maximum possible distance
        int found = false;       // Whether target was found
        
        for(int i = 0; i < n; i++)
        {
            // Check if current word matches target
            if(words[i] == target)
            {
                found = true;

                // Direct distance (one direction)
                int d = abs(i - startIndex);

                // Circular distance (other direction, wrapping around)
                int circulard = n - d;

                // Take minimum of both directions
                int temp = min(d, circulard);

                // Update overall minimum distance
                minDistance = min(temp, minDistance);
            }
        }

        return found ? minDistance : -1;
    }
};

/*
Time Complexity: O(n * m)
- n: number of words
- m: average length of comparison (string == operator)
- Linear scan through array with string comparison at each step

Space Complexity: O(1)
- Only constant extra space for tracking

Algorithm (Greedy Circular Distance):
1. Find all positions where word equals target string
2. For each matching position:
   a. Calculate direct distance: |i - startIndex|
   b. Calculate circular distance: n - direct
   c. Take minimum of both directions
3. Track overall minimum distance
4. Return minimum, or -1 if target not found

Key Insight - Circular Array:
- Can move in either direction on circular array
- Left wrap distance: (startIndex - i + n) % n
- Right wrap distance: (i - startIndex + n) % n
- Or simpler: direct = min distance, circular = n - direct

Example 1:
Input: words = ["abc","bcd","aaab","caaada","edaada"], target = "aa", start = 0

Target not found (no \"aa\" in words)
Return: -1

Example 2:
Input: words = ["abcd","cddc","aaab","caaada","edaada"], target = \"aaab\", start = 0

Target \"aaab\" found at index 2
Direct distance = |2 - 0| = 2 (go right: 0->1->2)
Circular distance = 5 - 2 = 3 (go left: 0->4->3->2)
Minimum = 2

Return: 2

Example 3:
Input: words = [\"a\",\"b\",\"c\"], target = \"c\", start = 0

Target \"c\" at index 2
Direct = |2-0| = 2
Circular = 3 - 2 = 1 (0 -> 2 wrapping backward)
Minimum = 1

Return: 1

Example 4:
Input: words = [\"a\",\"b\",\"c\",\"d\",\"a\"], target = \"a\", start = 1

Target \"a\" at indices 0 and 4

At index 0:
Direct = |0-1| = 1 (distance left)
Circular = 5-1 = 4 (distance right)
Min = 1

At index 4:
Direct = |4-1| = 3 (distance right)
Circular = 5-3 = 2 (distance left wrapping)
Min = 2

Overall minimum = 1 (position 0)

Return: 1

Circular Array Visualization:
Array: [0, 1, 2, 3, 4] (n=5)
Circular: 0<->1<->2<->3<->4<->0...

From position 1:
- To 0 (direct): distance 1 (left)
- To 0 (circular): distance 5-1=4 (right)

- To 4 (direct): distance 3 (right)
- To 4 (circular): distance 5-3=2 (left wrapping)

Edge Cases:
- Target at start position: distance = 0
- Target not in array: return -1
- Single element that matches: distance = 0
- Multiple occurrences: find minimum of all

Why Both Directions:
- Array is circular (can wrap around)
- Must check both clockwise and counter-clockwise
- Whichever is shorter is the answer

Circular Distance Formula:
- Direct: |i - start|
- Circular: n - direct
- Always: direct + circular = n

Optimization Opportunity:
- Once minDistance = 1, can return early (can't do better)
- But need to check all positions for global minimum

String Comparison:
- words[i] == target compares full strings
- O(m) where m is string length
- Done n times for O(nm) total

Alternative with Early Termination:
int closestTarget(vector<string>& words, string target, int startIndex) {
    int n = words.size();
    int minDistance = n;
    for(int i = 0; i < n; i++) {
        if(words[i] == target) {
            int d = abs(i - startIndex);
            int circulard = n - d;
            minDistance = min(minDistance, min(d, circulard));
            if(minDistance == 1) return 1;  // Can't be better
        }
    }
    return minDistance == n ? -1 : minDistance;
}

Related Concepts:
- Circular array problems
- Minimum distance/search
- Two-direction exploration

When To Use:
- Circular array distance problems
- Word matching in sequences
- Minimum resource allocation in round-robin

*/
