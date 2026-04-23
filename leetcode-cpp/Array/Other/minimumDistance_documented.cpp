// LeetCode 1891: Cutting Ribbons
// Problem: Find maximum length k such that we can cut m pieces of length k from all ribbons
// Approach: Binary Search on ribbon length with cutting simulation

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        // Initialize mindist to very large value
        int mindist = INT_MAX; 
        
        // Map each unique number to its indices
        unordered_map<int, vector<int>> mpp;
        
        for(int i = 0; i < nums.size(); i++){
            mpp[nums[i]].push_back(i);
        }
        
        // For each unique value, find minimum distance to remove 3 occurrences
        for(auto& it : mpp){
            vector<int>& ans = it.second;  // Indices where this value appears
            
            // Need at least 3 occurrences to cut out
            if(ans.size() < 3) continue;

            // Sliding window of size 3
            int l = 0;
            for(int r = 0; r < ans.size(); r++){
                if(r - l + 1 > 3) l++;  // Maintain window size of 3
                
                if(r - l + 1 == 3){
                    // Cut out indices from ans[l] to ans[r]
                    // Cost = 2 * distance between first and last
                    int dist = 2 * (ans[r] - ans[l]);
                    mindist = min(dist, mindist); 
                }
            }
        }
        
        // If no valid cut found, return -1
        return (mindist == INT_MAX) ? -1 : mindist;
    }
};

/*
Time Complexity: O(n)
- First pass to group indices: O(n)
- For each value, sliding window pass: O(k) where k is count of that value
- Sum of all counts = n, so total O(n)

Space Complexity: O(n)
- HashMap stores all indices: O(n)

Algorithm (Greedy Sliding Window):
1. Build HashMap: value -> list of indices
2. For each unique value with at least 3 occurrences:
   a. Use sliding window of size 3 on indices
   b. For each window, calculate cost = 2 * (last_index - first_index)
   c. Track minimum cost
3. Return minimum cost, or -1 if impossible

Key Insight - Cost Calculation:
- To cut out 3 occurrences at indices i, j, k:
  * Remove elements at i and k
  * Cost = distance between them
  * Distance = k - i
  * But elements on both sides, so cost = 2 * (k - i)
  * For both left and right remainder

Cutting Example:
Array: [1, 0, 1, 0, 1]
Indices: [0, 1, 2, 3, 4]

Value 1 at indices: [0, 2, 4]
Cut out indices 0, 2, 4:
- Left part: [] (index < 0)
- Middle part: [0, 1, 1] (indices 0,1,2)
- Right part: [0] (index > 4)
- Cost = 2 * (4 - 0) = 8

Wait, let me reconsider. The problem is about cutting array to remove specific elements.

If we want to remove elements at indices [0, 2, 4]:
- Option 1: Remove all three separately
  - Remove index 0: array becomes [0,1,0,1]
  - Remove index 1 (was 2): array becomes [0,1,1]
  - Remove index 1 (was 4): array becomes [0,1]
  - Total cuts: 3
  
- Option 2: Cut strategically
  - This is optimization problem
  - Remove [0, 2, 4] with minimum cuts

The cost formula: 2 * (index_last - index_first)
Suggests we need to consider indices as the boundaries.

Example: nums = [4,3,2,2,3,1]
Value 2 at indices [2, 3]
Only 2 occurrences, need 3 (skip)

Value 3 at indices [1, 4]
Only 2 occurrences, need 3 (skip)

No valid triplet, return -1

Better Example: nums = [1,2,1,2,1,2]
Value 1 at indices [0, 2, 4]
Cost = 2 * (4 - 0) = 8

Value 2 at indices [1, 3, 5]
Cost = 2 * (5 - 1) = 8

Minimum = 8

Sliding Window Logic:
- For each value, we have multiple indices
- We want to select 3 indices (i, j, k) where i < j < k
- We want to minimize cost = 2 * (k - i)
- Best strategy: take indices as close together as possible
- Sliding window finds all consecutive triplets

Example: Value appears at indices [1, 5, 9, 15, 20]
Windows of 3:
- [1, 5, 9]: cost = 2*(9-1) = 16
- [5, 9, 15]: cost = 2*(15-5) = 20
- [9, 15, 20]: cost = 2*(20-9) = 22

Minimum = 16 (first window)

Why Sliding Window Works:
- All values in window are sorted (indices are in order)
- Smallest window gives smallest cost
- For each starting position, advance right to find minimum
- This finds the optimal triplet

Edge Cases:
- No value appears 3+ times: return -1
- Exactly 3 occurrences: 1 window, return 2*(last-first)
- Large array: sliding window is efficient

Monotonic Property:
- As window grows (moving right), cost generally increases or stays same
- As window shifts right, leftmost index increases
- For fixed window size 3, cost = 2*(right - left)
- Smaller left and larger right means smaller cost? No.
- Smaller (right - left) is better, so minimize window span

That's why we use sliding window of fixed size 3.

Alternative Approach (Brute Force):
- For each value with 3+ occurrences
- Try all combinations of 3 indices
- Pick minimum cost
- Time: O(n^3) worst case, very slow

Why Sliding Window is Better:
- Fixed window of size 3
- Single pass through indices
- O(n) time, linear efficiency

Related Problem Concepts:
- Cutting/partitioning arrays
- Removal cost optimization
- Index-based distance problems

*/
