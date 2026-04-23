// LeetCode 1482: Minimum Number of Days to Make m Bouquets
// Problem: Find minimum days to make m bouquets with k consecutive flowers each
// Approach: Binary Search on day with greedy bouquet checking

class Solution {
public:

    int totalB(vector<int> &temp, int day, int k)
{
    int count = 0;           // Count of consecutive bloomed flowers
    int bouquets = 0;        // Total bouquets made

    for(int i = 0; i < temp.size(); i++)
    {
        // Check if flower i has bloomed by this day
        if(temp[i] <= day)  
        {
            count++;         // One more consecutive flower
            if(count == k)   // Have k consecutive flowers?
            {
                bouquets++;  // Make one bouquet
                count = 0;   // Reset counter for next bouquet
            }
        }
        else
        {
            count = 0;       // Streak broken, reset
        }
    }

    return bouquets;  // Total bouquets made by this day
}
    
    int minDays(vector<int>& bloomDay, int m, int k) {
       int n = bloomDay.size();
       
       // Early termination: if not enough flowers
       if(n < m * k) return -1;

        int maxi = -1;  // Maximum bloom day

        // Find the maximum bloom day
        for(int i =0; i<n; i++)
        {
             if(bloomDay[i]> maxi)
             {
                maxi = bloomDay[i];
             }
        }  

        // Binary search on day
        int low = 1;
        int high = maxi;
        int ans = -1;

        while(low<=high)
        {
            int mid = (low + high)/2;

            // Check how many bouquets we can make by day 'mid'
            int totalbouqet = totalB(bloomDay, mid, k);

            if(totalbouqet>=m)  // Can make m bouquets?
            {
                ans = mid;      // This day works, try earlier
                high = mid - 1;
            }
            else{               // Not enough bouquets
                low = mid +1;   // Need more days
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n log m)
- n: size of bloomDay array
- m: maximum bloom day (search space)
- Binary search: O(log m) iterations
- Each iteration calls totalB: O(n) to count bouquets
- Total: O(n log m)

Space Complexity: O(1)
- Only constant extra space

Algorithm (Binary Search on Day):
1. Early check: if n < m*k, impossible (need m*k consecutive flowers minimum)
2. Find range:
   a. Minimum day: 1
   b. Maximum day: max(bloomDay)
3. Binary search on day:
   a. For each mid day, count how many bouquets possible
   b. Use totalB() to greedily count bouquets by checking consecutive bloomed flowers
   c. If bouquets >= m:
      - This day works, try earlier (high = mid - 1)
   d. Else:
      - Not enough bouquets, need more days (low = mid + 1)
4. Return minimum valid day

Key Insight - Greedy Counting:
- To maximize bouquets, pick consecutive bloomed flowers greedily
- Process flowers left-to-right
- When we have k consecutive bloomed flowers, immediately make bouquet
- This greedy approach is optimal

Monotonic Property:
- As day increases, more flowers bloom
- More bouquets possible (monotonic increase)
- If m bouquets achievable by day d, also achievable by day d'
- Binary search finds minimum day

Bouquet Requirements:
- Need exactly k consecutive flowers from array
- Flowers must be adjacent in array (not value)
- Once k consecutive flowers picked, start fresh count
- Any bloomed flower can be picked (bloomDay[i] <= day)

Example 1:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1

Need: 3 bouquets with 1 flower each
Flowers bloom on: day 1, day 2, day 3, day 10, day 10

Bounds: low=1, high=10

Day 1: only flower 0 bloomed -> 1 bouquet
Day 2: flowers 0,4 bloomed (indices) -> 1 bouquet (index 0)
Day 3: flowers 0,2,4 bloomed -> 1 bouquet (index 0)
Day 10: all bloomed -> can make 5 bouquets (but only need 3)

Actually with k=1, need 3 non-consecutive flowers
- Day 1: flower[0] -> 1 bouquet
- Day 2: flower[0]=bloomed, flower[4]=bloomed
  Using greedy: index 0 (bloomed) -> 1 bouquet
               index 4 (bloomed) -> 1 bouquet
  Total: 2 bouquets
- Day 3: flowers 0,2,4 all bloomed
  Index 0 -> bouquet, index 2 -> bouquet, index 4 -> bouquet
  Total: 3 bouquets ✓

Binary search:
low=1, high=10
mid=5
totalB([1,10,3,10,2], 5, 1):
- Flowers bloomed by day 5: indices 0,2,4
- Using greedy: make bouquets at indices 0,2,4
- Result: 3 bouquets
3 >= 3? Yes, ans=5, high=4

mid=2
totalB([1,10,3,10,2], 2, 1):
- Bloomed: indices 0,4
- Bouquets: at 0, at 4
- Result: 2
2 >= 3? No, low=3

mid=3
totalB([1,10,3,10,2], 3, 1):
- Bloomed: indices 0,2,4
- Bouquets: at 0, at 2, at 4
- Result: 3
3 >= 3? Yes, ans=3, high=2

low > high, return ans=3

Output: 3

Example 2:
Input: bloomDay = [1,10,3,10,2], m = 2, k = 2

Need: 2 bouquets with 2 consecutive flowers each

Day 1: only flower 0 -> can't make bouquet (need 2 consecutive)
Day 2: flowers at 0,4 (not consecutive) -> can't make bouquet
Day 3: flowers at 0,2,4
  Consecutive pairs: none (0 is alone, 2 is alone, 4 is alone)
  Result: 0 bouquets
Day 10: all bloomed
  Consecutive bloomed: all 5
  Count k=2: at indices 0-1 -> bouquet, 2-3 -> bouquet, 4 remains
  Result: 2 bouquets ✓

Actually let me retrace day 10:
Flowers: [bloomed, bloomed, bloomed, bloomed, bloomed]
count=0
i=0: bloomed, count=1
i=1: bloomed, count=2 -> bouquet, count=0
i=2: bloomed, count=1
i=3: bloomed, count=2 -> bouquet, count=0
i=4: bloomed, count=1
Result: 2 bouquets ✓

Example 3:
Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3

Need: 2 bouquets with 3 consecutive flowers each

Day 7: indices 0,1,2,3,5,6 bloomed
  Index 0: bloomed, count=1
  Index 1: bloomed, count=2
  Index 2: bloomed, count=3 -> bouquet, count=0
  Index 3: bloomed, count=1
  Index 4: not bloomed, count=0
  Index 5: bloomed, count=1
  Index 6: bloomed, count=2
  Result: 1 bouquet (only index 5-6 left, need 3)

Day 12: all bloomed
  Index 0: bloomed, count=1
  Index 1: bloomed, count=2
  Index 2: bloomed, count=3 -> bouquet, count=0
  Index 3: bloomed, count=1
  Index 4: bloomed, count=2
  Index 5: bloomed, count=3 -> bouquet, count=0
  Index 6: bloomed, count=1
  Result: 2 bouquets ✓

Binary search finds minimum day = 12

Edge Cases:
- Not enough flowers: return -1 (if n < m*k)
- k = n and m = 1: need all flowers to bloom
- All flowers bloom same day: answer is that day
- k = 1: can pick any flower, answer = median or close to it

Greedy Optimality Proof:
- Taking k consecutive bloomed flowers greedily (left to right)
- Any alternative strategy would leave smaller gaps
- Or result in fewer total bouquets
- Greedy is optimal for this problem

Why Order Matters in Greedy:
- Flowers must be consecutive in array (adjacent positions)
- Cannot skip flowers to make different bouquets
- Greedy left-to-right ensures maximum bouquets

Conversely, Why Not Linear Search:
- Would be O(n * max_day) - too slow
- Binary search is O(n * log max_day) - much better
- For large max_day, exponential difference

Problem Constraints Help:
- Early termination check: n < m*k -> impossible
- Bounds clear: [1, max(bloomDay)]
- Solution guaranteed if possible

*/
