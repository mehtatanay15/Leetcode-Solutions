class Solution {
public:

    int totalB(vector<int> &temp, int day, int k)
{
    int count = 0;
    int bouquets = 0;

    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i] <= day)  
        {
            count++;
            if(count == k)
            {
                bouquets++;
                count = 0;   
            }
        }
        else
        {
            count = 0;  
        }
    }

    return bouquets;
}
    int minDays(vector<int>& bloomDay, int m, int k) {
       int n = bloomDay.size();

        int maxi = -1;

        for(int i =0; i<n; i++)
        {
             if(bloomDay[i]> maxi)
             {
                maxi = bloomDay[i];
             }
        }  

        int low = 1;
        int high = maxi;
        int ans = -1;

        while(low<=high)
        {
            int mid = (low + high)/2;

            int totalbouqet = totalB(bloomDay, mid, k);

            if(totalbouqet>=m)
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