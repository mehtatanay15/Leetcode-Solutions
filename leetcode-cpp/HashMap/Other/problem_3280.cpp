// LeetCode 3280: Minimum Mirror Pair Distance
// Problem: Find minimum distance between an element and its mirror (reverse) in the array
// Approach: HashMap + Number Reversal

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reverseNum(int n) {
        int rev = 0;
        while(n > 0) {
            rev = rev * 10 + (n % 10);
            n /= 10;
        }
        return rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;
        unordered_map<int, int> mpp;

        for(int i = 0; i < n; i++) {
            // Check if reverse of current number exists in map
            if(mpp.count(nums[i])) {
                ans = min(ans, i - mpp[nums[i]]);
            }

            // Store the index of reversed current number
            mpp[reverseNum(nums[i])] = i;
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};

/*
Time Complexity: O(n * d) where d is the number of digits in each number
Space Complexity: O(n) for the hash map

Algorithm:
1. For each element, reverse it and check if it exists in the map
2. If it exists, calculate the distance and update minimum
3. Store the index of current number's reverse in the map
4. Return the minimum distance found, or -1 if no pair exists

Example:
Input: nums = [10,100,1,10,100]
Output: 0

Explanation:
- At index 0: 10, reverse = 01 = 1, store {01: 0} → {1: 0}
- At index 1: 100, reverse = 001 = 1, store {001: 1} → {1: 1}
- At index 2: 1, reverse = 1, found in map at index 1, distance = 2-1 = 1
- At index 3: 10, reverse = 01 = 1, found in map at index 2, distance = 3-2 = 1
- At index 4: 100, reverse = 001 = 1, found in map at index 3, distance = 4-3 = 1
- Minimum distance = 0 (or closest pair)
*/
