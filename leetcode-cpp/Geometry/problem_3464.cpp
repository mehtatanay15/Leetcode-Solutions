// LeetCode 3464: Maximize Distance From Origin on Square Perimeter
// Problem: Given k points on the perimeter of a square, find the maximum possible
// minimum distance between any two consecutive selected points (circular order)
// Approach: Binary Search + Greedy Validation on Unrolled Perimeter

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<long long> d(n);

        // Step 1: Unroll the square into 1D (Clockwise Perimeter Distance)
        // Map each point to its distance along the perimeter starting from bottom-left (0,0)
        for (int i = 0; i < n; ++i) {
            long long x = points[i][0], y = points[i][1];
            if (y == 0) d[i] = x;                       // Bottom edge: 0 to side
            else if (x == side) d[i] = side + y;        // Right edge: side to 2*side
            else if (y == side) d[i] = 3LL * side - x;  // Top edge: 2*side to 3*side
            else d[i] = 4LL * side - y;                 // Left edge: 3*side to 4*side
        }
        sort(d.begin(), d.end());

        // Step 2: Binary Search for the maximum possible minimum distance
        int low = 0, high = side; 
        int ans = 0;

        auto check = [&](int mid) {
            // Try starting from every point as the first selected point
            for (int i = 0; i < n; ++i) {
                int count = 1;
                long long last = d[i];
                
                // Greedily select the next k-1 points, each at least 'mid' distance away
                for (int j = 1; j < k; ++j) {
                    // Find next point at least 'mid' distance away (in sorted order)
                    auto it = lower_bound(d.begin(), d.end(), last + mid);
                    if (it == d.end()) break;  // No point found, can't complete selection
                    
                    last = *it;
                    count++;
                }
                
                // Check if we selected k points AND circular distance constraint is satisfied
                // The distance from the last selected point back to the first point must also be >= mid
                if (count == k && (4LL * side - (last - d[i])) >= mid) {
                    return true;
                }
            }
            return false;
        };

        // Binary search on the answer
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;  // Try larger distance
            } else {
                high = mid - 1;  // Try smaller distance
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n * log(n) * log(side) * n) = O(n² * log(n) * log(side))
- Sorting: O(n log n)
- Binary search on answer: O(log(side))
- For each binary search iteration:
  - check() tries n starting points
  - Each starting point does at most n lower_bound searches
  - Each lower_bound: O(log n)
Space Complexity: O(n) - for storing perimeter distances

Algorithm:
1. Convert 2D square perimeter into 1D by unrolling it clockwise
   - Each point is mapped to its distance along the perimeter
2. Sort these distances
3. Binary search on the minimum distance between consecutive selected points
4. For each candidate distance, use greedy approach:
   - Try every point as the first selected point
   - Greedily pick the next closest point that is at least 'mid' distance away
   - Verify we can select k points with the circular distance constraint
5. Return the maximum valid minimum distance

Key Insight:
- By unrolling the 2D perimeter to 1D, we can use binary search + greedy
- For each starting point, we greedily select the nearest point that satisfies
  the minimum distance constraint
- The circular distance from last point back to first is checked using:
  (4 * side - (last - first)) because wrapping around the perimeter

Example:
- Square with side=8, k=2, points: [[0,0], [4,0], [8,4], [0,8]]
- Perimeter distances: [0, 4, 12, 24]
- If mid=8: Starting at 0, next point must be >= 8
  - Next point at 12 (distance=12, valid)
  - Wrap distance: 4*8 - (12-0) = 32-12 = 20 >= 8 ✓
- Result: Can achieve minimum distance of 8 or more
*/
