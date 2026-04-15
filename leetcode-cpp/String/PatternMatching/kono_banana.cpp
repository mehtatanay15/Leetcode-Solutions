class Solution {
public:

     long long reqTime ( vector<int> &temp , int hr)
        {
            long long totalhr = 0;
            for(int i = 0; i<temp.size(); i++)
            {
                totalhr += ceil((double)temp[i]/(double)hr);
            }
            return totalhr;
        }

    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();

        int maxi = -1;

        for(int i =0; i<n; i++)
        {
             if(piles[i]> maxi)
             {
                maxi = piles[i];
             }
        }


        int low = 1;
        int high = maxi;
        int ans;

        while(low<=high)
        {
            int mid = (low + high)/2;

            long long totalhr = reqTime(piles,mid);

            if(totalhr<=h)
            {
                ans = mid;
                high = mid - 1;
            }
            else{
                low = mid +1;
            }
        }

        return ans;
    }
};