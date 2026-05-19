// LeetCode 2540: Minimum Common Value
// Problem: Given two sorted arrays, find the minimum (earliest) common element
// If no common element exists, return -1
// Approach: Two-pointer technique - converge from start of both arrays

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // Two pointers starting from beginning of each array
        int i = 0, j = 0;

        // Move pointers until one array is exhausted
        while (i < n && j < m) {
            if (nums1[i] == nums2[j]) {
                // Found a common element - return immediately
                // Since arrays are sorted, this is the minimum common element
                return nums1[i];
            }

            // Advance the pointer pointing to the smaller element
            if (nums1[i] > nums2[j]) {
                j++;  // nums2[j] is too small, move forward in nums2
            } else {
                i++;  // nums1[i] is too small, move forward in nums1
            }
        }

        // No common element found
        return -1;
    }
};

/*
Time Complexity: O(m + n) where m = len(nums1), n = len(nums2)
  - Each element in both arrays visited at most once
  - Single pass through both arrays with pointers
  - Worst case: one pointer reaches end while other has elements left

Space Complexity: O(1)
  - Only using two pointer variables
  - No extra data structures needed

Algorithm Explanation:

Problem Overview:
Given two sorted arrays nums1 and nums2, find the minimum common value.
A common value is an element that appears in both arrays.
Return the smallest such value, or -1 if no common element exists.

Key Insight - Two-Pointer Convergence:
- Both arrays are sorted (ascending order)
- Start with pointers at beginning of each array
- Compare elements and advance the pointer of the smaller element
- When elements are equal, we found a match
- Since we start from smallest indices and advance systematically,
  the first match we find is the minimum common element

Why Two-Pointer Works:
- If nums1[i] < nums2[j], then nums1[i] cannot equal any element before nums2[j]
  in nums2, because nums2 is sorted and all earlier elements are ≤ nums2[j]
- Therefore, we safely advance i without missing potential matches
- Same logic applies when nums1[i] > nums2[j], advance j

Example 1: nums1 = [1, 2, 3, 6], nums2 = [2, 3, 4, 5]
Initial: i=0, j=0

Iteration 1:
- nums1[0]=1, nums2[0]=2
- 1 < 2 → i++

Iteration 2: i=1, j=0
- nums1[1]=2, nums2[0]=2
- 2 == 2 → return 2 ✓

Example 2: nums1 = [1, 2, 3, 4, 5], nums2 = [6, 7, 8, 9, 10]
Initial: i=0, j=0

Iteration 1:
- nums1[0]=1, nums2[0]=6
- 1 < 6 → i++

Iteration 2: i=1, j=0
- nums1[1]=2, nums2[0]=6
- 2 < 6 → i++

... continue advancing i ...

Eventually i reaches 5 (n), loop exits
- Return -1 ✓ (no common element)

Example 3: nums1 = [1, 3, 5, 7, 9, 11], nums2 = [2, 4, 5, 6, 8, 10]
Initial: i=0, j=0

Iterations:
- nums1[0]=1, nums2[0]=2: 1 < 2 → i++
- nums1[1]=3, nums2[0]=2: 3 > 2 → j++
- nums1[1]=3, nums2[1]=4: 3 < 4 → i++
- nums1[2]=5, nums2[1]=4: 5 > 4 → j++
- nums1[2]=5, nums2[2]=5: 5 == 5 → return 5 ✓

Example 4: nums1 = [5, 6, 7], nums2 = [1, 5, 9]
Initial: i=0, j=0

Iterations:
- nums1[0]=5, nums2[0]=1: 5 > 1 → j++
- nums1[0]=5, nums2[1]=5: 5 == 5 → return 5 ✓

Example 5: nums1 = [1, 2], nums2 = [3, 4]
Initial: i=0, j=0

Iterations:
- nums1[0]=1, nums2[0]=3: 1 < 3 → i++
- nums1[1]=2, nums2[0]=3: 2 < 3 → i++
- i=2, loop exits (i < n is false)
- Return -1 ✓

Edge Cases:
1. Empty arrays: handled by while condition (i < n && j < m)
2. Single element arrays: works correctly
3. Arrays with one common element: returns immediately
4. Arrays with multiple common elements: returns first (minimum)
5. Disjoint arrays: returns -1
6. One array subset of other: works correctly
7. Arrays with duplicates: handles correctly (finds first match)

Why First Match is Minimum:
- Pointers always advance from start (minimum values)
- First match found is guaranteed to be minimum
- Example: [1,2,3,4] and [3,4,5,6]
  * Can't find 1 or 2 in nums2 (too small)
  * When we reach 3, it matches
  * This is indeed the minimum common value

Comparison with Alternative Approaches:

1. Hash Set (Alternative):
   - Time: O(m + n)
   - Space: O(min(m, n))
   - Store one array in set, iterate other
   - Good if arrays very different sizes
   - More space overhead than two-pointer

2. Binary Search (Alternative):
   - Time: O(min(m, n) * log(max(m, n)))
   - Space: O(1)
   - Search each element of smaller array in larger
   - Slower than two-pointer for this problem

3. Two-Pointer (Current):
   - Time: O(m + n)
   - Space: O(1)
   - Optimal for sorted arrays
   - Simple and efficient

Why Two-Pointer is Best Here:
- Given that arrays are sorted, we can leverage this property
- Two-pointer uses sorting to achieve O(n) in linear fashion
- No extra space needed
- Clean and intuitive algorithm

Problem Variants:
- Return all common elements: slight modification, skip advancing both pointers
- Return count of common elements: similar modification
- Return common elements >= threshold: add condition
- Find k-th common element: modify return logic

Correctness Proof:
Claim: The first match found is the minimum common element

Proof:
1. Let x be the value where nums1[i] == nums2[j] at some iteration
2. Assume there exists y < x that is also common
3. Since y < x and arrays are sorted:
   - y must appear before position i in nums1
   - y must appear before position j in nums2
4. By algorithm design, if y were at positions < i and < j,
   we would have encountered it before position (i, j)
5. But we didn't, contradiction
6. Therefore, first match found is indeed the minimum

Time Complexity Detailed:
- Total iterations = at most (m + n)
- Each iteration: O(1) comparison and advance
- In worst case: traverse entire nums1 and entire nums2
- Example worst: [1,2,3,4,5] and [5,6,7,8,9]
  * Advance i five times (1,2,3,4,5)
  * Then compare with 5 (match)
  * Total: 6 operations

Space Complexity:
- i, j pointers: O(1)
- No auxiliary data structures
- Truly constant space solution
*/
