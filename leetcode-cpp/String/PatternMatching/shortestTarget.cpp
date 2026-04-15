class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();   
        int minDistance =n; 
        int found = false;
        for(int i = 0 ; i<n; i++)
        {
            if(words[i] == target)
            {
                found = true;

                int d = abs(i - startIndex);

                int circulard = n -d;

                int temp = min(d, circulard);

                minDistance = min(temp,minDistance);
            }

        }

        if( found ==  true) return minDistance;
        else return -1;
    }
};