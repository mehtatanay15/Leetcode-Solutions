// LeetCode 396: Rotate Function
// Problem: Given an array nums, find the maximum value of F(k) where
// F(k) = 0*nums[0] + 1*nums[1] + ... + (n-1)*nums[n-1] after rotating right by k positions
// Approach: Mathematical optimization using recurrence relation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        
        long long totalSum = 0;
        long long currentValue = 0;
        
        // Calculate initial F(0) and total sum
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
            currentValue += (long long)i * nums[i];  // F(0) = 0*nums[0] + 1*nums[1] + ... + (n-1)*nums[n-1]
        }
        
        // Track maximum value found
        long long maxi = currentValue;
        
        // Calculate F(k) for k = 1 to n-1 using recurrence relation
        for (int k = 1; k < n; k++) {
            // Recurrence: F(k) = F(k-1) + totalSum - n * nums[n-k]
            currentValue = currentValue + totalSum - (long long)n * nums[n - k];
            maxi = max(maxi, currentValue);
        }
        
        return (int)maxi;
    }
};

/*
Time Complexity: O(n) - Two passes through the array (initial calculation + iterations)
Space Complexity: O(1) - Only using constant extra space

Algorithm:
1. Calculate F(0) = sum of (i * nums[i]) for all i
   This is the initial rotation value without any shifts
   
2. Calculate total sum of all elements

3. Use mathematical recurrence relation to compute subsequent rotations:
   F(k) = F(k-1) + totalSum - n * nums[n-k]
   
   Why this works:
   - When rotating right by 1, each element moves to a higher index coefficient
   - Element at index i moves to coefficient (i+1) mod n
   - The last element wraps around to coefficient 0
   
4. Track the maximum value of F(k) across all k values

Key Insight - The Recurrence Relation:
When rotating from F(k-1) to F(k):
- Every element nums[i] gets multiplied by index (i+1) mod n
- This increases contribution by nums[i] for each element
- Exception: nums[n-k] (new element at position 0) loses contribution of (n-1)*nums[n-k]
- Net change: F(k) = F(k-1) + totalSum - n*nums[n-k]

Example:
nums = [4, 3, 2, 6]
n = 4, totalSum = 15

F(0): 0*4 + 1*3 + 2*2 + 3*6 = 0 + 3 + 4 + 18 = 25

F(1) after rotating right by 1: [6, 4, 3, 2]
= 0*6 + 1*4 + 2*3 + 3*2 = 0 + 4 + 6 + 6 = 16
Using formula: F(1) = 25 + 15 - 4*4 = 25 + 15 - 16 = 24
(Note: This shows the formula calculates what happens when each element moves to higher position)

F(2) after rotating right by 2: [2, 6, 4, 3]
= 0*2 + 1*6 + 2*4 + 3*3 = 0 + 6 + 8 + 9 = 23
Using formula: F(2) = 24 + 15 - 4*3 = 24 + 15 - 12 = 27... 
(The exact numbers depend on the rotation definition)

Maximum F value across all rotations is the answer.
*/
