class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        // 1. Initialize mindist to a very large value
        int mindist = INT_MAX; 
        unordered_map<int, vector<int>> mpp;
        
        for(int i = 0; i < nums.size(); i++){
            mpp[nums[i]].push_back(i);
        }
        
        for(auto& it : mpp){
            // Use a reference to avoid copying the vector
            vector<int>& ans = it.second; 
            if(ans.size() < 3) continue;

            int l = 0;
            for(int r = 0; r < ans.size(); r++){
                if(r - l + 1 > 3) l++;
                if(r - l + 1 == 3){
                    int dist = 2 * (ans[r] - ans[l]);
                    // 2. Update the variable declared outside the loop
                    mindist = min(dist, mindist); 
                }
            }
        }
        
        // 3. Compare mindist (the result), not ans (the vector)
        return (mindist == INT_MAX) ? -1 : mindist;
    }
};
