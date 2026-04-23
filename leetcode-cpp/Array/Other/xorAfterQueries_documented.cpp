// LeetCode 1738: Find Kth Largest XOR Coordinate Value
// Problem: Calculate XOR of array elements after multiple transformation queries
// Approach: Accumulate multiplicative effects, apply at calculation time

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        int MOD = 1000000007;

        // Multiplicative effect array (how much each element is multiplied)
        vector<long long> effect(n, 1);

        // Process each query: multiply elements in range with specified step
        for(int i = 0; i < q; i++)
        {
            vector<int> temp = queries[i];
            int idx = temp[0];           // Starting index
            int end = temp[1];           // Ending index (inclusive)
            int step = temp[2];          // Step size
            int multiplier = temp[3];    // Multiply by this value

            // Apply multiplier to all indices: start, start+step, start+2*step, ...
            while(idx <= end)
            {
                effect[idx] = (effect[idx] * multiplier) % MOD;
                idx += step;
            }
        }

        // Calculate final XOR result
        int output = 0;

        for(int i = 0; i < n; i++)
        {
            // Apply accumulated effects to each element
            long long val = (nums[i] * effect[i]) % MOD;
            
            // XOR this transformed value into result
            output ^= (int)val;
        }

        return output;
    }
};

/*\nTime Complexity: O(q * n)\n- For each query, might traverse up to n elements (worst case: step=1)\n- q queries total\n- Final XOR loop: O(n)\n- Total: O(q*n) where q*n is dominated term\n\nSpace Complexity: O(n)\n- Effect array of size n: O(n)\n- Query vector copy: O(1) since queries are small\n\nAlgorithm (Multiplicative Effect Accumulation):\n1. Initialize effect array with all 1s (no multiplication)\n2. For each query [start, end, step, multiplier]:\n   a. For indices: start, start+step, start+2*step, ..., while <= end\n   b. Multiply effect[idx] by multiplier (mod MOD)\n3. After all queries, calculate final result:\n   a. For each index, compute: transformed_value = nums[i] * effect[i] mod MOD\n   b. XOR all transformed values together\n\nKey Insight - Multiplicative Effect:\n- Multiple queries on same index: effects multiply\n- Query 1: multiply by m1\n- Query 2: multiply by m2 (if overlapping)\n- Result at index: nums[i] * m1 * m2 mod MOD\n- Deferred application: accumulate multipliers, apply once at end\n\nQuery Parameter Meanings:\n- [start, end, step, multiplier]\n- start: first index to affect\n- end: last index to affect (inclusive)\n- step: stride through indices (e.g., step=2 means every other element)\n- multiplier: value to multiply with\n\nExample:\nInput: nums = [2,4,6,8,10], queries = [[0,4,1,3]]\n\nQuery 0: start=0, end=4, step=1, multiplier=3\nAffects indices: 0,1,2,3,4 (all)\nEffect array: [3,3,3,3,3]\n\nTransformed values:\nnums[0]*3 mod MOD = 6\nnums[1]*3 mod MOD = 12\nnums[2]*3 mod MOD = 18\nnums[3]*3 mod MOD = 24\nnums[4]*3 mod MOD = 30\n\nFinal XOR: 6 ^ 12 ^ 18 ^ 24 ^ 30\n= 0110 ^ 1100 ^ 10010 ^ 11000 ^ 11110\n= 0110\n= 6\n\nWait, let me recalculate XOR properly:\n6 = 00110\n12 = 01100\n6 ^ 12 = 01010 = 10\n\n10 ^ 18:\n10 = 01010\n18 = 10010\n10 ^ 18 = 11000 = 24\n\n24 ^ 24:\n24 ^ 24 = 0\n\n0 ^ 30:\n0 ^ 30 = 30\n\nFinal: 30\n\nExample 2 - Multiple Queries:\nInput: nums = [1,2,4,8], queries = [[0,3,1,2],[1,3,2,3]]\n\nQuery 1: start=0, end=3, step=1, multiplier=2\nMultiplies all indices by 2\nEffect: [2,2,2,2]\n\nQuery 2: start=1, end=3, step=2, multiplier=3\nMultiplies indices 1,3 by 3\nEffect: [2, 2*3=6, 2, 2*3=6]\n\nTransformed:\n1*2 = 2\n2*6 = 12\n4*2 = 8\n8*6 = 48\n\nXOR: 2 ^ 12 ^ 8 ^ 48\n2 = 000010\n12 = 001100\n8 = 001000\n48 = 110000\n\n2 ^ 12 = 001110 = 14\n14 ^ 8 = 001110 ^ 001000 = 000110 = 6\n6 ^ 48 = 000110 ^ 110000 = 110110 = 54\n\nResult: 54\n\nStep Parameter Impact:\n- step=1: affects consecutive elements (0,1,2,3,...)\n- step=2: affects alternating elements (0,2,4,...)\n- step=3: affects every third element\n- Large step: might skip many elements\n\nMOD Operation Significance:\n- Values can grow large with multiple multiplications\n- Take modulo to keep numbers manageable\n- Modulo 10^9+7 is standard for such problems\n- XOR works on the modulo'd values\n\nEdge Cases:\n- No queries: effect array stays [1,1,...], XOR of original nums\n- Step larger than range: might hit only one element\n- Multiplier = 1: effect on those indices unchanged\n- Large numbers: MOD prevents overflow\n\nOptimization Opportunity:\n- If step=1 and all indices, use prefix sums\n- If ranges are sparse, segment tree better\n- Current approach simple but O(q*n) worst case\n\nWhy This Algorithm:\n- Simple to understand and implement\n- Accumulate effects in O(q*n) total\n- Apply effects in O(n)\n- No complex data structures needed\n\nAlternative Approach (Range Updates):\n- Could use lazy propagation segment tree\n- Or difference arrays for range updates\n- More complex, similar time complexity\n- Current approach more straightforward\n\nXOR Properties Used:\n- Associative: (a ^ b) ^ c = a ^ (b ^ c)\n- Commutative: a ^ b = b ^ a\n- Identity: a ^ 0 = a\n- Self-inverse: a ^ a = 0\n- Can XOR in any order\n\nRelated Concepts:\n- Range multiplication\n- Multiple queries on array\n- XOR operations\n- Modular arithmetic\n\n*/
