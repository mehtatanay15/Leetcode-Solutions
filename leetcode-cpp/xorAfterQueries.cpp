class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        int MOD = 1000000007;

        // NEW: effect array
        vector<long long> effect(n, 1);

        for(int i = 0; i < q; i++)
        {
            vector<int> temp = queries[i];
            int idx = temp[0];

            while(idx <= temp[1])
            {
                // CHANGE: update effect instead of nums
                effect[idx] = (effect[idx] * temp[3]) % MOD;
                idx += temp[2];
            }
        }

        int output = 0;

        for(int i = 0; i < n; i++)
        {
            // CHANGE: apply effect here
            long long val = (nums[i] * effect[i]) % MOD;
            output ^= (int)val;
        }

        return output;
    }
};