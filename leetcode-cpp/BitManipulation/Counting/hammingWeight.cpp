class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;

        while(n) {
            n = n & (n - 1); // removes one set bit
            count++;
        }

        return count;
    }
};