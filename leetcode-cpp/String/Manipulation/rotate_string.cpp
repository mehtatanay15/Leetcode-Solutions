class Solution {
public:
    bool rotateString(string s, string goal) {
        bool ans = false;

        int n = s.length();

        for(int i=0; i<n ; i++)
        {
            if(s == goal)
            {
                ans = true;
            }
            char first = s[0];
            s = s.substr(1) + first;


        }

        return ans;
    }
};