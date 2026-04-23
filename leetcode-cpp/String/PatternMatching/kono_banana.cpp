// LeetCode 875: Koko Eating Bananas
// Problem: Find minimum eating speed k such that Koko finishes all piles within h hours
// Approach: Binary Search on eating speed with feasibility check

class Solution {
public:

    long long reqTime ( vector<int> &temp , int hr)
        {
            // Calculate total hours needed to eat all piles at speed 'hr'
            long long totalhr = 0;
            for(int i = 0; i<temp.size(); i++)
            {
                // Time to eat pile i at speed hr = ceil(pile[i] / hr)
                totalhr += ceil((double)temp[i]/(double)hr);
            }
            return totalhr;
        }

    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();

        int maxi = -1;  // Maximum pile size

        // Find largest pile
        for(int i =0; i<n; i++)
        {
             if(piles[i]> maxi)
             {
                maxi = piles[i];
             }
        }

        // Binary search on eating speed
        // Minimum speed: 1 banana/hour
        // Maximum speed: largest pile (can finish in 1 hour)
        int low = 1;
        int high = maxi;
        int ans = 0;

        while(low<=high)
        {
            int mid = (low + high)/2;

            // Check if we can finish within h hours at speed mid
            long long totalhr = reqTime(piles,mid);

            if(totalhr<=h)
            {
                // This speed works, try slower
                ans = mid;
                high = mid - 1;
            }
            else{
                // This speed doesn't work, need faster
                low = mid +1;
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n log m)
- n: number of piles
- m: maximum pile size (size of search space)
- Binary search: O(log m) iterations
- Each iteration checks time via reqTime: O(n)
- Total: O(n log m)

Space Complexity: O(1)
- Only constant extra space

Algorithm (Binary Search on Eating Speed):
1. Find speed bounds:
   a. Minimum: 1 banana/hour
   b. Maximum: max(piles) - can finish largest pile in 1 hour
2. Binary search on speed:
   a. Calculate mid speed
   b. Use reqTime() to check total hours needed at this speed
   c. If total_hours <= h:
      - Speed works, try slower (high = mid - 1)
      - Update answer
   d. Else:
      - Speed too slow, need faster (low = mid + 1)
3. Return minimum valid speed

Key Insight - Monotonic Property:
- As eating speed increases, time decreases (monotonic)
- If speed k finishes in <= h hours, any speed > k also works
- If speed k doesn't finish in h hours, any speed < k also fails
- This monotonicity enables binary search

Constraint Analysis:
- Must eat from exactly one pile per hour
- Can only eat from next pile after finishing current one
- If pile[i] = 800 and speed = 1, takes 800 hours
- If pile[i] = 800 and speed = 1000, takes ceil(800/1000) = 1 hour

Example 1:
Input: piles = [1,1,1,1], h = 4

Bounds: low=1, high=1
mid=1
reqTime([1,1,1,1], 1) = 1+1+1+1 = 4
4 <= 4? Yes, ans=1, high=0
low > high, return 1

Output: 1 (eat 1 banana/hour, takes exactly 4 hours)

Example 2:
Input: piles = [312884132], h = 968709470

Bounds: low=1, high=312884132
Since h is very large and only 1 pile:
reqTime([312884132], 1) = ceil(312884132/1) = 312884132
312884132 <= 968709470? Yes, ans=1

Output: 1 (even at slowest speed finishes in time)

Example 3:
Input: piles = [1,1,1,1], h = 2

Bounds: low=1, high=1
mid=1
reqTime = 4
4 <= 2? No, low=2
low > high, return ans (should have set earlier)

Actually need to recheck:
Bounds: low=1, high=1
Only one iteration, if it fails, need higher
But high=1 already, so answer must be > 1

Wait, if piles = [1,1,1,1] and h=2:
Eating speed 2: pile 1 takes ceil(1/2)=1 hour, pile 2 takes 1 hour -> 2 hours total
So ans=2

But code starts with high=max(piles)=1
When low=1, high=1, mid=1, reqTime=4
4 <= 2? No, low=2
Now low > high, but haven't found answer!

Actually the constraint is that total pile <= m*h
If not satisfied, no solution exists (but problem guarantees solution)

Correct Example 3:
Input: piles = [1,1,1,1], h = 2
Sum = 4, need 2 hours
Speed needed = ceil(4/2) = 2

With binary search:
low=1, high=1
This won't work! We need high >= 2

Actually problem constraint ensures m*h >= sum(piles)
So maximum speed ever needed is ceil(sum/m) at most
But practical implementation sets high=max(piles)
If answer > max(piles), problem has no solution
But problem guarantees solution exists

Let me redo:
Input: piles = [1,1,1,1], h = 2
low=1, high=1

But wait, with max piles value 1, if speed is 1:
Total hours = 4
4 <= 2? No

So answer must be >= 2
But our high is 1!

This means the bounds assumption is wrong.
Actually, we need to ensure m*h >= sum(piles)
If not, no valid answer

In this case, min valid speed = ceil(sum(piles) / h) = ceil(4/2) = 2
But it's outside our search range [1,1]

For problem to have valid solution: max(piles) * h >= sum(piles)
Or equivalently: h >= ceil(sum(piles) / max(piles))

Assuming problem guarantees valid solution exists,
high = max(piles) is sufficient upper bound

Example 4:
Input: piles = [1,10,1,1], h = 4

Bounds: low=1, high=10
sum=13, need 4 hours, ceil(13/4)=4
So answer should be around 4

Iteration 1: mid=5
reqTime([1,10,1,1], 5) = ceil(1/5) + ceil(10/5) + ceil(1/5) + ceil(1/5)
= 1 + 2 + 1 + 1 = 5
5 <= 4? No, low=6

Iteration 2: mid=8
reqTime([1,10,1,1], 8) = 1 + 2 + 1 + 1 = 5
5 <= 4? No, low=9

Iteration 3: mid=9
reqTime([1,10,1,1], 9) = 1 + 2 + 1 + 1 = 5
5 <= 4? No, low=10

Iteration 4: mid=10
reqTime([1,10,1,1], 10) = 1 + 1 + 1 + 1 = 4
4 <= 4? Yes, ans=10, high=9

low > high, return ans=10

But we could do better! Let's check speed 4:
reqTime([1,10,1,1], 4) = ceil(1/4) + ceil(10/4) + ceil(1/4) + ceil(1/4)
= 1 + 3 + 1 + 1 = 6
6 <= 4? No

Speed 5:
reqTime = 1 + 2 + 1 + 1 = 5
5 <= 4? No

Speed 6:
reqTime = 1 + ceil(10/6) + 1 + 1 = 1 + 2 + 1 + 1 = 5
5 <= 4? No

Speed 7:
reqTime = 1 + ceil(10/7) + 1 + 1 = 1 + 2 + 1 + 1 = 5
5 <= 4? No

Speed 10:
reqTime = 1 + 1 + 1 + 1 = 4 ✓

So answer is 10... but I expected something smaller
Let me recalculate speed 5:
ceil(1/5) = 1
ceil(10/5) = 2
ceil(1/5) = 1
ceil(1/5) = 1
Total = 5 hours, but we need 4

So indeed answer is at least 6

Speed 6:
ceil(10/6) = ceil(1.666...) = 2
1 + 2 + 1 + 1 = 5

Speed 10:
ceil(10/10) = 1
1 + 1 + 1 + 1 = 4 ✓

So we need to find minimum speed where total <= 4
Seems answer might be 10 based on calculation

Edge Cases:
- Single pile: ans = pile size if h=1, else ans=1
- All same: ans = ceil(pile / h * m)
- Large h: ans = 1
- h = number of piles: ans = max(piles)

Ceiling Division:
- ceil(a/b) in floating point: ceil((double)a/b)
- ceil(a/b) in integer: (a+b-1)/b
- Code uses floating point for clarity

Monotonic Behavior:
speed 1: max hours (sum of all piles)
speed 2: fewer hours
...
speed max: 1 hour each (at most m hours total)

Why Binary Search:
- Linear search: O(n * max(piles)) - too slow
- Binary search: O(n * log max(piles)) - much better
- For large piles, huge difference

Constraint Importance:
- Problem must ensure h >= 1 and m >= 1
- Problem must ensure solution exists (m*max(piles) >= h)
- Otherwise search space invalid

*/