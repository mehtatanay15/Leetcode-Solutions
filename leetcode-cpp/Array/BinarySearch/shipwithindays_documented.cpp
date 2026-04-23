// LeetCode 1011: Capacity To Ship Packages Within D Days
// Problem: Find minimum capacity to ship all packages within D days
// Approach: Binary Search on capacity with feasibility check

class Solution {
public:
    int calcidays(vector<int> &temp, int capacity){
        int w =0;        // Current day's weight
        int day = 1;     // Day counter
        
        for(int i =0; i< temp.size();i++)
        {   
            // Check if adding this package exceeds capacity
            if(w + temp[i] <= capacity)
            {
               w+= temp[i];  // Add to current day
            }
            else{
                day++;        // Start new day
                w = temp[i];  // Put package on new day
            }
        }
        return day;
    }
    
    int shipWithinDays(vector<int>& weights, int days) {
        int maxi = -1;  // Maximum single package weight
        int sum = 0;    // Total weight of all packages

        // Find min and max capacity needed
        for(int i =0; i< weights.size(); i++)
        {
            sum += weights[i];
            if(weights[i] > maxi)
            {
                maxi = weights[i];
            }
        }

        // Binary search on capacity
        int low = maxi;      // Minimum capacity: can fit largest package
        int high = sum;      // Maximum capacity: fit everything in one day
        int ans = 0;

        while(low<=high)
        {
            int mid = (low + high)/2;

            // Check if we can ship with this capacity in D days
            int no_days = calcidays(weights, mid);

            if(no_days <= days)
            {
                // This capacity works, try smaller
                ans = mid;
                high = mid -1;
            }
            else{
                // This capacity doesn't work, need larger
                low = mid +1;
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n log S)
- n: number of packages
- S: sum of all weights
- Binary search: O(log S) iterations
- Each iteration calls calcidays: O(n) to count days
- Total: O(n log S)

Space Complexity: O(1)
- Only using constant extra space

Algorithm (Binary Search on Capacity):
1. Find capacity bounds:
   a. Minimum: max(weights) - must fit at least the heaviest package
   b. Maximum: sum(weights) - can ship everything in one day
2. Binary search on capacity:
   a. Calculate mid capacity
   b. Use calcidays() to check how many days needed with this capacity
   c. If days_needed <= D:
      - Capacity works, try smaller (high = mid - 1)
      - Update answer
   d. Else:
      - Capacity too small, need larger (low = mid + 1)
3. Return minimum valid capacity

Key Insight - Monotonic Property:
- As capacity increases, days needed decreases (monotonic)
- If we can ship in D days with capacity c, we can also with any c' > c
- If we cannot ship in D days with capacity c, we cannot with any c' < c
- This monotonicity allows binary search
- Find minimum capacity where days_needed <= D

Calcidays Function (Greedy Packing):
- Load packages onto ship day by day
- For each day, load as many packages as possible (greedy)
- When adding next package would exceed capacity, move to next day
- Count total days needed

Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5

Find bounds:
maxi = 10 (largest package)
sum = 55 (total weight)

Binary search: low=10, high=55

Iteration 1: mid=32
calcidays(weights, 32):
- Day 1: 1+2+3+4+5+6+7 = 28 <= 32
- Day 2: 8+9+10 = 27 <= 32
Return day=2

2 <= 5? Yes, ans=32, high=31

Iteration 2: mid=20
calcidays(weights, 20):
- Day 1: 1+2+3+4+5 = 15
- Day 2: 6+7 = 13
- Day 3: 8+9 = 17
- Day 4: 10 = 10
Return day=4

4 <= 5? Yes, ans=20, high=19

Iteration 3: mid=14
calcidays(weights, 14):
- Day 1: 1+2+3+4 = 10
- Day 2: 5+6 = 11
- Day 3: 7 = 7
- Day 4: 8 = 8
- Day 5: 9 = 9
- Day 6: 10 = 10
Return day=6

6 <= 5? No, low=15

Iteration 4: mid=17
calcidays(weights, 17):
- Day 1: 1+2+3+4+5 = 15
- Day 2: 6+7 = 13
- Day 3: 8+9 = 17
- Day 4: 10 = 10
Return day=4

4 <= 5? Yes, ans=17, high=16

Iteration 5: mid=15
calcidays(weights, 15):
- Day 1: 1+2+3+4+5 = 15
- Day 2: 6+7 = 13
- Day 3: 8 = 8
- Day 4: 9 = 9
- Day 5: 10 = 10
Return day=5

5 <= 5? Yes, ans=15, high=14

low > high, return ans=15

Output: 15 (with capacity 15, can ship in 5 days)

Example 2:
Input: weights = [3,2,2,4,1,4], days = 3

Bounds: maxi=4, sum=16
low=4, high=16

Let's check capacity=6:
calcidays([3,2,2,4,1,4], 6):
- 3+2=5<=6, add 2? 7>6 -> Day 1: [3,2] = 5
- Day 2: 2+4=6 <= 6, add 1? 7>6 -> [2,4] = 6
- Day 3: 1+4=5 <= 6 -> [1,4] = 5
Return 3 days

3 <= 3? Yes, ans=6, high=5

Check capacity=4:
calcidays([3,2,2,4,1,4], 4):
- 3<=4, add 2? 5>4 -> Day 1: [3] = 3
- 2+2=4<=4, add 4? 8>4 -> Day 2: [2,2] = 4
- 4<=4, add 1? 5>4 -> Day 3: [4] = 4
- 1+4=5>4 -> Day 4: [1] = 1
- Day 5: [4] = 4
Return 5 days

5 <= 3? No, low=5

low > high, return ans=6

Output: 6

Edge Cases:
- Single package: capacity = that package
- All packages light: capacity = sum / days
- One day limit: capacity = sum
- Many days available: capacity = max element

Greedy Packing Strategy:
- Load each day with maximum possible weight
- This minimizes total days needed
- Optimal local strategy leads to optimal global solution

Monotonic Behavior Visualization:
weights = [3, 2, 2, 4, 1, 4]

Capacity 4: needs 5 days
Capacity 5: needs 4 days
Capacity 6: needs 3 days
Capacity 7: needs 3 days
Capacity 16: needs 1 day

Monotonically decreasing (or staying same)

Binary Search Search Space:
- Left: max(weights) - cannot go lower
- Right: sum(weights) - cannot go higher
- Answer lies in [max, sum]

Why Not Linear Search:
- Would be O(n * sum) - too slow
- Binary search is O(n * log sum) - much better
- For large sums, huge difference

Capacity Bounds Correctness:
- Minimum: We must fit at least the heaviest single package
  * If capacity < max, impossible to ship any day
- Maximum: Ship everything in one day
  * If capacity >= sum, can ship all in 1 day
  * Any capacity >= sum would work
  * But we want minimum, so sum is our upper bound

Alternative Greedy Approach:
Divide sum by days: initial_capacity = ceil(sum / days)
Then check if this works, adjust if needed
But binary search is cleaner and guaranteed correct

This Binary Search on Answer pattern is common for:
- Minimize resource to achieve goal problems
- Capacity problems
- Speed/time problems
- Distance/threshold problems

Optimality:
- Binary search guarantees finding minimum valid answer
- Cannot be solved more efficiently than O(n log max_value)
*/
