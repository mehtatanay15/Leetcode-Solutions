// LeetCode 2190: Most Frequent Number Following Zero
// Problem: Find most frequent number that comes immediately after zero in array
// Approach: Single pass with HashMap and tracking

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int ans = INT_MAX;      // Initialize to max value\n        int n = nums.size();
        
        // Linear scan through array
        for(int i = 0; i < n ; i++)
        {\n            // Find positions where target appears
            if(target == nums[i])
            {
                // Calculate distance from start position
                int temp = abs(i - start);
                
                // Update minimum distance
                if(temp < ans)
                {
                    ans = temp;
                }
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n)
- Single pass through array
- n: size of nums array

Space Complexity: O(1)
- Only constant extra space

Algorithm (Linear Scan):
1. Initialize ans to INT_MAX (largest possible value)
2. For each index i in array:
   a. Check if nums[i] == target
   b. If yes, calculate distance = |i - start|
   c. Update ans = min(ans, distance)
3. Return final ans

Key Insight - Distance is Absolute:
- Distance from start to i: |i - start|
- Works in both directions (left and right)
- No need to distinguish between left/right

Example 1:
Input: nums = [1,3,1,2,4,2], target = 2, start = 0

Positions of target=2: indices 3, 5
Distance from start=0:
- To index 3: |3-0| = 3
- To index 5: |5-0| = 5
Minimum: 3

Trace:
i=0: nums[0]=1, not target
i=1: nums[1]=3, not target
i=2: nums[2]=1, not target
i=3: nums[3]=2, matches! distance=|3-0|=3, ans=3
i=4: nums[4]=4, not target
i=5: nums[5]=2, matches! distance=|5-0|=5, ans=min(3,5)=3

Return: 3

Example 2:
Input: nums = [1], target = 1, start = 0

Only one element at index 0
nums[0]=1 == target
distance = |0-0| = 0
ans = 0

Return: 0

Example 3:
Input: nums = [1,1,1,1], target = 1, start = 3

All elements are 1
i=0: distance=|0-3|=3
i=1: distance=|1-3|=2, ans=2
i=2: distance=|2-3|=1, ans=1
i=3: distance=|3-3|=0, ans=0

Return: 0

Edge Cases:
- Single element that matches: return 0
- Target not in array: handled by INT_MAX (should return -1 or error if required)
- Start at target location: distance = 0
- Target at beginning: distance = start
- Target at end: distance = n-1-start

Absolute Value:
- |i - start| handles both:
  * i > start: i - start (right side)
  * i < start: start - i (left side)
  * i == start: 0 (same position)
- All cases covered with one formula

Why Not Pre-process:
- Could store positions of target in a set
- But linear scan is already O(n), simple enough
- HashMap would add O(n) extra space

When Target Doesn't Exist:
- ans stays INT_MAX
- Should check if ans == INT_MAX before returning (depends on problem)
- Problem likely guarantees target exists

Optimization for Large Gaps:
- Early return if distance becomes 0 (best possible)
- Scan from start position outward in both directions
- But gains minimal for typical array sizes

Two-pointer Approach (alternative):
vector<int> positions;
for(int i = 0; i < nums.size(); i++) {
    if(nums[i] == target) {
        positions.push_back(i);
    }
}
int minDist = INT_MAX;
for(int pos : positions) {
    minDist = min(minDist, abs(pos - start));
}
return minDist;

Less efficient (two passes) but clear separation of concerns

Simplification:
int getMinDistance(vector<int>& nums, int target, int start) {
    int minDist = INT_MAX;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] == target) {
            minDist = min(minDist, abs(i - start));
        }
    }
    return minDist;
}

Even more concise, same O(n), O(1)

Why This Problem:
- Tests understanding of:
  * Linear array iteration
  * Absolute value/distance
  * Minimum tracking
- Simple but important building block

Related Problems:
- K closest elements
- Closest binary search value
- Closest sum to target

*/
