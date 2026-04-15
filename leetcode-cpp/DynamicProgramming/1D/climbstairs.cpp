class Solution {
public:
    int climbStairs(int n) {
        if(n<=2) return n;

        int f = 1;
        int s = 2;

        for(int i =3; i<=n; i++)
        {
            int c = f+s;
            f= s;
            s = c;
        }
        return s;
    }
};