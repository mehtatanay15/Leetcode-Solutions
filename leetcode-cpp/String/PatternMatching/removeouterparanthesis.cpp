class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int n = s.length();
        int c=0;
        for(int i=0;i<n;i++)
        {

            if(s[i]== '(')
            {
                if(c>0)
                {
                    result+= s[i];
                }
                c++;
            }

            else{
                c--;
                if(c>0)
                {
                    result += s[i];
                }
            }
        }
        return result;
    }
};