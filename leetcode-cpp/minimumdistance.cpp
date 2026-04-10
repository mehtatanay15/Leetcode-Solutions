class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;

        for(int i = 0; i < nums.size(); i++)
        {
            mp[nums[i]].push_back(i);  // FIXED
        }

        int ans = INT_MAX;
        
        for(auto it = mp.begin(); it != mp.end(); it++)
        {
            vector<int> vec = it->second;

            if(vec.size() >= 3)
            {
                for(int i = 0; i < vec.size() - 2; i++)
                {
                    int dist = 2 * (vec[i+2] - vec[i]);
                    
                    if(dist < ans)
                    {
                        ans = dist;
                    }
                }
            }
        }

        if(ans == INT_MAX)
            return -1;

        return ans;
    }
};