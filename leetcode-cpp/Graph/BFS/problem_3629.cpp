// LeetCode 3629: Minimum Jumps to Reach Last Index with Prime Factors
// Problem: From each index i, can jump to:
//   1. Adjacent indices (i-1, i+1)
//   2. Any index j where nums[i] and nums[j] share a prime factor
// Find minimum jumps to reach index n-1
// Approach: BFS with prime factorization and graph construction

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    static const int MAX_V = 1000001;
    static vector<bool> is_prime;
    
    // Sieve of Eratosthenes for prime checking
    static void compute_sieve() {
        if (!is_prime.empty()) return;
        is_prime.assign(MAX_V, true);
        is_prime[0] = is_prime[1] = false;
        for (int p = 2; p * p < MAX_V; p++) {
            if (is_prime[p]) {
                for (int i = p * p; i < MAX_V; i += p)
                    is_prime[i] = false;
            }
        }
    }

public:
    int minJumps(vector<int>& nums) {
        compute_sieve();
        int n = nums.size();
        if (n <= 1) return 0;

        // Step 1: Build graph - map prime factors to indices that contain them
        // prime_to_indices[p] = list of indices where nums[i] has prime factor p
        unordered_map<int, vector<int>> prime_to_indices;
        for (int i = 0; i < n; ++i) {
            int temp = nums[i];
            
            // Find all unique prime factors of nums[i]
            for (int d = 2; d * d <= temp; ++d) {
                if (temp % d == 0) {
                    prime_to_indices[d].push_back(i);
                    // Remove all occurrences of d
                    while (temp % d == 0) temp /= d;
                }
            }
            // If temp > 1, it's a prime factor
            if (temp > 1) prime_to_indices[temp].push_back(i);
        }

        // Step 2: BFS from index 0 to find shortest path to n-1
        queue<int> q;
        q.push(0);
        
        vector<int> dist(n, -1);
        dist[0] = 0;
        
        // Track which prime factors we've already processed
        // to avoid redundant edge additions
        unordered_map<int, bool> prime_visited;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Reached destination
            if (curr == n - 1) return dist[curr];

            // Option 1: Jump to adjacent indices (curr-1, curr+1)
            for (int next_idx : {curr - 1, curr + 1}) {
                if (next_idx >= 0 && next_idx < n && dist[next_idx] == -1) {
                    dist[next_idx] = dist[curr] + 1;
                    q.push(next_idx);
                }
            }

            // Option 2: Jump to any index sharing a prime factor
            int p = nums[curr];
            if (p < MAX_V && is_prime[p] && !prime_visited[p]) {
                // If nums[curr] is prime, connect to all indices with this prime factor
                for (int target_idx : prime_to_indices[p]) {
                    if (dist[target_idx] == -1) {
                        dist[target_idx] = dist[curr] + 1;
                        q.push(target_idx);
                    }
                }
                // Mark prime as visited and clear edges to avoid revisiting
                prime_visited[p] = true;
                prime_to_indices[p].clear();
            } else if (p >= MAX_V || !is_prime[p]) {
                // If nums[curr] is composite, connect via all its prime factors
                int temp = p;
                for (int d = 2; d * d <= temp; ++d) {
                    if (temp % d == 0) {
                        if (!prime_visited[d]) {
                            for (int target_idx : prime_to_indices[d]) {
                                if (dist[target_idx] == -1) {
                                    dist[target_idx] = dist[curr] + 1;
                                    q.push(target_idx);
                                }
                            }
                            prime_visited[d] = true;
                            prime_to_indices[d].clear();
                        }
                        while (temp % d == 0) temp /= d;
                    }
                }
                if (temp > 1 && !prime_visited[temp]) {
                    for (int target_idx : prime_to_indices[temp]) {
                        if (dist[target_idx] == -1) {
                            dist[target_idx] = dist[curr] + 1;
                            q.push(target_idx);
                        }
                    }
                    prime_visited[temp] = true;
                    prime_to_indices[temp].clear();
                }
            }
        }

        return -1;  // Unreachable
    }
};

vector<bool> Solution::is_prime;

/*
Time Complexity: O(n * √M + E) where:
  - n = array length
  - M = maximum value in array
  - √M = prime factorization time per element
  - E = number of edges in graph (adjacency + prime connections)
  - BFS: O(V + E) where V = n
Space Complexity: O(n + M) - prime sieve + prime_to_indices map

Algorithm Explanation:

Step 1 - Prime Factorization Preprocessing:
1. Use Sieve of Eratosthenes to precompute all primes up to MAX_V
2. For each number in nums:
   - Find all unique prime factors
   - Map each prime to indices containing it
3. Result: prime_to_indices[p] = list of indices with prime factor p

Step 2 - Graph Construction (Implicit):
Each index i connects to:
1. Adjacent indices: i-1 and i+1 (cost 1)
2. Any index j where nums[i] and nums[j] share a prime factor (cost 1)

Step 3 - BFS to Find Shortest Path:
1. Start from index 0 with distance 0
2. For each index, explore:
   - Adjacent positions (always available)
   - All indices sharing prime factors (mark prime as visited)
3. First time reaching index n-1 is the answer

Optimization - Prime Visited Tracking:
- Once we process a prime factor, mark it visited
- Clear the edges from that prime
- Prevents duplicate work in future explorations
- Key insight: Each prime factor edge is used at most once per component

Example:
nums = [3,6,9,12]

Prime factorizations:
- 3: prime 3
- 6: primes 2, 3
- 9: prime 3
- 12: primes 2, 3

prime_to_indices:
- 2: [1, 3]
- 3: [0, 1, 2, 3]

BFS from index 0:
1. Start: dist[0] = 0
2. From 0 (value 3, prime):
   - Adjacent: dist[1] = 1
   - Prime 3 indices: dist[1]=1 (already), dist[2]=1, dist[3]=1
   - Mark prime 3 visited
3. Process queue with indices 1, 2, 3 at distance 1
4. From 1 (value 6, composite, primes 2, 3):
   - Adjacent: dist[0]=0 (skip), dist[2]=1 (skip)
   - Prime 2: [1, 3] → dist[3]=1 (already)
   - Prime 3: already visited
   - Mark primes 2 visited
5. Reached index 3 (n-1) at distance 1
6. Return 1

Edge Cases:
- n = 1: return 0 (already at end)
- n = 2: return 1 (adjacent jump)
- All same value: all indices connected via same prime
- All prime values: each number is its own prime
- Large values > MAX_V: handled specially for composite numbers

Key Insights:
- Sieve preprocessing ensures O(1) prime checking
- Prime factor mapping enables efficient graph traversal
- Visited tracking prevents exponential edge exploration
- BFS guarantees shortest path in unweighted graph
- Clearing edges after visiting reduces memory and time
*/
