// LeetCode 1855: Maximum Distance Between a Pair of Values
// Problem: Find maximum distance between indices where nums1[i] <= nums2[j] and i < j
// Approach: Two Pointers from the beginning

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int maxi = 0;
        int i = 0, j = 0;

        while(i < m && j < n) {
            if(nums1[i] <= nums2[j]) {
                // Valid pair found, update max distance
                maxi = max(maxi, j - i);
                j++;  // Try to find larger j for greater distance
            }
            else {
                // nums1[i] > nums2[j], need to move i to find smaller value
                i++;
            }
        }

        return maxi;
    }
};

/*
Time Complexity: O(m + n)
- Each pointer moves through its array at most once
- Total iterations: at most m + n

Space Complexity: O(1)
- Only using constant extra space

Constraints:
- Both arrays are non-decreasing (sorted)
- Need to find indices i and j such that nums1[i] <= nums2[j] and i < j

Algorithm:
1. Start with two pointers: i at start of nums1, j at start of nums2
2. If nums1[i] <= nums2[j]:
   - Valid pair found, distance = j - i
   - Update maximum distance
   - Move j forward to find potentially larger distance (j++)
3. If nums1[i] > nums2[j]:
   - Current pair is invalid
   - Move i forward to find smaller value (i++)
4. Continue until one pointer reaches end
5. Return maximum distance found

Example 1:
Input: nums1 = [55,1,100], nums2 = [1,1,1,1]
Output: 2

Explanation:
- i=0, j=0: nums1[0]=55 > nums2[0]=1 → i++
- i=1, j=0: nums1[1]=1 <= nums2[0]=1 → maxi=0-1=-1 (invalid, keep 0), j++
- i=1, j=1: nums1[1]=1 <= nums2[1]=1 → maxi=1-1=0, j++
- i=1, j=2: nums1[1]=1 <= nums2[2]=1 → maxi=2-1=1, j++
- i=1, j=3: nums1[1]=1 <= nums2[3]=1 → maxi=3-1=2, j++
- j reached end
- Return 2

Example 2:
Input: nums1 = [1,2,3,4], nums2 = [1,2,3,4]
Output: 0

Explanation:
- Both arrays are identical
- i < j constraint can't be satisfied
- Distance stays 0
- Return 0

Example 3:
Input: nums1 = [4,5], nums2 = [1,2,3,4]
Output: 0

Explanation:
- i=0, j=0: nums1[0]=4 > nums2[0]=1 → i++
- i=1, j=0: nums1[1]=5 > nums2[0]=1 → i++
- i reached end
- Return 0

Why Two Pointers Work:
- Since both arrays are sorted:
  - If nums1[i] > nums2[j], we need smaller nums1 value, so move i forward
  - If nums1[i] <= nums2[j], we have valid pair, try to maximize distance by moving j forward
- Each comparison helps us eliminate impossible combinations
- At most m + n iterations needed
*/
