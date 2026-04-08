class Solution {
public:
    int maxDepth(string s) {
        int n = s.length();
        int maxi = 0;
        int curr=0;
        for(int i=0; i<n; i++)      
        {
            if(s[i] == '(')
            {
                curr++;
                maxi = max(curr,maxi);
            }
            else if(s[i] == ')')
            {
                curr--;
            }
        }
        return maxi;
    }
};